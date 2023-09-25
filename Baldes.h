#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Baldes
{
    private:

        struct balde
        {
            int agua = 0;
            int capacidade = 0;
        };

        balde baldes[2];

        bool isValid = true;

    public:

        Baldes();
        Baldes(int capacidadeA, int capacidadeB);
        ~Baldes();

        //Regras de Transição
        Baldes esvaziaBaldeA(); //1
        Baldes esvaziaBaldeB(); //2
        Baldes encheBaldeA();   //3
        Baldes encheBaldeB();   //4
        Baldes passaA2B();      //5
        Baldes passaB2A();      //6

        //Verificação de integridade
        bool getisValid();

        //Escolha de regra
        Baldes executarRegra(int nRegra);


};