#include <iostream>
#include "readData.h"
#include "Solution.h"
#include "ILS.h"
#include "Neighborhood.h"

using namespace std;
using namespace ILS;

int main(int argc, char* argv[]) {

    int dim; 
    double **matrizAdj;

    readData(argc, argv, &dim, &matrizAdj);

    Solver solve = Solver();

    Solution s = solve.Construction(matrizAdj, &dim);
    
    LocalSearch ls = LocalSearch();
    ls.run(&s);

    s.print();

    std::cout << "Apos recalcular FO: " << std::endl;
    s.calculaFO();
    s.print();
    return 0;    
}
