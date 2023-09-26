#include "Baldes.h"
#include <functional>       

Baldes::Baldes(){
    baldes[0].capacidade=3;
    baldes[1].capacidade=5;
}

Baldes::Baldes(int aguaA, int aguaB)
{
    baldes[0].capacidade=3;
    baldes[1].capacidade=5;

    baldes[0].agua=aguaA;
    baldes[1].agua=aguaB;
}

Baldes::Baldes(int numeroBaldes)
{    
    if(numeroBaldes>23)
        numeroBaldes=23;
    nBaldes = numeroBaldes;
    

    for(unsigned int i = 0; i< (unsigned int) nBaldes-1; i++)
    {
        baldes[i].capacidade = primos[i];
    }   

    inicializaRegras();
}

Baldes::Baldes(Baldes* b)
{
    baldes = b->baldes;
    solucoes = b->solucoes;
    nBaldes = b->nBaldes;
}

Baldes::~Baldes()
{

}

//Regras de Transição
Baldes* Baldes::esvaziaBalde(unsigned int nbalde)
{
    int aguaAtual = baldes[nbalde].agua;
    baldes[nbalde].agua = 0;
    Baldes* baldeNovo = new Baldes(this); 
    baldes[nbalde].agua = aguaAtual;
    
    return baldeNovo; 
}
Baldes* Baldes::encheBalde(unsigned int nbalde)
{
    int aguaAtual = baldes[nbalde].agua;
    baldes[nbalde].agua = baldes[nbalde].capacidade;
    Baldes* baldeNovo = new Baldes(this); 
    baldes[nbalde].agua = aguaAtual;

    return baldeNovo;
}
Baldes* Baldes::passaAgua(unsigned int baldeA, unsigned int baldeB)
{
    int aguaAtualA = baldes[baldeA].agua;
    int aguaAtualB = baldes[baldeB].agua;   

    int novaAguaA;
    int novaAguaB; 
    
    int capacidadeRestanteB = baldes[baldeB].capacidade - baldes[baldeB].agua;

    if(baldes[baldeA].agua < capacidadeRestanteB)
    {
        novaAguaB = baldes[baldeB].agua + baldes[baldeA].agua;
        novaAguaA = 0;
    }
    else
    {
        novaAguaB = baldes[baldeB].agua + capacidadeRestanteB;
        novaAguaA = baldes[baldeA].agua - capacidadeRestanteB;
    } 

    baldes[baldeB].agua = novaAguaB;
    baldes[baldeA].agua = novaAguaA;

    Baldes* baldeNovo = new Baldes(this); 

    baldes[baldeA].agua = aguaAtualA;
    baldes[baldeB].agua = aguaAtualB;

    return baldeNovo;
}

void Baldes::inicializaRegras() {
    regras.push_back([this](unsigned int baldeA, unsigned int baldeB) {
        return this->encheBalde(baldeA);
    });

    regras.push_back([this](unsigned int baldeA, unsigned int baldeB) {
        return this->esvaziaBalde(baldeA);
    });

    regras.push_back([this](unsigned int baldeA, unsigned int baldeB) {
        return this->passaAgua(baldeA, baldeB);
    });
}



void Baldes::findSolucoes()
{
    int soma = 0;
    for(unsigned int i = 0; i <(unsigned int) nBaldes ; i++){
        soma+=baldes[i].capacidade;
    }
    solucoes[0] = soma/2;
    solucoes[1] = primos[(unsigned int) nBaldes];
}




//Verificação de integridade
bool Baldes::getisValid()
{
    for(unsigned int i =0; i< (unsigned int) nBaldes; i++)
    {
        if(baldes[i].agua>baldes[i].capacidade || baldes[i].agua < 0)
            return false;
    }
    return true;
}

//Verificação de solução
bool Baldes::getisSolution()
{
    int soma = 0;
    for(unsigned int i =0; i<(unsigned int) nBaldes; i++)
        soma+=baldes[i].agua;

    for(unsigned int i = 0; i < solucoes.size() ; i++)
        if(soma==solucoes[i])
            return true;
    
    return false;
}


//Escolha de regra
/* Baldes* Baldes::executarRegra(int nRegra)
{
    switch (nRegra)
    {
    case 1:
        return esvaziaBaldeA();
        break;
    case 2:
        return esvaziaBaldeB();
        break;
    case 3:
        return encheBaldeA();
        break;
    case 4:
        return encheBaldeB();
        break;
    case 5:
        return passaA2B();
        break;
    case 6:
        return passaB2A();
        break;
    
    default:
        return new Baldes(-1,-1);
    }
} */

Baldes* Baldes::executarRegra(int nRegra)
{
    if(nRegra>nBaldes*2)
    {

    }
}

//Printar os valores
void Baldes::print()
{
    for(unsigned int i =0 ; i<(unsigned int) nBaldes ; i++)
        std::cout<<baldes[i].agua<<" ";
}

//Verificar igualdade
bool Baldes::isEqualTo(Baldes* balde2)
{
    for(unsigned int i =0; i< (unsigned int) nBaldes; i++)
    {
        if(baldes[i].agua != balde2->baldes[i].agua)
            return false;
    }
    return true;
}
