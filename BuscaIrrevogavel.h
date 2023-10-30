#ifndef IRREVOGAVEL_H
#define IRREVOGAVEL_H

#include "Baldes.h"
#include "No.h"

void BuscaIrrevogavel(int ordem[])
{
    No *noAtual = new No();
    No *noFilho, *aux;

    while (!(noAtual->getBaldes()->getisSolution()) && noAtual != nullptr)
    {
        // Visualização
        noAtual->getBaldes()->print();

        for (int i = 0; i < 6; i++)
        {
            aux = new No(noAtual, noAtual->getBaldes()->executarRegra(ordem[i]));

            if (aux->checkUnico())
            {
                noFilho = aux;
                break;
            }
        }

        noAtual = noFilho;
    }

    if (!(noFilho->getBaldes()->getisSolution()))
    {
        std::cout << "A busca não encontrou solução.\n";
        return;
    }

    std::cout << "Solucao encontrada!\n";
    noAtual->getBaldes()->print();
}

#endif
