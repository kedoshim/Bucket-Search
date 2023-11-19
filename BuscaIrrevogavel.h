#ifndef IRREVOGAVEL_H
#define IRREVOGAVEL_H

#include "Baldes.h"
#include "No.h"
#include <vector>

void BuscaIrrevogavel(int ordem[])
{
    No *estadoAtual = new No();

    while (!estadoAtual->getBaldes()->getisSolution())
    {
        bool regraAplicada = false;

        for (int i = 0; i < 6; ++i)
        {
            Baldes *novosBaldes = estadoAtual->getBaldes();

            novosBaldes = novosBaldes->executarRegra(ordem[i]);
            if (novosBaldes->getisValid())
            {
                No *novoNo = new No(estadoAtual, novosBaldes);

                if (novoNo->checkUnico())
                {
                    if (novoNo->getBaldes()->getisSolution())
                    {
                        std::cout << "Solucao encontrada na profundidade " << novoNo->getProfundidade() << std::endl;
                        // Imprimir o estado da solução aqui
                        std::vector<No *> caminho;
                        No *noAtual = novoNo;
                        while (noAtual != nullptr)
                        {
                            caminho.push_back(noAtual);
                            noAtual = noAtual->getPai();
                        }

                        for (int i = caminho.size() - 1; i >= 0; --i)
                        {
                            caminho[i]->getBaldes()->print();
                        }

                        delete novoNo;
                        delete estadoAtual;
                        return;
                    }

                    estadoAtual = novoNo;
                    regraAplicada = true;
                    break;
                }
                else
                {
                    delete novosBaldes;
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
