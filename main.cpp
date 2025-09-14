#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
    Matrix mat(3, 4, "testing matr");
    for (int i = 0; i < mat.GetRows(); i++) {
		for (int j = 0; j < mat.GetCols(); j++) {
			mat[i][j] = i * 4 + j + 1;
		}
	 }
    
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
	 
	 newMatr.Delete();
	 newMatr.Print();
    
    return 0;
}
