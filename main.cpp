#include "Matrix.h"
#include <iostream>

using namespace std;

int main() {
	 // Create Matrix
    Matrix mat(3, 4, "testing matr");

	 // Fill with vals
    for (int i = 0; i < mat.GetRows(); i++) {
		for (int j = 0; j < mat.GetCols(); j++) {
			mat[i][j] = i * mat.GetCols() + j + 1;
		}
	 }
    

    cout << "\n\n" << "=== Initial Matrix ===" << endl;
    mat.Print();


	 // Copy
	 Matrix test;
	 mat.Copy(&mat, &test);
	 cout << "\n\n" << "=== Copied Matrix ===" << endl;
    test.Print();


	 // SetTitle
	 mat.Copy(&mat, &test);
	 test.SetTitle("New title");
	 cout << "\n\n" << "=== Retitled Matrix ===" << endl;
    test.Print();


	 // Clear
	 mat.Copy(&mat, &test);
	 test.Clear();
	 cout << "\n\n" << "=== Cleared Matrix ===" << endl;
    test.Print();


	 // AddDim
	 mat.Copy(&mat, &test);
	 test.AddDim(Matrix::TypeSide::Both, 1, 1);
	 cout << "\n\n" << "=== Matrix with Extra Dim(s) ===" << endl;
    test.Print();


	 // Transposed
	 mat.Copy(&mat, &test);
	 test.Transpose();
	 cout << "\n\n" << "=== Transposed Matrix ===" << endl;
    test.Print();


	 // Insert
	 mat.Copy(&mat, &test);
	 test.Insert(Matrix::TypeSide::Row, 1);
	 cout << "\n\n" << "=== Matrix with Inserted Row(/Col/Both) ===" << endl;
    test.Print();


	 // DeleteDim
	 mat.Copy(&mat, &test);
	 test.DeleteDim(Matrix::TypeSide::Col, 2);
	 cout << "\n\n" << "=== Matrix with Deleted Dim(s) ===" << endl;
    test.Print();


	 // NewSize
	 mat.Copy(&mat, &test);
	 test.NewSize(4, 2);
	 cout << "\n\n" << "=== NewSized Matrix ===" << endl;
    test.Print();


	 // Assigned
	 mat.Copy(&mat, &test);
	 test.Assign(&mat);
	 cout << "\n\n" << "=== Assigned Matrix ===" << endl;
    test.Print();

    
	 // String
    cout << "\n\n" << "=== string output ===" << endl;
    string matrixString = mat.ToString();
    cout << "string representaion:\n" << matrixString << endl;
    

	 // File
    cout << "\n\n" << "=== file writing ===" << endl;
    if (mat.PrintToFile("matrix_output.txt")) {
        cout << "matrix has been successfully written to 'matrix_output.txt'" << endl;
    } else {
        cerr << "file writing error" << endl;
    }
	 
	 
	 // Delete
	 mat.Copy(&mat, &test);
	 test.Delete();
	 cout << "\n\n" << "=== Deleted Matrix ===" << endl;
    test.Print();
    
    return 0;
}
