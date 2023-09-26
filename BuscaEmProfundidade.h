#ifndef PROFUNDIDADE_H
#define PROFUNDIDADE_H

#include "No.h"
#include <stack>

int regraN;

No* proximaRegra(int i,int nbaldes)
{

}


void BuscaEmProfundidade(int nBaldes)
{
    No* noAtual = new No(nBaldes);

    No* noFilho;

    std::stack<No*> pilha;
    std::vector<No*> fechados;
    while(!(noAtual->getBaldes()->getisSolution()))
    {
        //Visualização
        noAtual->getBaldes()->print();

        for(int i = 0; i<(nBaldes*2)+(nBaldes*(nBaldes-1)); i++)
        {
            noFilho = proximaRegra(i,nBaldes);
            
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