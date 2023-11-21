#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "BuscaIrrevogavel.h"

bool stopFlag = false;


std::chrono::high_resolution_clock::time_point ini; 
std::chrono::high_resolution_clock::time_point f;

void BacktrackingRecursiva(No *estadoAtual, bool crescente, std::vector<No *> &caminho, int nRegras, bool printProcessamento, bool printCaminhoSolucao)
{
    unsigned int n = 0;
    unsigned int regra;
    if(!crescente)
        n=nRegras-1;

    if (stopFlag)
        return;

    if(printProcessamento)
        estadoAtual->getBaldes()->print();

    if (estadoAtual->getBaldes()->getisSolution())
    {
        f = std::chrono::high_resolution_clock::now();
        std::cout << "Solucao encontrada!\n\nProfundidade: " << estadoAtual->getProfundidade() << std::endl;
        std::cout << "Tempo: "<<std::chrono::duration_cast<std::chrono::duration<double>>(f - ini).count()<<"\n";
        if(printCaminhoSolucao){
            // Imprimir o estado da solução aqui.
            for (No *no : caminho)
            {
                no->getBaldes()->print();
            }
        }
        stopFlag = true;
        return;
    }

    for (int i = 0; i < nRegras; ++i) // Supondo que 6 é o número de regras possíveis
    {
        regra = static_cast<unsigned int>(std::abs(static_cast<int>(n - i)));
        Baldes *baldesTemporarios = estadoAtual->getBaldes()->executarRegra(regra);

        if (baldesTemporarios->getisValid())
        {
            No *novoNo = new No(estadoAtual, baldesTemporarios);

            if (novoNo->checkUnico())
            {
                caminho.push_back(novoNo); // Adiciona o novo estado ao caminho
                BacktrackingRecursiva(novoNo, crescente, caminho,nRegras,printProcessamento,printCaminhoSolucao);
                // Se a chamada retornou sem encontrar solução, faz o backtrack:
                caminho.pop_back();
                delete novoNo; // Não esqueça de lidar com a memória alocada
            }
            else
            {
                delete novoNo; // Se não é único, limpe o Baldes que foi criado.
            }
        }
    }
}

void BuscaBacktracking(unsigned int nBaldes,bool crescente, bool printProcessamento, bool printCaminhoSolucao)
{
    No *estadoInicial = new No(nBaldes); // Estado inicial do problema.
    estadoInicial->getBaldes()->printSolucoes();
    std::vector<No *> caminho;    // Armazena o caminho até a solução.

    ini = std::chrono::high_resolution_clock::now();
    caminho.push_back(estadoInicial); // Inicia o caminho com o estado inicial.
    BacktrackingRecursiva(estadoInicial, crescente, caminho, (nBaldes*2)+(nBaldes*(nBaldes-1)),printProcessamento, printCaminhoSolucao);
    stopFlag = false;

    // Limpando memória
    for (No *no : caminho)
    {
        delete no;
    }
}

#endif
