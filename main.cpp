#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
    Matrix mat(2, 3, "testing matr");
    mat[0][0] = 1.5; mat[0][1] = 2.3; mat[0][2] = 3.7;
    mat[1][0] = 4.1; mat[1][1] = 5.9; mat[1][2] = 6.2;
    
    cout << "=== console output ===" << endl;
    mat.Print();
    
    cout << "=== string output ===" << endl;
    string matrixString = mat.ToString();
    cout << "string representaion:\n" << matrixString << endl;
    
    cout << "=== file writing ===" << endl;
    if (mat.PrintToFile("matrix_output.txt")) {
        cout << "matrix has been successfully written to 'matrix_output.txt'" << endl;
    } else {
        cerr << "file writing error" << endl;
    }
    
    Matrix emptyMat;
    cout << "=== empty matrix ===" << endl;
    emptyMat.Print();
    cout << "string: " << emptyMat.ToString() << endl;

	 cout << endl << endl;

	 Matrix newMatr;
	 mat.Copy(&mat, &newMatr);
	 newMatr.Print();
    
    return 0;
}
