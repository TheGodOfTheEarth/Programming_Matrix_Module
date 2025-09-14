#include "Matrix.h"
#include <stdexcept>

Matrix::Matrix() {
    sTitle = "Матрица";
    nMatrR = 0;
    nMatrC = 0;
    bFull = false;
    matr = nullptr;
}

Matrix::Matrix(int rows, int cols) {
    sTitle = "Матрица";
    nMatrR = rows;
    nMatrC = cols;
    bFull = false;
    matr = nullptr;
    Create(rows, cols);
}

Matrix::Matrix(int rows, int cols, const std::string& title) {
    sTitle = title;
    nMatrR = rows;
    nMatrC = cols;
    bFull = false;
    matr = nullptr;
    Create(rows, cols);
}

Matrix::~Matrix() {
    Delete();
}

void Matrix::Clear() {
    if (matr == nullptr) return;
    for (int i = 0; i < nMatrR; i++) {
        for (int j = 0; j < nMatrC; j++) {
            matr[i][j] = 0;
        }
    }
    bFull = false;
}

int Matrix::Create() {
    if (nMatrR == 0 || nMatrC == 0) {
        return -101;
    }
    return Create(nMatrR, nMatrC);
}

int Matrix::Create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return -101;
    }

    if (matr != nullptr) {
        Delete();
    }

    try {
        matr = new double*[rows];
        for (int i = 0; i < rows; i++) {
            matr[i] = new double[cols]{};
        }
        
        nMatrR = rows;
        nMatrC = cols;
        bFull = false;
        return 0;
    }
    catch (const std::bad_alloc&) {
        return -102; // Ошибка выделения памяти
    }
}

void Matrix::Delete() {
    if (matr != nullptr) {
        for (int i = 0; i < nMatrR; i++) {
            if (matr[i] != nullptr) {
                delete[] matr[i];
                matr[i] = nullptr;
            }
        }
        delete[] matr;
        matr = nullptr;
    }
    nMatrR = 0;
    nMatrC = 0;
    bFull = false;
}

int Matrix::AddDim(TypeSide side, int rowCount, int colCount) {
    if (rowCount == 0 && colCount == 0) return -201;
    
    Matrix newMatrix;
    
    switch (side) {
        case TypeSide::Row:
            if (newMatrix.Create(nMatrR + rowCount, nMatrC) != 0) return -202;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;
            
        case TypeSide::Col:
            if (newMatrix.Create(nMatrR, nMatrC + colCount) != 0) return -202;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;
            
        case TypeSide::Both:
            if (newMatrix.Create(nMatrR + rowCount, nMatrC + colCount) != 0) return -202;
            for (int r = 0; r < nMatrR; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    newMatrix.matr[r][c] = matr[r][c];
                }
            }
            break;
            
        default:
            return -200;
    }
    
    Delete();
    matr = newMatrix.matr;
    nMatrR = newMatrix.nMatrR;
    nMatrC = newMatrix.nMatrC;
    bFull = newMatrix.bFull;
    
    newMatrix.matr = nullptr;
    newMatrix.nMatrR = 0;
    newMatrix.nMatrC = 0;
    
    return 0;
}

int Matrix::Transpose() {
    if (matr == nullptr || nMatrR <= 0 || nMatrC <= 0) {
        return -1;
    }
    
    Matrix tempMatrix(nMatrC, nMatrR);
    
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
    
    return 0;
}

int Matrix::Copy(const Matrix* source, Matrix* destination) const {
    if (source == nullptr || destination == nullptr) {
        return -1;
    }
    
    if (destination->Create(source->nMatrR, source->nMatrC) != 0) {
        return -2;
    }
    
    for (int r = 0; r < source->nMatrR; r++) {
        for (int c = 0; c < source->nMatrC; c++) {
            destination->matr[r][c] = source->matr[r][c];
        }
    }
    
    destination->bFull = source->bFull;
    destination->sTitle = source->sTitle;
    
    return 0;
}

int Matrix::Insert(TypeSide side, int index, int count) {
    if (count <= 0) return -204;
    if (index < 0) index = 0;
    
    Matrix tempMatrix;
    if (Copy(this, &tempMatrix) != 0) {
        return -205;
    }
    
    switch (side) {
        case TypeSide::Row:
            if (index > nMatrR) index = nMatrR;
            if (Create(nMatrR + count, nMatrC) != 0) return -206;
            
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
            if (Create(nMatrR, nMatrC + count) != 0) return -206;
            
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
            return -200;
    }
    
    return 0;
}

// Создание копии матрицы !!! не работает !!!
// Matrix Matrix::Double() const {
//     Matrix result(nMatrR, nMatrC);
//     Copy(this, &result);
//     return result;
// }

// удаление пространства !!! не работает !!!
int Matrix::DeleteDim(TypeSide side, int index) {
    if (index < 0) return -1;
    
    switch (side) {
        case TypeSide::Row:
            if (index >= nMatrR) return -2;
            
            for (int r = index; r < nMatrR - 1; r++) {
                for (int c = 0; c < nMatrC; c++) {
                    matr[r][c] = matr[r + 1][c];
                }
            }
            
            if (Create(nMatrR - 1, nMatrC) != 0) return -3;
            break;
            
        case TypeSide::Col:
            if (index >= nMatrC) return -2;
            
            for (int r = 0; r < nMatrR; r++) {
                for (int c = index; c < nMatrC - 1; c++) {
                    matr[r][c] = matr[r][c + 1];
                }
            }
            
            if (Create(nMatrR, nMatrC - 1) != 0) return -3;
            break;
            
        default:
            return -200;
    }
    
    return 0;
}

// Присвоение матрицы
int Matrix::Assign(const Matrix* source) {
    if (source == nullptr) return -202;
    
    if (matr != nullptr) {
        Delete();
    }
    
    if (Create(source->nMatrR, source->nMatrC) != 0) {
        return -203;
    }
    
    for (int r = 0; r < nMatrR; r++) {
        for (int c = 0; c < nMatrC; c++) {
            matr[r][c] = source->matr[r][c];
        }
    }
    
    bFull = source->bFull;
    sTitle = source->sTitle;
    
    return 0;
}

int Matrix::NewSize(int newRows, int newCols) {
    Matrix tempMatrix;
    if (Copy(this, &tempMatrix) != 0) {
        return -1;
    }
    
    if (Create(newRows, newCols) != 0) {
        return -2;
    }
    
    int copyRows = (newRows < tempMatrix.nMatrR) ? newRows : tempMatrix.nMatrR;
    int copyCols = (newCols < tempMatrix.nMatrC) ? newCols : tempMatrix.nMatrC;
    
    for (int r = 0; r < copyRows; r++) {
        for (int c = 0; c < copyCols; c++) {
            matr[r][c] = tempMatrix.matr[r][c];
        }
    }
    
    return 0;
}

std::string Matrix::FormatMatrixToString() const {
    std::stringstream ss;
    
    ss << sTitle << " (" << nMatrR << "x" << nMatrC << "):\n";
    
    for (int r = 0; r < nMatrR; r++) {
        for (int c = 0; c < nMatrC; c++) {
            ss << std::setw(10) << std::setprecision(0) << std::fixed << matr[r][c]; ////////////////////
        }
        ss << "\n";
    }
    
    return ss.str();
}

void Matrix::Print() const {
    if (Empty()) {
        std::cout << "Matr is empty/ Матрица пуста\n";
        return;
    }
    std::cout << FormatMatrixToString() << std::endl;
}

std::string Matrix::ToString() const {
    if (Empty()) {
        return "Matr is empty/ Матрица пуста";
    }
    return FormatMatrixToString();
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