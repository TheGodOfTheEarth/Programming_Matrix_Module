#include "Matrix.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>

Matrix::Matrix() {
    nMatrR = 0;
    nMatrC = 0;
    bFull = false;
    matr = nullptr;
}

Matrix::Matrix(int rows, int cols) {
    nMatrR = rows;
    nMatrC = cols;
    bFull = false;
    matr = nullptr;
    Create(rows, cols);
}

Matrix::~Matrix() { Delete(); }

void Matrix::Clear() {
    if (matr == nullptr) return;
    for (int i = 0; i < nMatrR; i++) {
        for (int j = 0; j < nMatrC; j++) {
            matr[i][j] = 0;
        }
    }
    bFull = false;
}

Matrix::Errors Matrix::Create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return Errors::invalid_size;
    }

    if (matr != nullptr) {
        Delete();
    }

    matr = new (std::nothrow) double*[rows];
    if (matr == nullptr) {
        delete[] matr;
        nMatrR = 0;
        nMatrC = 0;
        bFull = false;

        return Errors::bad_alloc;
    }

    for (int i = 0; i < rows; i++) {
        matr[i] = new (std::nothrow) double[cols]{};
        if (matr[i] == nullptr) {
            PrivateDelete(i);  // i - 1
            return Errors::bad_alloc;
        }
    }

    nMatrR = rows;
    nMatrC = cols;
    bFull = false;

    return Errors::success;
}

void Matrix::Delete() {
    if (matr != nullptr) {
        // for (int i = 0; i < nMatrR; i++) {
        //     if (matr[i] != nullptr) {
        //         delete[] matr[i];
        //     }
        // }
        delete[] matr;
        matr = nullptr;
    }
    nMatrR = 0;
    nMatrC = 0;
    bFull = false;
}

void Matrix::PrivateDelete(int nPoint) {
    for (int i = 0; i < nPoint; i++) {
        if (matr[i] != nullptr) {
            delete[] matr[i];
        }
    }
    delete[] matr;
    matr = nullptr;

    nMatrR = 0;
    nMatrC = 0;
    bFull = false;
}

Matrix::Errors Matrix::AddDim(TypeSide side, int rowCount, int colCount) {
    if (rowCount == 0 && colCount == 0) return Errors::invalid_argument;

    Matrix newMatrix;

    switch (side) {
        case TypeSide::Row:
            if (newMatrix.Create(nMatrR + rowCount, nMatrC) != Errors::success)
                return Errors::bad_create;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;

        case TypeSide::Col:
            if (newMatrix.Create(nMatrR, nMatrC + colCount) != Errors::success)
                return Errors::bad_create;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;

        case TypeSide::Both:
            if (newMatrix.Create(nMatrR + rowCount, nMatrC + colCount) !=
                Errors::success)
                return Errors::bad_create;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;

        default:
            return Errors::invalid_typeside;
    }

    Delete();
    matr = newMatrix.matr;
    nMatrR = newMatrix.nMatrR;
    nMatrC = newMatrix.nMatrC;
    bFull = newMatrix.bFull;

    newMatrix.matr = nullptr;
    newMatrix.nMatrR = 0;
    newMatrix.nMatrC = 0;

    return Errors::success;
}

Matrix::Errors Matrix::Transpose() {
    if (matr == nullptr || nMatrR <= 0 || nMatrC <= 0) {
        return Errors::invalid_size;
    }

    Matrix tempMatrix;
    if (tempMatrix.Create(nMatrC, nMatrR) != Errors::success) {
        return Errors::bad_create;
    }

    for (int r = 0; r < nMatrR; r++) {
        for (int c = 0; c < nMatrC; c++) {
            tempMatrix.matr[c][r] = matr[r][c];
        }
    }

    Delete();
    matr = tempMatrix.matr;
    nMatrR = tempMatrix.nMatrR;
    nMatrC = tempMatrix.nMatrC;

    tempMatrix.matr = nullptr;

    return Errors::success;
}

Matrix::Errors Matrix::Copy(const Matrix* source, Matrix* destination) const {
    if (source == nullptr || destination == nullptr) {
        return Errors::invalid_ptr;
    }

    if (destination->nMatrR != source->nMatrR ||
        destination->nMatrC != source->nMatrC) {
        if (destination->Create(source->nMatrR, source->nMatrC) !=
            Errors::success) {
            return Errors::bad_create;
        }
    } else {
        destination->Clear();
    }

    for (int r = 0; r < source->nMatrR; r++) {
        for (int c = 0; c < source->nMatrC; c++) {
            destination->matr[r][c] = source->matr[r][c];
        }
    }

    destination->bFull = source->bFull;

    return Errors::success;
}

Matrix::Errors Matrix::Insert(TypeSide side, int index, int count) {
    if (count <= 0) return Errors::invalid_argument;
    if (index < 0) index = 0;

    Matrix tempMatrix;
    if (Copy(this, &tempMatrix) != Errors::success) {
        return Errors::bad_create;
    }

    switch (side) {
        case TypeSide::Row:
            if (index > nMatrR) index = nMatrR;
            if (Create(nMatrR + count, nMatrC) != Errors::success)
                return Errors::bad_create;

            for (int r = 0; r < index; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    matr[r][c] = tempMatrix.matr[r][c];
                }
            }

            for (int r = index; r < index + count; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    matr[r][c] = 0;
                }
            }

            for (int r = index + count; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    matr[r][c] = tempMatrix.matr[r - count][c];
                }
            }
            break;

        case TypeSide::Col:
            if (index > nMatrC) index = nMatrC;
            if (Create(nMatrR, nMatrC + count) != Errors::success)
                return Errors::bad_create;

            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < index; c++) {
                    matr[r][c] = tempMatrix.matr[r][c];
                }

                for (int c = index; c < index + count; c++) {
                    matr[r][c] = 0;
                }

                for (int c = index + count; c < nMatrC; c++) {
                    matr[r][c] = tempMatrix.matr[r][c - count];
                }
            }
            break;

        default:
            return Errors::invalid_typeside;
    }

    return Errors::success;
}

Matrix::Errors Matrix::Assign(const Matrix* source) {
    if (source == nullptr) return Errors::bad_create;

    if (matr != nullptr) {
        Delete();
    }

    if (Create(source->nMatrR, source->nMatrC) != Errors::success) {
        return Errors::bad_create;
    }

    for (int r = 0; r < nMatrR; r++) {
        for (int c = 0; c < nMatrC; c++) {
            matr[r][c] = source->matr[r][c];
        }
    }

    bFull = source->bFull;

    return Errors::success;
}

Matrix::Errors Matrix::NewSize(int newRows, int newCols) {
    Matrix tempMatrix;
    if (Copy(this, &tempMatrix) != Errors::success) {
        return Errors::bad_create;
    }

    if (Create(newRows, newCols) != Errors::success) {
        return Errors::bad_create;
    }

    int copyRows = (newRows < tempMatrix.nMatrR) ? newRows : tempMatrix.nMatrR;
    int copyCols = (newCols < tempMatrix.nMatrC) ? newCols : tempMatrix.nMatrC;

    for (int r = 0; r < copyRows; r++) {
        for (int c = 0; c < copyCols; c++) {
            matr[r][c] = tempMatrix.matr[r][c];
        }
    }

    return Errors::success;
}

std::string Matrix::FormatMatrixToString(std::streamsize nSetW,
                                         std::streamsize nSetPrecision,
                                         const std::string& sDivider,
                                         TypeOutput type) const {
    std::stringstream ss;

    switch (type) {
        case TypeOutput::fixed:
        case TypeOutput::f:
            ss << std::fixed;
            break;
        case TypeOutput::scientific:
        case TypeOutput::s:
            ss << std::scientific;
            break;
        case TypeOutput::defaultfloat:
        case TypeOutput::d:
            ss << std::defaultfloat;
            break;
    }

    for (int r = 0; r < nMatrR; r++) {
        for (int c = 0; c < nMatrC; c++) {
            ss << std::setw(nSetW) << std::setprecision(nSetPrecision)
               << matr[r][c];
        }
        ss << sDivider;
    }

    return ss.str();
}

bool Matrix::PrintToFile(const std::string& filename) const {
    if (Empty()) {
        return false;
    }

    if (filename.empty()) {
        return false;
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << FormatMatrixToString();
    file.close();

    return true;
}