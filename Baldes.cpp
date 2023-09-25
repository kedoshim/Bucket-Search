#include "Baldes.h"

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


    if((baldes[0].agua > baldes[0].capacidade)||(baldes[0].agua < 0) || (baldes[1].agua > baldes[1].capacidade) || (baldes[1].agua < 0))
        isValid = false;

    if((baldes[0].agua + baldes[1].agua == 4) || (baldes[0].agua + baldes[1].agua == 7))
        isSolution = true;
}

Baldes::~Baldes()
{

}

//Regras de Transição
Baldes* Baldes::esvaziaBaldeA()
{
    return new Baldes(0 , baldes[1].agua);
}
Baldes* Baldes::esvaziaBaldeB()
{
    return new Baldes(baldes[0].agua , 0);
}
Baldes* Baldes::encheBaldeA()
{
    return new Baldes(baldes[0].capacidade , baldes[1].agua);
}
Baldes* Baldes::encheBaldeB()
{
    return new Baldes(baldes[0].agua , baldes[1].capacidade);
}
Baldes* Baldes::passaA2B()
{
    int novaAguaA = 0;
    int novaAguaB = 0;
    int capacidadeRestanteB = baldes[1].capacidade - baldes[1].agua;

    if(baldes[0].agua < capacidadeRestanteB)
    {
        novaAguaB = baldes[1].agua + baldes[0].agua;
        novaAguaA = 0;
        return new Baldes(novaAguaA,novaAguaB);
    }
    else
    {
        novaAguaB = baldes[1].agua + capacidadeRestanteB;
        novaAguaA = baldes[0].agua -capacidadeRestanteB;
        return new Baldes(novaAguaA,novaAguaB);
    } 
}
Baldes* Baldes::passaB2A()
{
    int novaAguaA = 0;
    int novaAguaB = 0;
    int capacidadeRestanteA = baldes[0].capacidade - baldes[0].agua;

    if(baldes[1].agua < capacidadeRestanteA)
    {
        novaAguaA = baldes[0].agua + baldes[1].agua;
        novaAguaB = 0;
        return new Baldes(novaAguaA,novaAguaB);
    }
    else
    {
        novaAguaA = baldes[0].agua + capacidadeRestanteA;
        novaAguaB = baldes[1].agua -capacidadeRestanteA;
        return new Baldes(novaAguaA,novaAguaB);
    }
}

//Verificação de integridade
bool Baldes::getisValid()
{
    return isValid;
}

//Verificação de solução
bool Baldes::getisSolution()
{
    return isSolution;
}


//Escolha de regra
Baldes* Baldes::executarRegra(int nRegra)
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
}

//Printar os valores
void Baldes::print()
{
    std::cout<<baldes[0].agua<<" "<<baldes[1].agua<<std::endl;
}

//Verificar igualdade
bool Baldes::isEqualTo(Baldes* balde2)
{
    if(baldes[0].agua == balde2->baldes[0].agua && baldes[1].agua == balde2->baldes[1].agua)
        return true;
    else
        return false;
}