// main.cpp
#include <iostream>
#include "Matrix.h"

int main() {
    setlocale(LC_CTYPE, "ukr");
    int K, N;

    std::cout << "Введiть кiлькicть рядкiв (K): ";
    std::cin >> K;
    std::cout << "Введiть кiлькiсть стовпцiв (N): ";
    std::cin >> N;

    Matrix A(K, N), B(K, N);

    std::cout << "Введiть матрицю A:\n";
    std::cin >> A;

    std::cout << "Введiть матрицю B:\n";
    std::cin >> B;

    std::cout << "\nМатриця A:\n" << A;
    std::cout << "\nМатриця B:\n" << B;

    if (A == B)
        std::cout << "\nМатрицi A i B рiвнi\n";
    else
        std::cout << "\nМатрицi A i B НЕ рiвнi\n";

    std::cout << "Норма A: " << A.norm() << std::endl;
    std::cout << "Норма B: " << B.norm() << std::endl;

    Matrix C = A + B;
    std::cout << "\nA + B =\n" << C;

    int scalar;
    std::cout << "Введiть число для множення матрицi A: ";
    std::cin >> scalar;

    Matrix D = A * scalar;
    std::cout << "A * " << scalar << " =\n" << D;

    return 0;
}
// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath> 

class Matrix {
private:
    int rows, cols;
    int** data;

    void allocateMemory();
    void copyData(const Matrix& other);

public:
    Matrix(int rows = 3, int cols = 3);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(int scalar) const;

    bool operator==(const Matrix& other) const; // Порівняння матриць
    bool operator!=(const Matrix& other) const; // Порівняння на нерівність

    double norm() const; // Норма матриці (корінь із суми квадратів елементів)

    void input();
    void print() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};

#endif
// Matrix.cpp
#include "Matrix.h"
#include <iostream>
#include <cmath>

void Matrix::allocateMemory() {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols] {0};
    }
}

void Matrix::copyData(const Matrix& other) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            data[i][j] = other.data[i][j];
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    allocateMemory();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    copyData(other);
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; i++) delete[] data[i];
    delete[] data;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    for (int i = 0; i < rows; i++) delete[] data[i];
    delete[] data;

    rows = other.rows;
    cols = other.cols;
    allocateMemory();
    copyData(other);

    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        std::cerr << "Помилка: Матрицi рiзного розмiру!" << std::endl;
        exit(1);
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];

    return result;
}

Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] * scalar;

    return result;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) return false;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (data[i][j] != other.data[i][j]) return false;

    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

double Matrix::norm() const {
    double sum = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            sum += data[i][j] * data[i][j];

    return std::sqrt(sum);
}

void Matrix::input() {
    std::cout << "Введiть елементи матрицi " << rows << "x" << cols << ":" << std::endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            std::cin >> data[i][j];
}

void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << " ";
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++)
            os << m.data[i][j] << " ";
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            is >> m.data[i][j];
    return is;
} 
