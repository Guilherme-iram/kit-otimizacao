#include "ILS.h"
#include "Solution.h"
#include <cstdlib>
#include <ctime>

using namespace ILS;

std::vector<InsertionInfo> Solver::calcularCustoInsercao(Solution& s, std::vector<int>& CL)
{
    std::vector<InsertionInfo> custoInsercao = std::vector<InsertionInfo>((s.sequencia.size() - 1) * CL.size());
    int l = 0;
    
    for(int a = 0; a < s.sequencia.size() - 1; a++)
    {
    
    int i = s.sequencia[a];
    int j = s.sequencia[a + 1];
    
    for (auto k : CL)
        {
            custoInsercao[l].deltaCusto = s.matrizDistancias[i][k] + s.matrizDistancias[j][k] - s.matrizDistancias[i][j];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }

    return custoInsercao;
}

Solution Solver::Construction(double** matrizAdj, int* dim)
{
    srand(time(0));
    Solution s = Solution();

    std::vector<int> sequencia = {1, 1};
    std::vector<int> clients = std::vector<int>(*dim - 2);
    
    for (int i = 2; i < *dim; i++)
    {   
        clients[i - 2] = i;
    }

    
    int random_index;
    int size_clients = clients.size();
    
    // Escolha aleatoria de 3 cidades para visita
    for (int i = 0; i < 3; i++)
    {
        random_index = rand() % size_clients;
        sequencia.insert(sequencia.begin() + (i + 1), clients[random_index]);
        clients.erase(clients.begin() + random_index--);
    }

    /*
    while(!clients.empty()) 
    {
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, clients);
        // ordenarEmOrdemCrescente(custoInsercao);
        // double alpha = (double) rand() / RAND_MAX;
        // int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        // inserirNaSolucao(s, custoInsercao[selecionado].k);
    }
    */


    s.sequencia = sequencia;
    s.matrizDistancias = matrizAdj;
    s.calculaFO();
    s.print();

    return s;
}

Solver::Solver()
{

}
