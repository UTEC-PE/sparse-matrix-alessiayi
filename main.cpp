
#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> M(5, 5);
    M.set(0, 0, 3);
    M.oPrint();

    //system("PAUSE");
    return EXIT_SUCCESS;
}
