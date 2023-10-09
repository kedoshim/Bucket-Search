#ifndef NO_H
#define MO_H


#include "Baldes.h"

class No
{
    private:

        Baldes* baldes;
        No* pai;
        unsigned int profundidade = 0; 

    public:
        No()
        {
            baldes = new Baldes();
            pai = nullptr;
            profundidade = 0;
        }
        No(No* noPai, Baldes* balde)
        {
            pai = noPai;
            baldes = balde;
            profundidade = noPai->getProfundidade()+1;

        }
        No(unsigned int nBaldes)
        {
            baldes = new Baldes(nBaldes);
            pai = nullptr;
            profundidade = 0;
        }
        ~No()
        {
            delete  baldes;
        }
        unsigned int getProfundidade(){
            return profundidade;
        }
    
        Baldes* getBaldes()
        {
            return baldes;
        }

        No* getPai()
        {
            return pai;
        }

        //Checa se esse nó é único em seu caminho
        bool checkUnico()
        {
            No* atual=this;
            No* noPai = pai;
            while(noPai!=nullptr)
            {
                if(atual->getBaldes()->isEqualTo(noPai->getBaldes()))
                    return false;
                else
                    noPai=noPai->getPai();
            }
            return true;
        } 
        void printCaminhoSolucao()
        {
            No* atual=this;

            do
            {
                atual->getBaldes()->print();
                //std::cout<<"-v-\n";
                atual = atual->pai;
                
            }while(atual->pai!=nullptr);

            atual->getBaldes()->print();
        }
};


#endif