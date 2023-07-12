#include "ILS.h"
#include "Solution.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>


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

    std::cout << "Sequencia inicial: " << std::endl;
    for (int i = 0; i < 2; i++)
    {
        std::cout << sequencia[i] << " -> ";
    }
    std::cout << sequencia[2] << std::endl;
    
    while(!clients.empty()) 
    {
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, clients);

        //  ordena do menor para o maior delta custo (nao crescente)
        std::sort(custoInsercao.begin(), custoInsercao.end(), [](const InsertionInfo& a, const InsertionInfo& b) {
            return a.deltaCusto < b.deltaCusto;
        });

        // escolhe um alpha aleatorio entre 0 e 1
        // 0 total guloso
        // 1 total aleatorio
        double alpha = (double) rand() / RAND_MAX;

        // faz a escolha do candidato selecionado com base no alpha 
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));

        // insere o candidato selecionado na sequencia
        sequencia.insert(sequencia.begin() + (custoInsercao[selecionado].arestaRemovida + 1), custoInsercao[selecionado].noInserido);
        
        // remove o cliente da lista de clientes
        clients.erase(std::find(clients.begin(), clients.end(), custoInsercao[selecionado].noInserido));
    }
    
    std::cout << "Sequencia final: " << std::endl;
    s.sequencia = sequencia;
    s.matrizDistancias = matrizAdj;
    s.calculaFO();
    s.print();

    return s;
}

Solver::Solver()
{

}
