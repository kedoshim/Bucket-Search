#ifndef IRREVOGAVEL_H
#define IRREVOGAVEL_H

#include "HashNo.h"
#include <chrono>

void BuscaIrrevogavel(unsigned int nBaldes,bool crescente, bool printProcessamento, bool printCaminhoSolucao)
{
    unsigned int n = 0;
    unsigned int regra;
    if(!crescente)
        n=((nBaldes*2)+(nBaldes*(nBaldes-1)))-1;

     //para medir o tempo
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    No* estadoAtual = new No(nBaldes);
    estadoAtual->getBaldes()->printSolucoes();

    while (!estadoAtual->getBaldes()->getisSolution())
    {
        //Visualização
        if(printProcessamento)
            estadoAtual->getBaldes()->print();

        bool regraAplicada = false;

        for(unsigned int i = 0; i<(nBaldes*2)+(nBaldes*(nBaldes-1)); i++)
        {
            Baldes *novosBaldes = estadoAtual->getBaldes();

            regra = static_cast<unsigned int>(std::abs(static_cast<int>(n - i)));
            novosBaldes = novosBaldes->executarRegra(regra);

            if (novosBaldes->getisValid())
            {
                No *novoNo = new No(estadoAtual, novosBaldes);

                if (novoNo->checkUnico())
                {
                    if (novoNo->getBaldes()->getisSolution())
                    {
                        std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
                        std::cout << "Solucao encontrada!\n\nProfundidade: " << estadoAtual->getProfundidade() << std::endl;
                        std::cout << "Tempo: "<<std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count()<<"\n";

                        // Imprimir o estado da solução aqui
                        std::vector<No *> caminho;
                        estadoAtual = novoNo;
                        /* while (estadoAtual != nullptr)
                        {
                            caminho.push_back(estadoAtual);
                            estadoAtual = estadoAtual->getPai();
                        }

                        for (int i = caminho.size() - 1; i >= 0; --i)
                        {
                            caminho[i]->getBaldes()->print();
                        } */
                        if(printCaminhoSolucao)
                            estadoAtual->printCaminhoSolucao();

                        delete novoNo;
                        delete estadoAtual;
                        return;
                    }
                    if(printProcessamento)
                        novoNo->getBaldes()->print();

                    estadoAtual = novoNo;
                    regraAplicada = true;
                    break;
                }
                else
                {
                    delete novoNo;
                }
            }
        }

        if (!regraAplicada)
        {
            std::cout << "Nenhuma regra pôde ser aplicada. Busca falhou." << std::endl;
            delete estadoAtual;
            return;
        }
    }

    std::cout << "Nao foi possivel encontrar uma solucao." << std::endl;
    delete estadoAtual;
}

#endif
