#pragma once  // первый вариант защиты от повторного включения

#ifndef Matrix_h  // второй вариант защиты от повторного включения
#define Matrix_h

#include <iostream>
#include <string>

class Matrix {
   private:
    int nMatrR;
    int nMatrC;
    bool bFull;
    double** matr;

   public:
    enum class TypeSide { NONE, Row, Col, Both };

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
    void Delete(int nPoint = 0);
    void Clear();
    bool Empty() const { return matr == nullptr; }

    Matrix::Errors AddDim(TypeSide side, int rowCount = 0, int colCount = 0);
    Matrix::Errors Assign(const Matrix* source);
    Matrix::Errors Copy(const Matrix* source, Matrix* destination) const;
    Matrix::Errors Insert(TypeSide side, int index = 0, int count = 1);
    bool IsFull() const { return bFull; }
    Matrix::Errors NewSize(int newRows, int newCols);
    Matrix::Errors Transpose();

    std::string FormatMatrixToString(
        std::streamsize nSetW = 10, std::streamsize nSetPrecision = 0,
        const std::string& sDivider = "\n",
        std::ios_base::fmtflags flags =
            std::ios_base::fixed) const;  // right и dec
    bool PrintToFile(const std::string& filename) const;

    int GetRows() const { return nMatrR; }
    int GetCols() const { return nMatrC; }

    double* operator[](int index) { return matr[index]; }
    const double* operator[](int index) const { return matr[index]; }
};

#endif