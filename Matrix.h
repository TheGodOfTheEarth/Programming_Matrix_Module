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

    void PrivateDelete(int nPoint);

   public:
    enum class TypeSide { NONE, Row, Col, Both };

    enum class TypeOutput { fixed, scientific, defaultfloat };

    enum class Errors {
        success = 0,
        bad_alloc = 1,
        invalid_argument = 2,
        invalid_size = 3,
        bad_create = 4,
        invalid_typeside = 5,
        invalid_ptr = 6
    };

    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();

    Matrix::Errors Create(int rows, int cols);
    void Delete();
    void Clear();
    bool Empty() const { return matr == nullptr; }

    Matrix::Errors AddDim(TypeSide side, int rowCount = 0, int colCount = 0);
    Matrix::Errors Assign(const Matrix* source);
    Matrix::Errors Copy(const Matrix* source, Matrix* destination) const;
    Matrix::Errors DeleteDim(TypeSide side, int index = -1);
    Matrix::Errors Insert(TypeSide side, int index = 0, int count = 1);
    bool IsFull() const { return bFull; }
    Matrix::Errors NewSize(int newRows, int newCols);
    Matrix::Errors Transpose();

    std::string FormatMatrixToString(int nSetW = 10, int nSetPrecision = 0,
                                     std::string sDivider = "\n",
                                     TypeOutput type = TypeOutput::fixed) const;
    bool PrintToFile(const std::string& filename) const;

    int GetRows() const { return nMatrR; }
    int GetCols() const { return nMatrC; }

    double* operator[](int index) { return matr[index]; }
    const double* operator[](int index) const { return matr[index]; }
};