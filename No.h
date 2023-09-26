#include "Baldes.h"

class No
{
    private:
        Baldes* baldes;
        No* pai;
        int profundidade = 0;

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
        No(int nBaldes)
        {
            baldes = new Baldes(nBaldes);
            pai = nullptr;
            profundidade = 0;
        }
        int getProfundidade(){
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
};