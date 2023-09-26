#ifndef PROFUNDIDADE_H
#define PROFUNDIDADE_H

#include "No.h"
#include <stack>

void BuscaEmProfundidade(unsigned int nBaldes,bool crescente)
{
    unsigned int n = 0;
    unsigned int regra;
    if(!crescente)
        n=((nBaldes*2)+(nBaldes*(nBaldes-1)))-1;


    No* noAtual = new No(nBaldes);

    No* noFilho;

    std::stack<No*> pilha;
    std::vector<No*> fechados;
    while(!(noAtual->getBaldes()->getisSolution()))
    {
        //Visualização
        noAtual->getBaldes()->print();

        bool gerouFilho = false;

        for(unsigned int i = 0; i<(nBaldes*2)+(nBaldes*(nBaldes-1)); i++)
        {
            regra = static_cast<unsigned int>(std::abs(static_cast<int>(n - i)));
            noFilho = new No(noAtual,noAtual->getBaldes()->executarRegra(regra));
            
            if(!(noFilho->getBaldes()->getisValid()&&noFilho->checkUnico()))
                delete noFilho;
            else
            {
                pilha.push(noFilho);
                gerouFilho = true;
            }
        }

        if(!gerouFilho)
            std::cout<<"Impasse -> Trocando de ramo\n";

        //estado atual vai para fechados
        fechados.push_back(noAtual);

        
        if(pilha.size()==0)
        {
            std::cout<<"Solucao nao encontrada! :(\n";
            return;
        }

        //novo estado atual é o topo da pilha
        noAtual = pilha.top();
        pilha.pop();
    }

    std::cout<<"Solucao encontrada!\n";
    noAtual->getBaldes()->print();

    std::cout<<"Profundidade: "<<noAtual->getProfundidade()<<"\n";
}

#endif