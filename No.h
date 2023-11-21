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
            std::vector<No*> caminho;  // Usaremos um vetor para armazenar os nós do caminho

            No* atual = this;

            do
            {
                caminho.push_back(atual);
                atual = atual->pai;
            } while (atual != nullptr);

            // Agora, imprimimos os valores em ordem inversa
            for (int i = caminho.size() - 1; i >= 0; --i)
            {
                caminho[i]->getBaldes()->print();
                //std::cout << "-v-\n";
            }
        }

};


#endif