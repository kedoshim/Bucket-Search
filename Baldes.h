#ifndef BALDES_H
#define BALDES_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

struct balde
        {
            int agua = 0;
            int capacidade = 0;
        };

class Baldes
{
    private:

        std::vector<int> primos = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};        

        std::vector<balde> baldes;

        std::vector<int> solucoes;

        std::vector<std::function<Baldes*(unsigned int,unsigned int)>> regras;

        int nBaldes=2;

        bool isValid = true;
        bool isSolution = false;

        //Regras de Transição
        Baldes* esvaziaBalde(unsigned int balde);
        Baldes* encheBalde(unsigned int balde);
        Baldes* passaAgua(unsigned int baldeA, unsigned int baldeB);

        //Preenche o vetro regras
        void inicializaRegras();

        void findSolucoes();

    public:

        Baldes();
        Baldes(int capacidadeA, int capacidadeB);
        Baldes(int numeroBaldes);
        Baldes(Baldes* b);
        ~Baldes();        

        //Verificação de integridade
        bool getisValid();

        //Verificação de solução
        bool getisSolution();

        //Escolha de regra
        Baldes* executarRegra(int nRegra);

        //Printar os valores
        void print();

        //Verificar igualdade
        bool isEqualTo(Baldes* balde2);


};

#endif