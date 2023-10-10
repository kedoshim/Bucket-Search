#ifndef MAIN_H
#define MAIN_H

#include "BuscaIrrevogavel.h"
#include "BuscaBacktracking.h"
#include "BuscaEmLargura.h"
#include "BuscaEmProfundidade.h"
/* #include "BuscaOrdenada.h"
#include "BuscaGulosa.h" */
#include "BuscaAEstrela.h"

int main()
{
    void (*funcoes[7])(unsigned int, bool, bool, bool) = {BuscaIrrevogavel, BuscaBacktracking, BuscaEmLargura, BuscaEmProfundidade, BuscaOrdenada, BuscaGulosa, BuscaAEstrela};

    int busca=1;
    bool printProcessamento = false;
    bool printSolucao = false;
    while(busca!=0)
    {    
        std::cout<<"Quantos baldes?\n";
        unsigned int nBalde;
        std::cin>>nBalde;

        if(nBalde==0) return 0;

        std::cout<<"Ordem Crescente?(0=false 1=true)\n";
        unsigned int crescente_int;
        std::cin>>crescente_int;

        bool crescent = crescente_int==1 ? true : false;

        std::cout<<"Qual busca?\n";
        std::cout<<" 1 - Busca Irrevogavel\n";
        std::cout<<" 2 - Busca Backtracking\n";
        std::cout<<" 3 - Busca em Largura\n";
        std::cout<<" 4 - Busca em Profundidade\n";
        std::cout<<" 5 - Busca Ordenada\n";
        std::cout<<" 6 - Busca Gulosa\n";
        std::cout<<" 7 - Busca A Estrela\n";

        std::cout<<"\n 0 - Sair\n";
        std::cout<<"-1 - Opcoes\n";
        std::cin>>busca;

        if(busca==-1)
        {
            std::cout<<"Print Processamento?(0=false 1=true)\n";
            std::cin>>printProcessamento;
            std::cout<<"Print Solucao?(0=false 1=true)\n";
            std::cin>>printSolucao;
        }
        
        if(busca==0) return 0;
        
        // Verifica se o valor de busca é válido
        if (busca >= 1 && busca <= 7) {
            // Chama a função apropriada
            funcoes[busca - 1](nBalde, crescent, printProcessamento, printSolucao);
        } else {
            std::cout << "Opcao invalida!\n";
        }
        
        std::cout<<"\n--------------\n\n";
    }

    return 0;
}

#endif