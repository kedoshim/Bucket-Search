#include "Baldes.h"
#include <functional>       
#include <cmath>
#include <limits>

std::vector<unsigned int> Baldes::primos = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239};
std::vector<unsigned int> Baldes::solucoes(2);
unsigned int Baldes::nBaldes = 2;

Baldes::Baldes(){
    baldes[0]->capacidade=3;
    baldes[1]->capacidade=5;
}

Baldes::Baldes(unsigned int numeroBaldes)
{    
    if(numeroBaldes>47)
        numeroBaldes=47;
    nBaldes = numeroBaldes;

    for(unsigned int i = 0; i< nBaldes; i++)
    {
        baldes.push_back(new balde());
        baldes[i]->capacidade = primos[i];
    }   

    findSolucoes();
}

Baldes::Baldes(const Baldes& b)
{
    nBaldes = b.nBaldes;
    soma = b.soma;

    // Create new balde structures and copy values
    for (const balde* originalBalde : b.baldes)
    {
        balde* newBalde = new balde;
        newBalde->agua = originalBalde->agua;
        newBalde->capacidade = originalBalde->capacidade;
        baldes.push_back(newBalde);
    }

    // Copy the solutions
    solucoes = b.solucoes;
}

Baldes::~Baldes()
{
    for (balde* b : baldes)
    {
        delete b;
    }
    baldes.clear();
}

//Regras de Transição
Baldes* Baldes::esvaziaBalde(unsigned int baldeN)
{
    unsigned int aguaAtual = baldes[baldeN]->agua;
    baldes[baldeN]->agua = 0;
    soma = soma-aguaAtual;
    Baldes baldeNovo(*this); 
    baldes[baldeN]->agua = aguaAtual;
    soma = soma + aguaAtual;
    
    return new Baldes(baldeNovo);
}

Baldes* Baldes::encheBalde(unsigned int baldeN)
{
    unsigned int aguaAtual = baldes[baldeN]->agua;
    unsigned int capacidadeBalde = baldes[baldeN]->capacidade;
    baldes[baldeN]->agua = capacidadeBalde;
    soma = soma - aguaAtual + capacidadeBalde;
    Baldes baldeNovo(*this); 
    baldes[baldeN]->agua = aguaAtual;
    soma = soma + aguaAtual - capacidadeBalde;

    return new Baldes(baldeNovo);
}

Baldes* Baldes::passaAgua(unsigned int baldeA, unsigned int baldeB)
{
    unsigned int aguaAtualA = baldes[baldeA]->agua;
    unsigned int aguaAtualB = baldes[baldeB]->agua;   

    unsigned int novaAguaA;
    unsigned int novaAguaB; 
    
    unsigned int capacidadeRestanteB = baldes[baldeB]->capacidade - baldes[baldeB]->agua;

    if(baldes[baldeA]->agua < capacidadeRestanteB)
    {
        novaAguaB = baldes[baldeB]->agua + baldes[baldeA]->agua;
        novaAguaA = 0;
    }
    else
    {
        novaAguaB = baldes[baldeB]->agua + capacidadeRestanteB;
        novaAguaA = baldes[baldeA]->agua - capacidadeRestanteB;
    } 

    baldes[baldeB]->agua = novaAguaB;
    baldes[baldeA]->agua = novaAguaA;

    Baldes baldeNovo(*this); 

    baldes[baldeA]->agua = aguaAtualA;
    baldes[baldeB]->agua = aguaAtualB;

    return new Baldes(baldeNovo); // Return a dynamically allocated copy
}
bool is_prime(unsigned int num) {
            if (num <= 1) return false;
            if (num == 2) return true;
            if (num % 2 == 0) return false;

            for (unsigned int i = 3; i <= sqrt(num); i += 2) {
                if (num % i == 0)
                    return false;
            }

            return true;
        }
unsigned int find_closest_prime(unsigned int n) {
    if (n <= 2) return 2;

    unsigned int lower = n - 1;

    while (true) {
        if (is_prime(lower)) return lower;

        lower--;
    }
}

unsigned int find_closest_power_of_two(unsigned int n) {
    n=n-1;
    if (n <= 2) return 2;

    unsigned int closest_power = 1;
    while (closest_power <= n / 2) {
        closest_power *= 2;
    }

    return closest_power;
}

void Baldes::findSolucoes()
{
    
    
    unsigned somaCapacidade = 0;
    for(unsigned i =0; i< nBaldes; i++)
        somaCapacidade += baldes[i]->capacidade;

    solucoes[0] = find_closest_power_of_two(somaCapacidade);

    solucoes[1] = find_closest_prime(somaCapacidade); 

    //solucoes[0] = (nBaldes * nBaldes)+(nBaldes-2)-(nBaldes/2);
    //solucoes[1] = (primos[nBaldes]); 
    //solucoes.push_back(-1);
    
}

//Verificação de integridade
bool Baldes::getisValid()
{
    for(unsigned int i =0; i< nBaldes; i++)
    {
        if(baldes[i]->agua>baldes[i]->capacidade)
            return false;
    }
    return true;
}

//Verificação de solução
bool Baldes::getisSolution()
{
    /* unsigned int soma = 0;
    for(unsigned int i =0; i<nBaldes; i++)
        soma+=baldes[i]->agua; */

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
        return esvaziaBalde(0);
        break;
    case 2:
        return esvaziaBalde(1);
        break;
    case 3:
        return encheBalde(0);
        break;
    case 4:
        return encheBalde(1);
        break;
    case 5:
        return passaAgua(0,1);
        break;
    case 6:
        return passaAgua(1,0);
        break;
    
    default:
        std::cout<<"instrucao invalida\n";
        return nullptr;
    }
} */


Baldes* Baldes::executarRegra(unsigned int nRegra)
{
    nRegra = nRegra+1;
    unsigned int a;
    unsigned int b;
    if(nRegra<=nBaldes)
    {
        a = nRegra;
        b = 0;
        return esvaziaBalde(a-1);
    }
    else if (nRegra<=nBaldes*2)
    {
        a = nRegra - nBaldes;
        b=0;
        return encheBalde(a-1);
    }
    else if (nRegra <= (nBaldes*2) + (nBaldes*(nBaldes-1)))
    {
        unsigned int ruleNumber = nRegra - (nBaldes*2);
        a = static_cast<unsigned int>(std::trunc((ruleNumber - 1) / (nBaldes-1))) + 1;
        b = (ruleNumber - 1) % (nBaldes-1) + 1;

        if (b >= a)
            b = b + 1;

        return passaAgua(a-1, b-1);
    }
    std::cout<<"Valor de Regra de transicao invalido\n";
    return nullptr;
}

void Baldes::print()
{
    for(unsigned int i =0 ; i<nBaldes ; i++)
        std::cout<<baldes[i]->agua<<" ";
    
    std::cout<<"- "<<soma;
    std::cout<<"\n";
}

//verifica se dois Baldes são iguais
bool Baldes::isEqualTo(Baldes* balde2)
{
    if(soma != balde2->soma)
        return false;
    else
    {
        for(unsigned int i =0; i< nBaldes; i++)
        {
            if(baldes[i]->agua != balde2->baldes[i]->agua)
                return false;
        }
    }
    return true;
}

unsigned int Baldes::getNBaldes()
{
    return nBaldes;
}

unsigned int Baldes::getAgua(unsigned int baldeN)
{
    return baldes[baldeN]->agua;
}

unsigned int Baldes::getCapacidade(unsigned int baldeN)
{
    return baldes[baldeN]->capacidade;
}

void Baldes::printSolucoes()
{
    std::cout<<"solucoes:"<<solucoes[0]<<" "<<solucoes[1]<<"\n";
}

unsigned int Baldes::getSoma()
{
    return soma;
}

