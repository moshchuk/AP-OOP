//////////////////////////////////////////////////////////////////////////////
// StringArray.h 
// Заголовний файл 
#pragma once
#ifndef STRINGARRAY_H
#define STRINGARRAY_H

#include <iostream>
#include <string>
#include <set>

class StringArray {
private:
    std::string* array;
    int size;

public:
    StringArray(int n);
    StringArray(const StringArray& other);
    ~StringArray();

    std::string getElement(int index) const;
    void setElement(int index, const std::string& value);

    void Init();
    void Read();
    void Display() const;
    std::string toString() const;
    StringArray concatenate(const StringArray& other) const;

    StringArray& operator=(const StringArray& other);
};

#endif // STRINGARRAY_H
//////////////////////////////////////////////////////////////////////////////
// StringArray.cpp 
// Файл реалізації – реалізація методів класу
#include "StringArray.h"
#include <sstream>
#include <stdexcept>

StringArray::StringArray(int n) : size(n) {
    array = new std::string[size];
}

StringArray::StringArray(const StringArray& other) : size(other.size) {
    array = new std::string[size];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
}

StringArray::~StringArray() {
    delete[] array;
}

std::string StringArray::getElement(int index) const {
    if (index >= 0 && index < size)
        return array[index];
    throw std::out_of_range("Index out of range");
}

void StringArray::setElement(int index, const std::string& value) {
    if (index >= 0 && index < size)
        array[index] = value;
    else
        throw std::out_of_range("Index out of range");
}

void StringArray::Init() {
    for (int i = 0; i < size; i++) {
        array[i] = "";
    }
}

void StringArray::Read() {
    for (int i = 0; i < size; i++) {
        std::cout << "Enter string " << i + 1 << ": ";
        std::getline(std::cin, array[i]);
    }
}

void StringArray::Display() const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << std::endl;
    }
}

std::string StringArray::toString() const {
    std::ostringstream oss;
    for (int i = 0; i < size; i++) {
        oss << array[i] << " ";
    }
    return oss.str();
}

StringArray StringArray::concatenate(const StringArray& other) const {
    std::set<std::string> combined;
    for (int i = 0; i < size; i++) {
        combined.insert(array[i]);
    }
    for (int i = 0; i < other.size; i++) {
        combined.insert(other.array[i]);
    }
    StringArray result(combined.size());
    int index = 0;
    for (const auto& str : combined) {
        result.setElement(index++, str);
    }
    return result;
}

StringArray& StringArray::operator=(const StringArray& other) {
    if (this != &other) {
        delete[] array;
        size = other.size;
        array = new std::string[size];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    return *this;
}
//////////////////////////////////////////////////////////////////////////////
// Lab1.4.cpp 
// Головний файл проекту – функція main
#include "StringArray.h"
#include <iostream>
#include <stdexcept>

int main() {
    setlocale(LC_CTYPE, "ukr");
    int size1, size2;
    std::cout << "Введiть розмiр першого масиву рядкiв: ";
    std::cin >> size1;
    std::cin.ignore();
    StringArray arr1(size1);
    arr1.Read();

    std::cout << "Введiть розмiр другого масиву рядкiв: ";
    std::cin >> size2;
    std::cin.ignore();
    StringArray arr2(size2);
    arr2.Read();

    try {
        int choice;
        do {
            std::cout << "\nМеню:\n";
            std::cout << "1. Вiдобразити масив 1\n";
            std::cout << "2. Вiдобразити масив 2\n";
            std::cout << "3. Вiдобразити елемент масиву 1\n";
            std::cout << "4. Вiдобразити елемент масиву 2\n";
            std::cout << "5. З'єднати масиви\n";
            std::cout << "6. Вийти\n";
            std::cout << "Введiть ваш вибiр: ";
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1:
                arr1.Display();
                break;
            case 2:
                arr2.Display();
                break;
            case 3: {
                int index;
                std::cout << "Введiть iндекс: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << arr1.getElement(index) << std::endl;
                break;
            }
            case 4: {
                int index;
                std::cout << "Введiть iндекс: ";
                std::cin >> index;
                std::cin.ignore();
                std::cout << arr2.getElement(index) << std::endl;
                break;
            }
            case 5: {
                StringArray concatenated = arr1.concatenate(arr2);
                std::cout << "З'єднаний масив:\n";
                concatenated.Display();
                break;
            }
            case 6:
                break;
            default:
                std::cout << "Невiрний вибір!\n";
            }
        } while (choice != 6);
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Помилка! " << e.what() << std::endl;
    }

    return 0;
}
