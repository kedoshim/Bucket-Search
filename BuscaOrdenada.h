#ifndef ORDENADA_H
#define ORDENADA_H

#include "HashNo.h"
#include <queue>
#include <chrono>
#include <algorithm>


struct NoOrdenada
{
    No* no;
    unsigned int ponto;
};

//Realiza a busca em profundidade para encontrar uma solução para o problema dos baldes com nBaldes
void BuscaOrdenada(unsigned int nBaldes,bool crescente)
{
    

    unsigned int n = 0;
    unsigned int regra;

    if(!crescente)
        n=((nBaldes*2)+(nBaldes*(nBaldes-1)))-1;


    NoOrdenada* noAtual = new NoOrdenada;
    noAtual->no = new No(nBaldes);
    
    noAtual->no->getBaldes()->printSolucoes();

    NoOrdenada* noFilho;

    HashNo* hash = new HashNo();


    std::priority_queue<NoOrdenada*, std::vector<NoOrdenada*>, 
                        std::function<bool(NoOrdenada*, NoOrdenada*)>> abertos(
        [](NoOrdenada* a, NoOrdenada* b) { return a->ponto < b->ponto; }
    );

    //para medir o tempo
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    hash->inserirNo(noAtual->no);
    
    while (!(noAtual->no->getBaldes()->getisSolution()))
    { 
        // Visualização
        noAtual->no->getBaldes()->print();

        for (unsigned int i = 0; i < (nBaldes*2)+(nBaldes*(nBaldes-1)); i++)
        {
            regra = static_cast<unsigned int>(std::abs(static_cast<int>(n - i)));
            noFilho = new NoOrdenada;
            noFilho->no = new No(noAtual->no, noAtual->no->getBaldes()->executarRegra(regra));
            noFilho->ponto = static_cast<unsigned int>(std::abs(static_cast<int>(noFilho->no->getBaldes()->getSoma() - noAtual->no->getBaldes()->getSoma())));
            //noFilho->no->getBaldes()->getPontoOrdenada();

            if (!(hash->inserirNo(noFilho->no)))
            {
                delete noFilho->no;
                delete noFilho;
            }else
            {
                abertos.push(noFilho);
            }
        }

        if (abertos.empty())
        {
            std::cout << "Solucao nao encontrada! :( \n";
            delete hash;
            return;
        }

        while(abertos.top()==nullptr)
            abertos.pop();

        NoOrdenada* noAntigo = noAtual;
        noAtual = abertos.top();
        delete noAntigo;
        abertos.pop();
    }

    std::cout<<"Solucao encontrada!\n";
    noAtual->no->printCaminhoSolucao();

    std::cout<<"\nProfundidade: "<<noAtual->no->getProfundidade()<<"\n";

    hash->printStats();

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    std::cout<<"Tempo "<<std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count()<<"\n";

    delete hash;
}

#endif