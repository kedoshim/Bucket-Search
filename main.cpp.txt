// #include "Baldes.h"
#include "BuscaIrrevogavel.h"
#include "BuscaBacktracking.h"
#include "BuscaEmLargura.h"
#include "BuscaEmProfundidade.h"
#include <sstream>

using namespace std;

int main()
{

    cout << "A: 3 litros    B: 5 litros\n\n";
    cout << "Regras de Transicao:\n\n";
    cout << "1. Esvazia balde A\n";
    cout << "2. Esvazia balde B\n";
    cout << "3. Enche balde A\n";
    cout << "4. Enche balde B\n";
    cout << "5. Passa agua de A para B\n";
    cout << "6. Passa agua de B para A\n";

    string ordem;
    cout << "\nQual sera a ordem de aplicacao das regras?\n";
    cout << "(separe os indices por espacos)\n";
    getline(cin, ordem);

    int ordemRegras[6];
    int i = 0;

    // Transforma a string 'ordem' em um vetor de int 'ordemRegras'
    stringstream ss(ordem);
    string word;
    while (ss >> word && i < 6)
    {
        ordemRegras[i] = std::stoi(word);
        i++;
    }

    BuscaIrrevogavel(ordemRegras);

    return 0;
}