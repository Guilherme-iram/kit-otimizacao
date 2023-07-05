#include <iostream>
#include <vector>

namespace ILS
{
    class Solution
    {
        public:
            std::vector<int> sequencia;
            double custoSolucao;
            double** matrizDistancias;

            void print();
            void calculaFO();
            Solution(double** matrizDistancias, std::vector<int> clients);
    };
}

