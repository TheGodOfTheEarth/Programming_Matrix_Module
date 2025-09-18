#include <iostream>

#include "Matrix.h"

using namespace std;

int main() {
    // Create Matrix
    Matrix mat(3, 4);
    Matrix test;
    string output;

    // Fill with vals
    for (int i = 0; i < mat.GetRows(); i++) {
        for (int j = 0; j < mat.GetCols(); j++) {
            mat[i][j] = i * mat.GetCols() + j + 1;
        }
    }

    cout << "\n\n" << "=== Initial Matrix ===" << endl;
    output = mat.FormatMatrixToString();
    cout << output << endl;

    // Copy
    mat.Copy(&mat, &test);
    cout << "\n\n" << "=== Copied Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // Clear
    mat.Copy(&mat, &test);
    test.Clear();
    cout << "\n\n" << "=== Cleared Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // AddDim
    mat.Copy(&mat, &test);
    test.AddDim(Matrix::TypeSide::Both, 1, 1);
    cout << "\n\n" << "=== Matrix with Extra Dim(s) ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // Transposed
    mat.Copy(&mat, &test);
    test.Transpose();
    cout << "\n\n" << "=== Transposed Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // Insert
    mat.Copy(&mat, &test);
    test.Insert(Matrix::TypeSide::Row, 1);
    cout << "\n\n" << "=== Matrix with Inserted Row(/Col/Both) ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // DeleteDim
    // mat.Copy(&mat, &test);
    // test.DeleteDim(Matrix::TypeSide::Col, 2);
    // cout << "\n\n" << "=== Matrix with Deleted Dim(s) ===" << endl;
    // output = test.FormatMatrixToString();
    // cout << output << endl;

    // NewSize
    mat.Copy(&mat, &test);
    test.NewSize(4, 2);
    cout << "\n\n" << "=== NewSized Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // Assigned
    mat.Copy(&mat, &test);
    test.Assign(&mat);
    cout << "\n\n" << "=== Assigned Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    // String
    cout << "\n\n" << "=== string output ===" << endl;
    cout << "string representaion:\n" << output << endl;

    // File
    cout << "\n\n" << "=== file writing ===" << endl;
    if (mat.PrintToFile("matrix_output.txt")) {
        cout << "matrix has been successfully written to 'matrix_output.txt'"
             << endl;
    } else {
        cerr << "file writing error" << endl;
    }

    // Delete
    mat.Copy(&mat, &test);
    test.Delete();
    cout << "\n\n" << "=== Deleted Matrix ===" << endl;
    output = test.FormatMatrixToString();
    cout << output << endl;

    return 0;
}
