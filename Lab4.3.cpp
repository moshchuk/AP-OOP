// Array.cpp
#include "Array.h"

Array::Array(int size, unsigned char init) {
    if (size > MAX_SIZE) throw length_error("Size exceeds MAX_SIZE");
    this->size = size;
    for (int i = 0; i < size; ++i) {
        data[i] = init;
    }
}

unsigned char& Array::operator[](int index) {
    rangeCheck(index);
    return data[index];
}

const unsigned char& Array::operator[](int index) const {
    rangeCheck(index);
    return data[index];
}

void Array::print() const {
    for (int i = size - 1; i >= 0; --i) {
        cout << (int)data[i];
    }
    cout << endl;
}
// Array.h
#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class Array {
protected:
    static const int MAX_SIZE = 100;
    unsigned char data[MAX_SIZE];
    int size;

    void rangeCheck(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
    }

public:
    Array(int size = 10, unsigned char init = 0);
    virtual ~Array() {}

    unsigned char& operator[](int index);
    const unsigned char& operator[](int index) const;

    int getSize() const { return size; }

    virtual void add(const Array& other) = 0;
    virtual void print() const;
    virtual const char* getType() const = 0;
};
// Hex.cpp
#include "Hex.h"
#include <iomanip>

Hex::Hex(int size, unsigned char init)
    : Array(size, init) {
}

void Hex::add(const Array& other) {
    int otherSize = other.getSize();
    for (int i = 0; i < size; ++i) {
        int sum = data[i];
        if (i < otherSize) sum += other[i];
        data[i] = sum % 16;
        if (sum >= 16 && i + 1 < size) data[i + 1]++;
    }
}

void Hex::print() const {
    cout << "Hex: ";
    for (int i = size - 1; i >= 0; --i) {
        cout << hex << uppercase << (int)data[i];
    }
    cout << dec << endl;
}

const char* Hex::getType() const {
    return "Hex";
}
// Hex.h
#pragma once
#include "Array.h"

class Hex : public Array {
public:
    Hex(int size = 10, unsigned char init = 0);
    void add(const Array& other) override;
    void print() const override;
    const char* getType() const override;
};
// Money.cpp
#include "Money.h"

Money::Money(int size, unsigned char init)
    : Array(size, init) {
}

void Money::add(const Array& other) {
    int carry = 0;
    int otherSize = other.getSize();
    for (int i = 0; i < size; ++i) {
        int sum = data[i] + (i < otherSize ? other[i] : 0) + carry;
        data[i] = sum % 10;
        carry = sum / 10;
    }
}

void Money::print() const {
    cout << "Money: ";
    for (int i = size - 1; i >= 2; --i)
        cout << (int)data[i];
    cout << '.';
    cout << (int)data[1] << (int)data[0] << " грн" << endl;
}

const char* Money::getType() const {
    return "Money";
}
// Money.h
#pragma once
#include "Array.h"

class Money : public Array {
public:
    Money(int size = 10, unsigned char init = 0);
    void add(const Array& other) override;
    void print() const override;
    const char* getType() const override;
};
// main.cpp
#include <iostream>
#include <vector>
#include <limits>
#include "Hex.h"
#include "Money.h"
using namespace std;

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Невiрне введення. Спробуйте ще раз.\n";
        }
        else {
            return value;
        }
    }
}

unsigned char getCharInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (value < 0 || value > 15) {
            cout << "Невiрне значення (повинно бути вiд 0 до 15).\n";
        }
        else {
            return static_cast<unsigned char>(value);
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    vector<Array*> arrays;

    int choice;
    while (true) {
        cout << "\n=== Меню ===\n";
        cout << "1. Створити масив Hex\n";
        cout << "2. Створити масив Money\n";
        cout << "3. Додати масиви (до самого себе)\n";
        cout << "4. Вивести всi масиви\n";
        cout << "5. Перевiрка iндексацiї\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибiр: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int size = getIntInput("Введiть розмiр масиву Hex (макс. 100): ");
            unsigned char init = getCharInput("Введiть початкове значення елементiв (від 0 до 15): ");
            arrays.push_back(new Hex(size, init));
            cout << "Масив Hex успiшно створено!\n";
            break;
        }

        case 2: {
            int size = getIntInput("Введiть розмiр масиву Money (макс. 100): ");
            unsigned char init = getCharInput("Введiть початкове значення елементiв (вiд 0 до 9): ");
            arrays.push_back(new Money(size, init));
            cout << "Масив Money успiшно створено!\n";
            break;
        }

        case 3: {
            cout << "\n== Полiморфне додавання (масив + сам до себе) ==\n";
            for (Array* a : arrays) {
                a->add(*a);
                a->print();
            }
            break;
        }

        case 4: {
            cout << "\n== Вивести всi масиви ==\n";
            for (Array* a : arrays) {
                a->print();
                cout << "Type: " << a->getType() << endl;
            }
            break;
        }

        case 5: {
            cout << "\n== Перевiрка iндексацiї ==\n";
            int index = getIntInput("Введiть iндекс елементу для перевiрки: ");
            try {
                cout << "Масив 0, елемент " << index << ": " << (int)(*arrays[0])[index] << endl;
            }
            catch (const exception& e) {
                cout << "Помилка: " << e.what() << endl;
            }
            break;
        }

        case 0: {
            for (Array* a : arrays) {
                delete a;
            }
            cout << "Вихiд з програми...\n";
            return 0;
        }

        default:
            cout << "Невiрний вибiр! Спробуйте ще раз.\n";
        }
    }

    return 0;
}
