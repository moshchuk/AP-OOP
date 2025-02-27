//////////////////////////////////////////////////////////////////////////////
// RightAngled.h
// Заголовний файл
#pragma once
#ifndef RIGHTANGLED_H
#define RIGHTANGLED_H

#include <iostream>
#include <cmath>
#include <string>

class RightAngled {
private:
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
        std::string toString() const;
    };

    Pair legs; // Вкладений об'єкт (катети трикутника)

public:
    RightAngled();
    RightAngled(double a, double b);

    Pair getLegs() const;
    void setLegs(double a, double b);

    void Init(double a, double b);
    void Read();
    void Display() const;
    std::string toString() const;

    double Hypotenuse() const;
    double Area() const;
};

#endif
//////////////////////////////////////////////////////////////////////////////
// RightAngled.cpp 
// Файл реалізації – реалізація методів класу з вкладенним класом 
#include "RightAngled.h"

// Методи класу Pair
RightAngled::Pair::Pair() : first(0), second(0) {}

RightAngled::Pair::Pair(double a, double b) : first(a), second(b) {}

double RightAngled::Pair::getFirst() const { return first; }
double RightAngled::Pair::getSecond() const { return second; }

void RightAngled::Pair::setFirst(double a) { first = a; }
void RightAngled::Pair::setSecond(double b) { second = b; }

void RightAngled::Pair::Init(double a, double b) {
    first = a;
    second = b;
}

void RightAngled::Pair::Read() {
    std::cout << "Введiть перше число: ";
    std::cin >> first;
    std::cout << "Введiть друге число: ";
    std::cin >> second;
}

void RightAngled::Pair::Display() const {
    std::cout << "(" << first << ", " << second << ")";
}

double RightAngled::Pair::Product() const {
    return first * second;
}

std::string RightAngled::Pair::toString() const {
    return "(" + std::to_string(first) + ", " + std::to_string(second) + ")";
}

// Методи класу RightAngled
RightAngled::RightAngled() : legs(0, 0) {}

RightAngled::RightAngled(double a, double b) : legs(a, b) {}

RightAngled::Pair RightAngled::getLegs() const {
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
    std::cout << std::endl;
}

std::string RightAngled::toString() const {
    return "Прямокутний трикутник з катетами: " + legs.toString();
}

double RightAngled::Hypotenuse() const {
    return std::sqrt(std::pow(legs.getFirst(), 2) + std::pow(legs.getSecond(), 2));
}

double RightAngled::Area() const {
    return 0.5 * legs.getFirst() * legs.getSecond();
}
//////////////////////////////////////////////////////////////////////////////
// Lab1.6.cpp 
// головний файл
#include "RightAngled.h"

int main() {
    setlocale(LC_CTYPE, "ukr");

    RightAngled triangle;
    triangle.Read();
    triangle.Display();

    std::cout << "Гiпотенуза: " << triangle.Hypotenuse() << std::endl;
    std::cout << "Площа: " << triangle.Area() << std::endl;
    std::cout << "Рядкове представлення: " << triangle.toString() << std::endl;

    return 0;
}
