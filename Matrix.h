#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

class Matrix {
private:
    std::string sTitle;
    int nMatrR;
    int nMatrC;
    bool bFull;
    double** matr;

    std::string FormatMatrixToString() const;

public:
    enum class TypeSide {
        NONE,
        Row,
        Col,
        Both
    };

    Matrix();
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, const std::string& title);
    ~Matrix();

    void Clear();
    int Create(int rows, int cols);
    int Create();
    void Delete();
    bool Empty() const { return matr == nullptr; }

    int AddDim(TypeSide side, int rowCount = 0, int colCount = 0);
    int Assign(const Matrix* source);
    int Copy(const Matrix* source, Matrix* destination) const;
    int DeleteDim(TypeSide side, int index = -1);
    Matrix Double() const;
    int Insert(TypeSide side, int index = 0, int count = 1);
    bool IsFull() const { return bFull; }
    int NewSize(int newRows, int newCols);
    int Transpose();

    void Print() const;
    std::string ToString() const;
    bool PrintToFile(const std::string& filename) const;
    
    int GetRows() const { return nMatrR; }
    int GetCols() const { return nMatrC; }
    const std::string& GetTitle() const { return sTitle; }
    void SetTitle(const std::string& title) { sTitle = title; }
    
    double* operator[](int index) { return matr[index]; }
    const double* operator[](int index) const { return matr[index]; }
};