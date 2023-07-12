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

bool compare(const InsertionInfo& a, const InsertionInfo& b)
{
    return a.deltaCusto < b.deltaCusto;
}

Solution Solver::Construction(double** matrizAdj, int* dim)
{
    srand(time(0));
    
    Solution s = Solution(matrizAdj);

    std::vector<int> clients;

    s.sequencia.push_back(1);

    for (int i = 2; i <= (*dim); i++)
    {   
        clients.push_back(i);
    }

    random_shuffle(clients.begin(), clients.end());

    for (int i = 0; i < 2; i++)
    {
        // adiciona o cliente na sequencia 
        s.sequencia.push_back(clients[i]);

        // remove o cliente da lista de clientes
        clients.erase(std::find(clients.begin(), clients.end(), clients[i]));
    }
    
    s.sequencia.push_back(1);
    // Escolha aleatoria de 3 cidades para visita

    std::cout << "Sequencia inicial: " << std::endl;
    for (int i = 0; i < s.sequencia.size() - 1; i++)
    {
        std::cout << s.sequencia[i] << " -> ";
    }
    std::cout << " 1 " << std::endl;
    
    int cont = 0;
    
    while(!clients.empty()) 
    {

        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, clients);
        //  ordena do menor para o maior delta custo (nao crescente)

        std::sort(custoInsercao.begin(), custoInsercao.end(), compare);

        // escolhe um alpha aleatorio entre 0 e 1
        // 0 total guloso
        // 1 total aleatorio
        double alpha = (double) rand() / RAND_MAX;

        // faz a escolha do candidato selecionado com base no alpha 
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));

        // insere o candidato selecionado na sequencia
        s.sequencia.insert(s.sequencia.begin() + (custoInsercao[selecionado].arestaRemovida + 1), custoInsercao[selecionado].noInserido);
        
        // remove o cliente da lista de clientes
        clients.erase(std::find(clients.begin(), clients.end(), custoInsercao[selecionado].noInserido));
    
    }
    
    std::cout << "Sequencia final: " << std::endl;

    s.calculaFO();
    s.print();

    return s;
}

Solver::Solver()
{

}
