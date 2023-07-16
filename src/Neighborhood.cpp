#include "Neighborhood.h"

using namespace ILS;

LocalSearch::LocalSearch()
{
}

void LocalSearch::run(Solution* s)
{
    std::vector<int> neighbors = {1};
    bool improve = false;
    
    Swap swap = Swap();

    while (neighbors.empty() == false)
    {
        int i = rand() % neighbors.size();

        switch (neighbors[i])
        {
        case 1:
            improve = swap.run(s);
            break;
        
        default:
            break;
        }

        if (improve == true)
        {
            std::cout << "Melhorou! " << std::endl;
            neighbors = {1};
        }
        else
        {
            neighbors.erase(neighbors.begin() + i);
        }
    }

}

Swap::Swap()
{
    this->besti = 0;
    this->bestj = 0;
    this->bestDeltaCusto = 0.0;
}

void Swap::calCost(Solution* s)
{
    double deltaCost;
    this->bestDeltaCusto = 0.0;
    
    for (int i = 1; i < s->sequencia.size() - 1; i++)
    {
        for (int j = i + 1; j < s->sequencia.size() - 1; j ++)
        {
            deltaCost = 0;

            if (i + 1 == j)
            {
                deltaCost -= s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[i]];
                deltaCost -= s->matrizDistancias[s->sequencia[i]][s->sequencia[j]];
                deltaCost -= s->matrizDistancias[s->sequencia[j]][s->sequencia[j + 1]];

                deltaCost += s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[j]];
                deltaCost += s->matrizDistancias[s->sequencia[j]][s->sequencia[i]];
                deltaCost += s->matrizDistancias[s->sequencia[i]][s->sequencia[j + 1]];
            }
            else
            {
                deltaCost -= s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[i]];
                deltaCost -= s->matrizDistancias[s->sequencia[i]][s->sequencia[i + 1]];
                deltaCost -= s->matrizDistancias[s->sequencia[j - 1]][s->sequencia[j]];
                deltaCost -= s->matrizDistancias[s->sequencia[j]][s->sequencia[j + 1]];

                deltaCost += s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[j]];
                deltaCost += s->matrizDistancias[s->sequencia[j]][s->sequencia[i + 1]];
                deltaCost += s->matrizDistancias[s->sequencia[j - 1]][s->sequencia[i]];
                deltaCost += s->matrizDistancias[s->sequencia[i]][s->sequencia[j + 1]];
            }
            // std::cout << "Delta cost i j => " << i << " " << j << " " << deltaCost << std::endl;

            if (deltaCost < this->bestDeltaCusto)
            {
                this->besti = i;
                this->bestj = j;
                this->bestDeltaCusto = deltaCost;
            }

        }
    }

    
}

void Swap::movement(Solution* s, int i, int j, double deltaCusto)
{   
    std::cout << "MELHOR DELTA:" << deltaCusto << std::endl;

    int aux = s->sequencia[i];
    s->sequencia[i] = s->sequencia[j];
    s->sequencia[j] = aux;
    s->custoSolucao += deltaCusto;
}

bool Swap::run(Solution* s)
{
    this->calCost(s);
    if (this->bestDeltaCusto < 0)
    {
        this->movement(s, this->besti, this->bestj, this->bestDeltaCusto);
        return true;
    }

    return false;
    
}

/* 
TwoOpt::TwoOpt()
{
    this->besti = 0;
    this->bestj = 0;
    this->bestDeltaCusto = 0.0;
}

void TwoOpt::calCost(Solution* s)
{
    double deltaCost;
    this->bestDeltaCusto = 0.0;

    for (int i = 1; i < s->sequencia.size() - 2; i++)
    {
        for (int j = i + 1; j < s->sequencia.size() - 1; j ++)
        {

        }
    }

}
*/