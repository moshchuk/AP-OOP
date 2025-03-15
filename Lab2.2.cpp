// main.cpp
#include "Matrix.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");
    std::cout << "Розмiр класу без #pragma pack(1): " << sizeof(Matrix) << " байт\n";
#pragma pack(1)
    std::cout << "Розмiр класу з #pragma pack(1): " << sizeof(Matrix) << " байт\n";
#pragma pack()

    Matrix A(2, 2), B(2, 2);

    std::cout << "Введiть елементи матрицi A (2x2):\n";
    std::cin >> A;
    std::cout << "Введiть елементи матрицi B (2x2):\n";
    std::cin >> B;

    std::cout << "Матриця A:\n" << A;
    std::cout << "Матриця B:\n" << B;

    Matrix C(A);
    std::cout << "Матриця C (копiя A):\n" << C;

    Matrix D = A + B;
    std::cout << "Матриця D (A + B):\n" << D;

    Matrix E = A - B;
    std::cout << "Матриця E (A - B):\n" << E;

    C = B;
    std::cout << "Матриця C пiсля C = B:\n" << C;

    A += B;
    std::cout << "Матриця A пiсля A += B:\n" << A;

    B -= C;
    std::cout << "Матриця B пiсля B -= C:\n" << B;

    Matrix F = A * C;
    std::cout << "Матриця F (A * C):\n" << F;

    A *= C;
    std::cout << "Матриця A пiсля A *= C:\n" << A;

    return 0;
}
// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

class Matrix {
private:
    float** data;
    int rows, cols;
    void allocateMemory();
    void deallocateMemory();
public:
    // Конструктори
    Matrix();
    Matrix(int size);
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    // Методи доступу
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    float getElement(int i, int j) const;
    void setElement(int i, int j, float value);

    // Оператори
    Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix operator*(const Matrix& other) const;
    Matrix& operator*=(const Matrix& other);

    // Друзі
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};

#endif // MATRIX_H
// Matrix.cpp
#include "Matrix.h"
#include <stdexcept>

void Matrix::allocateMemory() {
    data = new float* [rows];
    for (int i = 0; i < rows; ++i)
        data[i] = new float[cols] {};
}

void Matrix::deallocateMemory() {
    for (int i = 0; i < rows; ++i)
        delete[] data[i];
    delete[] data;
}

// Конструктори
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}
Matrix::Matrix(int size) : rows(size), cols(size) { allocateMemory(); }
Matrix::Matrix(int r, int c) : rows(r), cols(c) { allocateMemory(); }
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
}
Matrix::~Matrix() { deallocateMemory(); }

// Методи доступу
float Matrix::getElement(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw std::out_of_range("Iндекс поза межами");
    return data[i][j];
}
void Matrix::setElement(int i, int j, float value) {
    if (i < 0 || i >= rows || j < 0 || j >= cols)
        throw std::out_of_range("Iндекс поза межами");
    data[i][j] = value;
}

// Оператори
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        deallocateMemory();
        rows = other.rows;
        cols = other.cols;
        allocateMemory();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Розмiри не спiвпадають");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Розмiри не спiвпадають");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}
Matrix& Matrix::operator+=(const Matrix& other) {
    *this = *this + other;
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other) {
    *this = *this - other;
    return *this;
}
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Неможливо помножити матрицi: невiдповідні розмiри");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            for (int k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];
    return result;
}
Matrix& Matrix::operator*=(const Matrix& other) {
    *this = *this * other;
    return *this;
}

// Потокові оператори
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j)
            os << std::setw(8) << matrix.data[i][j] << " ";
        os << '\n';
    }
    return os;
}
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (int i = 0; i < matrix.rows; ++i)
        for (int j = 0; j < matrix.cols; ++j)
            is >> matrix.data[i][j];
    return is;
} 
