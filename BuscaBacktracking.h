#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "Baldes.h"

bool stopFlag = false;

void BacktrackingRecursiva(No *estadoAtual, int ordem[], std::vector<No *> &caminho)
{
    if (stopFlag)
        return;

    if (estadoAtual->getBaldes()->getisSolution())
    {
        std::cout << "Solucao encontrada na profundidade " << estadoAtual->getProfundidade() << std::endl;
        // Imprimir o estado da solução aqui.
        for (No *no : caminho)
        {
            no->getBaldes()->print();
        }
        stopFlag = true;
        return;
    }

    for (int i = 0; i < 6; ++i) // Supondo que 6 é o número de regras possíveis
    {
        Baldes *baldesTemporarios = estadoAtual->getBaldes()->executarRegra(ordem[i]);

        if (baldesTemporarios->getisValid())
        {
            No *novoNo = new No(estadoAtual, baldesTemporarios);

            if (novoNo->checkUnico())
            {
                caminho.push_back(novoNo); // Adiciona o novo estado ao caminho
                BacktrackingRecursiva(novoNo, ordem, caminho);
                // Se a chamada retornou sem encontrar solução, faz o backtrack:
                caminho.pop_back();
                delete novoNo; // Não esqueça de lidar com a memória alocada
            }
            else
            {
                delete baldesTemporarios; // Se não é único, limpe o Baldes que foi criado.
            }
        }
    }
}

void BuscaBacktracking(int ordem[])
{
    No *estadoInicial = new No(); // Estado inicial do problema.
    std::vector<No *> caminho;    // Armazena o caminho até a solução.

    caminho.push_back(estadoInicial); // Inicia o caminho com o estado inicial.
    BacktrackingRecursiva(estadoInicial, ordem, caminho);

    // Limpando memória
    for (No *no : caminho)
    {
        delete no;
    }
}

#endif
