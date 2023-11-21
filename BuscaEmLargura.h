#ifndef LARGURA_H
#define LARGURA_H

#include "HashNo.h"
#include <queue>
#include <chrono>


void BuscaEmLargura(unsigned int nBaldes,bool crescente, bool printProcessamento, bool printCaminhoSolucao)
{
    unsigned int n = 0;
    unsigned int regra;
    if(!crescente)
        n=((nBaldes*2)+(nBaldes*(nBaldes-1)))-1;


    No* noAtual = new No(nBaldes);
    noAtual->getBaldes()->printSolucoes();

    No* noFilho;

    HashNo* hash = new HashNo();
    std::queue<No*> fila;
    //std::vector<No*> fechados;
    
    unsigned int profundidadeMAX = nBaldes * 3;

    //para medir o tempo
    std::chrono::high_resolution_clock::time_point inicio = std::chrono::high_resolution_clock::now();

    hash->inserirNo(noAtual);

    while(!(noAtual->getBaldes()->getisSolution()))
    { 
        //Visualização
        if(printProcessamento)
            noAtual->getBaldes()->print();

        bool gerouFilho = false;
        if(noAtual->getProfundidade()<profundidadeMAX)
        {
            //Esse loop itera sobre todas as regras de transicao gerando todos os filhos possiveis de um certo no, deleta os repetidos e insere os validos na fila
            for(unsigned int i = 0; i<(nBaldes*2)+(nBaldes*(nBaldes-1)); i++)
            {
                regra = static_cast<unsigned int>(std::abs(static_cast<int>(n - i)));
                noFilho = new No(noAtual,noAtual->getBaldes()->executarRegra(regra));
                
                //se inserirNo retorna falso, significa que esse no gerado já foi gerado anteriormente em uma profundidade menor ou igual a atual, entao ele e cortado
                if(!(hash->inserirNo(noFilho)/* &&noFilho->checkUnico() */))
                    delete noFilho;
                else
                {
                    fila.push(noFilho);
                    gerouFilho = true;
                }
            }

            if(!gerouFilho && printProcessamento)
                std::cout<<"Impasse -> Trocando de ramo\n";

        }
        
        else{
            //std::cout<<"> ";
            //std::cout<<"passei do limite :P \n";
        }

        
        if(fila.size()==0)
        {
            std::cout<<"Solucao nao encontrada! :( \n";
            delete hash;
            return;
        }
        

        //novo estado atual é o fronto da fila
        noAtual = fila.front();
        fila.pop();

        while(noAtual==nullptr){
            noAtual = fila.front();
            fila.pop();
        }
    }

    std::cout<<"Solucao encontrada!\n";

    if(printCaminhoSolucao)
        noAtual->printCaminhoSolucao();

    std::cout<<"\nProfundidade: "<<noAtual->getProfundidade()<<"\n";

    hash->printStats();

    std::chrono::high_resolution_clock::time_point fim = std::chrono::high_resolution_clock::now();
    std::cout<<"Tempo "<<std::chrono::duration_cast<std::chrono::duration<double>>(fim - inicio).count()<<"\n";

    delete hash;
}

#endif
