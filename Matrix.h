#pragma once
// #ifndef Matrix_h
// #define Matrix_h
#include <string>


class Matrix {
private:
    int nMatrR;
    int nMatrC;
    bool bFull;
    double** matr;


public:
    enum class TypeSide {
        NONE,
        Row,
        Col,
        Both
    };

	 enum class TypeOutput {
        fixed,
        scientific,
        defaultfloat
    };
	 

    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();

    int Create(int rows, int cols);
    void Delete();
    void Clear();
    bool Empty() const { return matr == nullptr; }

    int AddDim(TypeSide side, int rowCount = 0, int colCount = 0);
    int Assign(const Matrix* source);
    int Copy(const Matrix* source, Matrix* destination) const;
    int DeleteDim(TypeSide side, int index = -1);
    int Insert(TypeSide side, int index = 0, int count = 1);
    bool IsFull() const { return bFull; }
    int NewSize(int newRows, int newCols);
    int Transpose();

	 std::string FormatMatrixToString(int nSetW = 10, int nSetPrecision = 0, std::string sDivider = "\n", TypeOutput type = TypeOutput::fixed) const;
    bool PrintToFile(const std::string& filename) const;
    
    int GetRows() const { return nMatrR; }
    int GetCols() const { return nMatrC; }
    
    double* operator[](int index) { return matr[index]; }
    const double* operator[](int index) const { return matr[index]; }
};