#ifndef HASHNO_H
#define HASHNO_H

#include "No.h"
#include <math.h>
#include <sstream>
#include <functional>

class HashNo
{
    private:
        std::vector<No*>* hashTable;
        std::vector<No*>* substituidos;
        unsigned int tamanhoTabela;
        unsigned int valorAuxiliar;
        unsigned int nInsercoes;
        unsigned int colisoesTotais = 0;

        //achar primos para ser o tamanho da tabela
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
        //achar primos para ser o tamanho da tabela
        unsigned int find_closest_prime(unsigned int n) {
            if (n <= 2) return 2;

            unsigned int lower = n - 1;
            unsigned int upper = n + 1;

            while (true) {
                if (is_prime(lower)) return lower;
                if (is_prime(upper)) return upper;

                lower--;
                upper++;
            }
        }

        //Recebe um nó e faz calculos que tentam atribuir a ele um valor unico
        double calculaValorNo(No* no)
        {
            double valor = 0;
            Baldes* baldes = no->getBaldes();
            unsigned int nb = baldes->getNBaldes();
            unsigned int limitante = (nb - 1) / 10 + 1;

            for(unsigned int i = 0; i < nb; i++) {
                valor += pow(baldes->getAgua(i), ((i + 1) / limitante));
                valor += ((baldes->getAgua(i)+1) * pow(baldes->getCapacidade(i),2) * (baldes->getSoma()/(i+1)));
            }
            return valor;
        }

        //Calcula qual deve ser o index de um no na tabela baseando-se no tamanho da tabela e o numero de colisoes que já ocorreram com esse no
        unsigned int hash(No* no, unsigned int colisions, unsigned int h1, unsigned int h2) {
            double val = calculaValorNo(no);
            std::ostringstream oss;
            oss << std::fixed << val; // Convert to string without scientific notation
            oss << colisions; // Append collision count

            std::hash<std::string> str_hash;
            unsigned int hash = str_hash(oss.str());

            return hash % h1;
        }

        /* unsigned int hash(No* no, unsigned int colisions, unsigned int h1, unsigned int h2) {
            double val = calculaValorNo(no);

            // Convert val to an unsigned long long int
            unsigned long long int val_int = static_cast<unsigned long long int>(val);

            // Combine val and colisions using bitwise XOR
            unsigned long long int combined = val_int ^ colisions;

            unsigned int hash = combined % h1;

            return hash;
        } */




    public:

        //construtor
        HashNo()
        {
            nInsercoes = 0;
            
            tamanhoTabela = find_closest_prime(94967295);
            valorAuxiliar = 2*tamanhoTabela/9;
            hashTable = new std::vector<No*>(tamanhoTabela);
            substituidos = new std::vector<No*>(1000);
            No* null = nullptr;
            std::fill(hashTable->begin(), hashTable->end(), null);
        }

        //destrutor
        ~HashNo()
        {
            for(unsigned int i = 0; i < tamanhoTabela; i++)
            {
                if(hashTable->at(i)!=nullptr)
                    delete hashTable->at(i);
            }
            for(unsigned int i = 0; i < substituidos->size(); i++)
            {
                if(substituidos->at(i)!=nullptr)
                    delete substituidos->at(i);
            }
            delete hashTable;
            delete substituidos;
        }

        //tenta inserir um nó na tabela
        //true-> inseriu  false->repetido
        bool inserirNo(No* no)
        {
            bool finalizado = false;
            unsigned int colisoes = 0;
            

            unsigned int index;

            while (!finalizado)
            {
                index = hash(no,colisoes,tamanhoTabela,valorAuxiliar);

                if (hashTable->at(index)==nullptr)
                {
                    hashTable->at(index) = no;
                    nInsercoes++;
                    return true;
                }
                else if(hashTable->at(index)->getBaldes()->isEqualTo(no->getBaldes()))
                {
                    if(hashTable->at(index)->getProfundidade()>no->getProfundidade())
                    {
                        No* noAntigo = hashTable->at(index);
                        hashTable->at(index) = no;

                        substituidos->push_back(noAntigo);

                        return true;
                    }
                        
                    return false;
                }
                else
                {
                    if(colisoes>no->getBaldes()->getNBaldes()*10)
                        std::cout<<"muita colisao, bro\n";
                    
                    /* std::cout<<"\ncollisao - index "<<index<<"\n";
                    no->getBaldes()->print();
                    hashTable->at(index)->getBaldes()->print();
                    std::cout<<"\n"; */


                    colisoes++;
                    colisoesTotais++;
                    continue;
                }
            }
        return false;
    }

    //printa todos os indexes que foram inseridos na tabela (pra que alguem usaria isso?)
    void printAllIndex()
    {
        unsigned int n = 0;
        for(unsigned int i = 0; i < tamanhoTabela; i++)
        {
            if(hashTable->at(i) != nullptr)
            {
                std::cout << i << "\n";
                n++;
            }
                
        }
        std::cout<<n<<"\n"; 
    }

    //printa o total de insercoes e colisoes que ocorreram na tabela                 

    void printStats()
    {
        std::cout<<"Insercoes "<<nInsercoes<<"\n";
        std::cout<<"Colisoes "<<colisoesTotais<<"\n";
    }
};


#endif

