#ifndef PROFUNDIDADE_H
#define PROFUNDIDADE_H

#include "No.h"
#include <stack>



void BuscaEmProfundidade(int ordem[])
{
    No* noAtual = new No();

    No* noFilho;

    std::stack<No*> pilha;
    std::vector<No*> fechados;
    while(!(noAtual->getBaldes()->getisSolution()))
    {
        //Visualização
        noAtual->getBaldes()->print();

        for(int i = 0; i<6; i++)
        {
            noFilho = new No(noAtual,noAtual->getBaldes()->executarRegra(ordem[i]));
            
            if(!(noFilho->getBaldes()->getisValid()&&noFilho->checkUnico()))
                delete noFilho;
            else
                pilha.push(noFilho);
                
        }

        //estado atual vai para fechados
        fechados.push_back(noAtual);

        //novo estado atual é o topo da pilha
        noAtual = pilha.top();
        pilha.pop();
    }

    std::cout<<"Solucao encontrada!\n";
    noAtual->getBaldes()->print();
    
}

#endif