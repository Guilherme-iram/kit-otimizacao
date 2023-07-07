#include <iostream>
#include "readData.h"
#include "Solution.h"
#include "ILS.h"

using namespace std;
using namespace ILS;

int main(int argc, char* argv[]) {

    int dim; 
    double **matrizAdj;

    readData(argc, argv, &dim, &matrizAdj);

    Solver solve = Solver();
    Solution s = solve.Construction(matrizAdj, &dim);

    return 0;    
}
