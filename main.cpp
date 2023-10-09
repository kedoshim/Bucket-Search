#ifndef MAIN_H
#define MAIN_H

#include "BuscaIrrevogavel.h"
#include "BuscaBacktracking.h"
#include "BuscaEmLargura.h"
#include "BuscaEmProfundidade.h"
#include "BuscaOrdenada.h"

int main()
{
    void (*funcoes[5])(unsigned int, bool) = {BuscaIrrevogavel, BuscaBacktracking, BuscaEmLargura, BuscaEmProfundidade, BuscaOrdenada};

    unsigned int busca;
    while(busca!=0)
    {    
        std::cout<<"Quantos baldes?\n";
        unsigned int nBalde;
        std::cin>>nBalde;

        if(nBalde==0) return 0;

        std::cout<<"Ordem Crescente?(1=true  0=false)\n";
        unsigned int crescente_int;
        std::cin>>crescente_int;

        bool crescent = crescente_int==1 ? true : false;

        std::cout<<"Qual busca?\n";
        std::cout<<"1 - Busca Irrevogavel\n";
        std::cout<<"2 - Busca Backtracking\n";
        std::cout<<"3 - Busca em Largura\n";
        std::cout<<"4 - Busca em Profundidade\n";
        std::cout<<"5 - Busca Ordenada\n";

        std::cout<<"0 - Sair\n";
        std::cin>>busca;
        
        if(busca==0) return 0;
        
        // Verifica se o valor de busca é válido
        if (busca >= 1 && busca <= 5) {
            // Chama a função apropriada
            funcoes[busca - 1](nBalde, crescent);
        } else {
            std::cout << "Opcao invalida!\n";
        }
        
        std::cout<<"\n--------------\n\n";
    }

    return 0;
}

#endif