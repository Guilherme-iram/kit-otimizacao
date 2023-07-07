#include "Solution.h"


namespace ILS
{
    struct InsertionInfo
    {
        int noInserido;
        int arestaRemovida;
        double deltaCusto;
    };

    class Solver
    {
        public:
            Solution bestSolution;
            
            Solver();
            std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL);
            Solution Construction(double** matrizAdj, int* dim);
    };    
}

