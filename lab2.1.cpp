// main.cpp 
#include "Time.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    // Різні способи створення об'єктів
    Time t1;
    Time t2(10, 30);
    Time t3 = t2;
    Time t4 = makeTime(12, 45);
    Time arr[2] = { t1, t2 };

    // Вивід розміру класу
#pragma pack(1)
    std::cout << "Розмiр класу з #pragma pack(1): " << sizeof(Time) << std::endl;
#pragma pack()
    std::cout << "Розмiр класу без #pragma pack(1): " << sizeof(Time) << std::endl;

    // Використання операторів введення/виведення
    std::cout << "";
    std::cin >> t1;
    std::cout << "t1: " << t1 << std::endl;
    std::cout << "t2: " << t2 << std::endl;
    std::cout << "t3: " << t3 << std::endl;
    std::cout << "t4: " << t4 << std::endl;

    // Використання оператора приведення типу
    std::string timeString = static_cast<std::string>(t1);
    std::cout << "t1 як рядок: " << timeString << std::endl;

    // Використання операторів інкременту/декременту
    std::cout << "t1++: " << t1++ << std::endl;
    std::cout << "++t1: " << ++t1 << std::endl;
    std::cout << "t1--: " << t1-- << std::endl;
    std::cout << "--t1: " << --t1 << std::endl;

    // Використання методу Minutes()
    std::cout << "t1 у хвилинах: " << t1.Minutes() << std::endl;

    // Використання масиву об'єктів
    std::cout << "Масив arr:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cout << arr[i] << std::endl;
    }

    return 0;
}
// Time.h - Заголовний файл
#pragma once
#include <iostream>
#include <string>

class Time {
private:
    int first;  // години
    int second; // хвилини

public:
    // Конструктори
    Time();
    Time(int h, int m);
    Time(const Time& other);

    // Оператори присвоєння
    Time& operator=(const Time& other);

    // Оператори введення/виведення
    friend std::istream& operator>>(std::istream& is, Time& t);
    friend std::ostream& operator<<(std::ostream& os, const Time& t);

    // Оператор приведення типу
    operator std::string() const;

    // Оператори інкременту/декременту
    Time& operator++();    // префіксний інкремент
    Time operator++(int); // постфіксний інкремент
    Time& operator--();    // префіксний декремент
    Time operator--(int); // постфіксний декремент

    // Методи доступу
    int GetFirst() const { return first; }
    int GetSecond() const { return second; }
    void SetFirst(int value);
    void SetSecond(int value);

    // Метод перетворення у хвилини
    int Minutes() const;
};

Time makeTime(int h, int m);
// Time.cpp - Реалізація методів класу
#include "Time.h"

// Конструктори
Time::Time() : first(0), second(0) {}

Time::Time(int h, int m) {
    SetFirst(h);
    SetSecond(m);
}

Time::Time(const Time& other) : first(other.first), second(other.second) {}

// Оператори присвоєння
Time& Time::operator=(const Time& other) {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

// Оператори введення/виведення
std::istream& operator>>(std::istream& is, Time& t) {
    std::cout << "Введiть години: ";
    is >> t.first;
    std::cout << "Введiть хвилини: ";
    is >> t.second;
    t.SetFirst(t.first);
    t.SetSecond(t.second);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << t.first << " годин " << t.second << " хвилин";
    return os;
}

// Оператор приведення типу
Time::operator std::string() const {
    return std::to_string(first) + " годин " + std::to_string(second) + " хвилин";
}

// Оператори інкременту/декременту
Time& Time::operator++() {
    SetFirst(++first);
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    SetSecond(second++);
    return temp;
}

Time& Time::operator--() {
    SetFirst(--first);
    return *this;
}

Time Time::operator--(int) {
    Time temp = *this;
    SetSecond(second--);
    return temp;
}

// Методи доступу
void Time::SetFirst(int value) {
    first = (value >= 0) ? value : 0;
}

void Time::SetSecond(int value) {
    second = (value >= 0 && value < 60) ? value : 0;
}

// Метод перетворення у хвилини
int Time::Minutes() const {
    return first * 60 + second;
}

Time makeTime(int h, int m) {
    if (h < 0 || m < 0 || m >= 60) {
        std::cerr << "Помилка: некоректнi значення часу!" << std::endl;
        exit(1);
    }
    return Time(h, m);
}
