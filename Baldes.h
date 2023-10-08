#ifndef BALDES_H
#define BALDES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

struct balde
        {
            unsigned int agua = 0;
            unsigned int capacidade = 0;
        };

class Baldes
{
    private:
        //atributos estáticos
        static std::vector<unsigned int> primos;
        static std::vector<unsigned int> solucoes;
        static unsigned int nBaldes;
        
        std::vector<balde*> baldes;

        unsigned int soma = 0;

        //Regras de Transição
        Baldes* esvaziaBalde(unsigned int balde);
        Baldes* encheBalde(unsigned int balde);
        Baldes* passaAgua(unsigned int baldeA, unsigned int baldeB);

        //Calcula quais devem ser as somas solução
        void findSolucoes();

    public:

        Baldes();
        Baldes(unsigned int capacidadeA, unsigned int capacidadeB);
        Baldes(unsigned int numeroBaldes);
        Baldes(const Baldes& b);
        ~Baldes();        

        //Verificação de integridade
        bool getisValid();

        //Verificação de solução
        bool getisSolution();

        //Escolha de regra
        Baldes* executarRegra(unsigned int nRegra);

        //Printar os valores
        void print();

        //Verificar igualdade
        bool isEqualTo(Baldes* balde2);

        unsigned int getNBaldes();

        unsigned int getAgua(unsigned int balde);

        unsigned int getCapacidade(unsigned int balde);

        unsigned int getSoma();

        void printSolucoes();


};

#endif