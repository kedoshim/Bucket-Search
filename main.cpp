#ifndef MAIN_H
#define MAIN_H

#include "BuscaIrrevogavel.h"
#include "BuscaBacktracking.h"
#include "BuscaEmLargura.h"
#include "BuscaEmProfundidade.h"

int main()
{
    std::cout<<"Quantos baldes?\n";
    unsigned int nBalde;
    std::cin>>nBalde;

    std::cout<<"Ordem Crescente?(1=true  0=false)\n";
    unsigned int crescente_int;
    std::cin>>crescente_int;

    bool crescent = crescente_int==1 ? true : false;

    BuscaEmProfundidade(nBalde,crescent);

    return 0;
}

#endif