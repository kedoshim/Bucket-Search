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

        std::vector<unsigned int> primos = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};        

        std::vector<balde*> baldes;

        std::vector<unsigned int> solucoes;

        unsigned int nBaldes=2;

        unsigned int soma = 0;

        bool isValid = true;
        bool isSolution = false;

        //Regras de Transição
        Baldes* esvaziaBalde(unsigned int balde);
        Baldes* encheBalde(unsigned int balde);
        Baldes* passaAgua(unsigned int baldeA, unsigned int baldeB);

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


};

#endif