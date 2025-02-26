//////////////////////////////////////////////////////////////////////////////
// Vector.h 
// Заголовний файл 

#pragma once
#include <iostream>
#include <cmath>

class Vector {
private:
    int* data;
    int size;
    int state;

public:
    Vector();
    ~Vector();

    int getSize() const { return size; }
    int getState() const { return state; }
    int getElement(int index) const;
    void setElement(int index, int value);

    bool Init(int newSize);
    void Read();
    void Display() const;
    double EuclideanNorm() const;
};

Vector makeVector(int size);

//////////////////////////////////////////////////////////////////////////////
// Vector.cpp 
// Файл реалізації – реалізація методів класу
#include "Vector.h"
using namespace std;

Vector::Vector() : data(nullptr), size(0), state(0) {}

Vector::~Vector() {
    delete[] data;
}

bool Vector::Init(int newSize) {
    if (newSize <= 0) {
        state = 1;
        return false;
    }
    size = newSize;
    data = new (std::nothrow) int[size];
    if (!data) {
        state = 2;
        return false;
    }
    return true;
}

void Vector::Read() {
    int newSize;
    std::cout << "Введiть розмiр вектора: ";
    std::cin >> newSize;
    if (!Init(newSize)) {
        std::cout << "Помилка видiлення пам'ятi.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << "Елемент [" << i << "]: ";
        std::cin >> data[i];
    }
}

void Vector::Display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

double Vector::EuclideanNorm() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += data[i] * data[i];
    }
    return std::sqrt(sum);
}

int Vector::getElement(int index) const {
    if (index < 0 || index >= size) {
        return -1;
    }
    return data[index];
}

void Vector::setElement(int index, int value) {
    if (index >= 0 && index < size) {
        data[index] = value;
    }
}

Vector makeVector(int size) {
    Vector v;
    if (!v.Init(size)) {
        std::cerr << "Не вдалося створити вектор.\n";
        exit(EXIT_FAILURE);
    }
    return v;
}
//////////////////////////////////////////////////////////////////////////////
// Lab1.2.cpp 
// Головний файл проекту – функція main

#include "Vector.h"

using namespace std;

int main() {

    setlocale(LC_CTYPE, "ukr");
    Vector v = makeVector(5);
    v.Read();
    v.Display();
    std::cout << "Евклiдова норма: " << v.EuclideanNorm() << std::endl;
    return 0;
}
