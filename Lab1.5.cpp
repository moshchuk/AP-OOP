//////////////////////////////////////////////////////////////////////////////
// Pair.h 
// Заголовний файл 
#pragma once
#ifndef PAIR_H
#define PAIR_H

class Pair {
private:
    double first;
    double second;

public:
    Pair();
    Pair(double a, double b);

    double getFirst() const;
    double getSecond() const;
    void setFirst(double a);
    void setSecond(double b);

    void Init(double a, double b);
    void Read();
    void Display() const;
    double Product() const;
};

#endif 
//////////////////////////////////////////////////////////////////////////////
// Pair.cpp 
// Файл реалізації – реалізація методів класу
#include "Pair.h"
#include <iostream>

Pair::Pair() : first(0), second(0) {}

Pair::Pair(double a, double b) : first(a), second(b) {}

double Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }

void Pair::setFirst(double a) { first = a; }
void Pair::setSecond(double b) { second = b; }

void Pair::Init(double a, double b) {
    first = a;
    second = b;
}

void Pair::Read() {
    std::cout << "Введiть перше число: ";
    std::cin >> first;
    std::cout << "Введiть друге число: ";
    std::cin >> second;
}

void Pair::Display() const {
    std::cout << "Пара чисел: (" << first << ", " << second << ")\n";
}

double Pair::Product() const {
    return first * second;
}

//////////////////////////////////////////////////////////////////////////////
// RightAngled.h
// Заголовний файл
#pragma once
#ifndef RIGHTANGLED_H
#define RIGHTANGLED_H

#include "Pair.h"

class RightAngled {
private:
    Pair legs; // катети

public:
    RightAngled();
    RightAngled(double a, double b);

    Pair getLegs() const;
    void setLegs(double a, double b);

    void Init(double a, double b);
    void Read();
    void Display() const;

    double Hypotenuse() const;
    double Area() const;
};

#endif 

//////////////////////////////////////////////////////////////////////////////
// RightAngled.cpp 
// Файл реалізації – реалізація методів класу
#include "RightAngled.h"
#include <iostream>
#include <cmath>

RightAngled::RightAngled() : legs(0, 0) {}

RightAngled::RightAngled(double a, double b) : legs(a, b) {}

Pair RightAngled::getLegs() const {
    return legs;
}

void RightAngled::setLegs(double a, double b) {
    legs.setFirst(a);
    legs.setSecond(b);
}

void RightAngled::Init(double a, double b) {
    legs.Init(a, b);
}

void RightAngled::Read() {
    std::cout << "Введiть катети трикутника:\n";
    legs.Read();
}

void RightAngled::Display() const {
    std::cout << "Прямокутний трикутник з катетами: ";
    legs.Display();
}

double RightAngled::Hypotenuse() const {
    return std::sqrt(std::pow(legs.getFirst(), 2) + std::pow(legs.getSecond(), 2));
}

double RightAngled::Area() const {
    return 0.5 * legs.getFirst() * legs.getSecond();
}
//////////////////////////////////////////////////////////////////////////////
// Lab1.5.cpp 
// головний файл
#include "RightAngled.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    RightAngled triangle;
    triangle.Read();
    triangle.Display();

    std::cout << "Гiпотенуза: " << triangle.Hypotenuse() << std::endl;
    std::cout << "Площа: " << triangle.Area() << std::endl;

    return 0;
}
