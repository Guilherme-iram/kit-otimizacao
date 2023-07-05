#include "Solution.h"

using namespace ILS;

void Solution::print()
{   
    std::cout << "Solucao: " << std::endl;
    int size = this->sequencia.size();

    for (int i = 0; i < size- 1; i++)
    {
        std::cout << this->sequencia[i] << " -> ";
    }
    std::cout << this->sequencia[size - 1] << std::endl;

    std::cout << "FO: " << this->custoSolucao << std::endl;
}

void Solution::calculaFO()
{
    this->custoSolucao = 0;

    for (int i = 0; i < this->sequencia.size() - 1; i++)
    {
        this->custoSolucao  += this->matrizDistancias[this->sequencia[i]][this->sequencia[i + 1]];
    }
}

Solution::Solution (double** matrizDistancias, std::vector<int> clients): sequencia(clients), matrizDistancias(matrizDistancias)
{
}