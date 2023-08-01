#include "Neighborhood.h"

using namespace ILS;

LocalSearch::LocalSearch()
{
}

void LocalSearch::run(Solution* s)
{
    std::vector<int> neighbors = {1, 2};
    bool improve = false;
    
    Swap swap = Swap();
    TwoOpt twoOpt = TwoOpt();

    while (neighbors.empty() == false)
    {
        int i = rand() % neighbors.size();

        switch (neighbors[i])
        {
        case 1:
            improve = swap.run(s);
            break;
        
        case 2:
            improve = twoOpt.run(s);
            break;


        default:
            break;
        }

        if (improve == true)
        {
            // std::cout << "Melhorou! " << std::endl;
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
    // std::cout << "MELHOR DELTA Swap:" << deltaCusto << std::endl;

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

    for (int size = 1; size < 4; size++)
    {
        for (int i = 1; i < s->sequencia.size() - 2; i++)
        {
        for (int j = i + size + 1; j < s->sequencia.size() - 1; j ++)
            {
                deltaCost = 0;

                deltaCost -= s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[i]];
                deltaCost -= s->matrizDistancias[s->sequencia[j]][s->sequencia[j + 1]];

                deltaCost += s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[j]];
                deltaCost += s->matrizDistancias[s->sequencia[i]][s->sequencia[j + 1]];

                if (deltaCost < this->bestDeltaCusto)
                {   
                    this->besti = i;
                    this->bestj = j;        
                    this->bestDeltaCusto = deltaCost;
                }
            }
        }
    }
}

void TwoOpt::movement(Solution* s, int i, int j, double deltaCusto)
{   
    std::cout << "MELHOR DELTA 2-OPT:" << deltaCusto << std::endl;

    int startIndex = i; // Início do intervalo a ser invertido
    int endIndex = j;  // Fim do intervalo a ser invertido

    while (startIndex < endIndex) {
        int temp = s->sequencia[startIndex];
        s->sequencia[startIndex] = s->sequencia[endIndex];
        s->sequencia[endIndex] = temp;
        startIndex++;
        endIndex--;
    }


    s->custoSolucao += deltaCusto;
}

bool TwoOpt::run(Solution* s)
{
    this->calCost(s);
    if (this->bestDeltaCusto < 0)
    {
        this->movement(s, this->besti, this->bestj, this->bestDeltaCusto);
        return true;
    }

    return false;
}



Reinsertion::Reinsertion()
{
    this->besti = 0;
    this->bestj = 0;
    this->bestDeltaCusto = 0.0;
}

void Reinsertion::calCost(Solution* s)
{
    double deltaCost;
    this->bestDeltaCusto = 0.0;

    for (int i = 1; i < s->sequencia.size() - 2; i++)
    {
    for (int j = i + 1; j < s->sequencia.size() - 1; j ++)
        {
            deltaCost = 0;

            deltaCost -= s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[i]];
            deltaCost -= s->matrizDistancias[s->sequencia[i]][s->sequencia[i + 1]];
            deltaCost -= s->matrizDistancias[s->sequencia[j]][s->sequencia[j + 1]];

            deltaCost += s->matrizDistancias[s->sequencia[i - 1]][s->sequencia[i + 1]];
            deltaCost += s->matrizDistancias[s->sequencia[j]][s->sequencia[i]];
            deltaCost += s->matrizDistancias[s->sequencia[i]][s->sequencia[j + 1]];

            if (deltaCost < this->bestDeltaCusto)
            {   
                this->besti = i;
                this->bestj = j;
                this->bestDeltaCusto = deltaCost;
            }
        }
    }
    
}

void Reinsertion::movement(Solution* s, int i, int j, double deltaCusto)
{   
    std::cout << "MELHOR DELTA Reinsertion:" << deltaCusto << std::endl;

    int startIndex = i; // Início do intervalo a ser invertido
    int endIndex = j;  // Fim do intervalo a ser invertido

    while (startIndex < endIndex) {
        int temp = s->sequencia[startIndex];
        s->sequencia[startIndex] = s->sequencia[endIndex];
        s->sequencia[endIndex] = temp;
        startIndex++;
        endIndex--;
    }

    s->custoSolucao += deltaCusto;
}

bool Reinsertion::run(Solution* s)
{
    this->calCost(s);
    if (this->bestDeltaCusto < 0)
    {
        this->movement(s, this->besti, this->bestj, this->bestDeltaCusto);
        return true;
    }

    return false;
}
