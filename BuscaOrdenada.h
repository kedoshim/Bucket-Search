#ifndef ORDENADA_H
#define ORDENADA_H

#include "HashNo.h"
#include <stack>
#include <chrono>


//Realiza a busca em profundidade para encontrar uma solução para o problema dos baldes com nBaldes
void BuscaOrdenada(unsigned int nBaldes,bool crescente)
{
    //para medir o tempo
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    unsigned int n = 0;
    unsigned int regra;

    if(!crescente)
        n=((nBaldes*2)+(nBaldes*(nBaldes-1)))-1;


    No* noAtual = new No(nBaldes);
    noAtual->getBaldes()->printSolucoes();

    No* noFilho;

    HashNo* hash = new HashNo();
    std::vector<No*> abertos;
    //std::vector<No*> fechados;
    
    unsigned int profundidadeMAX = nBaldes * 10;
    while(!(noAtual->getBaldes()->getisSolution()))
    { 
        //Visualização
        noAtual->getBaldes()->print();

    }

    hash->printStats();

    delete hash;
    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    std::cout<<"Tempo "<<std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count()<<"\n";
}

#endif