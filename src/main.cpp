#include <iostream>
#include "readData.h"
#include "Solution.h"


using namespace std;
using namespace ILS;

int main(int argc, char* argv[]) {

    int dim; 
    double **matrizAdj;

    readData(argc, argv, &dim, &matrizAdj);

    cout << "Dimensao: " << dim << endl;
    cout << "-----------" << endl;
    cout << "Matriz de adjacencia: " << endl;

    for(int i = 1; i < dim; i++) {
        for(int j = 1; j < dim; j++) {
            cout << matrizAdj[i][j] << " ";
        }
        cout << endl;
    }

    vector<int> auxClientss = {1, 16, 1};
    Solution solucao = Solution(matrizAdj, auxClientss);
    solucao.calculaFO();
    solucao.print();

    return 0;    
}
