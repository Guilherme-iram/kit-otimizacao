#pragma once
#include "Solution.h"

namespace ILS
{

    class LocalSearch
    {
        public:
            void run(Solution* s);
            LocalSearch();
    };

    class Swap
    {
        public:
            int besti;
            int bestj;
            double bestDeltaCusto;
            bool run(Solution* s);
            void calCost(Solution* s);
            void movement(Solution* s, int i, int j, double deltaCusto);
            Swap();
    };

    class TwoOpt
    {
        public:
            int besti;
            int bestj;
            double bestDeltaCusto;
            bool run(Solution* s);
            void calCost(Solution* s);
            void movement(Solution* s, int i, int j, double deltaCusto);
            TwoOpt();
    };

    class Reinsertion
    {
        public:
            int besti;
            int bestj;
            double bestDeltaCusto;
            bool run(Solution* s);
            void calCost(Solution* s);
            void movement(Solution* s, int i, int j, double deltaCusto);
            Reinsertion();
    };
    
}