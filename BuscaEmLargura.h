#ifndef LARGURA_H
#define LARGURA_H

#include "No.h"
#include <queue>



void BuscaEmLargura(int ordem[])
{
    No* noAtual = new No();

    No* noFilho;

    std::queue<No*> fila;
    std::vector<No*> fechados;

    noAtual->getBaldes()->print();
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
                fila.push(noFilho);
                
        }

        //estado atual vai para fechados
        fechados.push_back(noAtual);

        //novo estado atual é o topo da fila
        noAtual = fila.front();
        fila.pop();
    }    

    std::cout<<"Lista de fechados"<<std::endl;
    for(int i = 0; i < fechados.size(); i++)
    {
        fechados[i]->getBaldes()->print();
    }
    std::cout<<std::endl;


    std::cout<<"Solucao encontrada!\n";
    noAtual->getBaldes()->print();
    std::cout<<"Custo solução: "<<noAtual->getProfundidade()<<std::endl;
}

#endif
