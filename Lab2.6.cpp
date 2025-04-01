//////////////////////////////////////////////////////////////////////////////
// main.cpp
// Головний файл програми

#include "RightAngled.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    RightAngled triangle;
    triangle.Read();
    triangle.Display();

    std::cout << "Гiпотенуза: " << triangle.Hypotenuse() << std::endl;
    std::cout << "Площа: " << triangle.Area() << std::endl;
    std::cout << "Рядкове представлення: " << triangle.toString() << std::endl;
    std::cout << "Кiлькiсть об'єктiв Pair: " << Pair::getCount() << std::endl;
    std::cout << "Кiлькiсть об'єктiв RightAngled: " << RightAngled::getCount() << std::endl;

    return 0;
}
//////////////////////////////////////////////////////////////////////////////
// Pair.cpp
// Файл реалізації

#include "Pair.h"
#include <iostream>
#include <string>

int Pair::count = 0;

Pair::Pair() : first(0), second(0) { count++; }
Pair::Pair(double a, double b) : first(a), second(b) { count++; }
Pair::Pair(const Pair& other) : first(other.first), second(other.second) { count++; }
Pair::~Pair() { count--; }

double Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }
void Pair::setFirst(double a) { first = a; }
void Pair::setSecond(double b) { second = b; }
void Pair::Init(double a, double b) { first = a; second = b; }
void Pair::Read() {
    std::cout << "Введiть перше число: ";
    std::cin >> first;
    std::cout << "Введiть друге число: ";
    std::cin >> second;
}
void Pair::Display() const {
    std::cout << "(" << first << ", " << second << ")" << std::endl;
}
double Pair::Product() const { return first * second; }
Pair& Pair::operator=(const Pair& other) {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}
Pair Pair::operator+(const Pair& other) const { return Pair(first + other.first, second + other.second); }
Pair Pair::operator-(const Pair& other) const { return Pair(first - other.first, second - other.second); }
Pair& Pair::operator++() { first++; second++; return *this; }
Pair Pair::operator++(int) { Pair temp = *this; ++(*this); return temp; }
Pair& Pair::operator--() { first--; second--; return *this; }
Pair Pair::operator--(int) { Pair temp = *this; --(*this); return temp; }
Pair::operator std::string() const { return "(" + std::to_string(first) + ", " + std::to_string(second) + ")"; }
int Pair::getCount() { return count; }
//////////////////////////////////////////////////////////////////////////////
// Pair.h
// Заголовний файл

#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <string>

class Pair {
private:
    double first;
    double second;
    static int count;

public:
    Pair();
    Pair(double a, double b);
    Pair(const Pair& other);
    ~Pair();

    double getFirst() const;
    double getSecond() const;
    void setFirst(double a);
    void setSecond(double b);

    void Init(double a, double b);
    void Read();
    void Display() const;
    double Product() const;

    Pair& operator=(const Pair& other);
    Pair operator+(const Pair& other) const;
    Pair operator-(const Pair& other) const;
    Pair& operator++(); 
    Pair operator++(int); 
    Pair& operator--(); 
    Pair operator--(int); 

    operator std::string() const;

    static int getCount();
};

#endif
//////////////////////////////////////////////////////////////////////////////
// RightAngled.h
// Заголовний файл

#pragma once
#ifndef RIGHTANGLED_H
#define RIGHTANGLED_H

#include "Pair.h"
#include <iostream>
#include <cmath>
#include <string>

class RightAngled {
private:
    Pair legs;
    static int count;

public:
    RightAngled();
    RightAngled(double a, double b);
    RightAngled(const RightAngled& other);
    ~RightAngled();

    Pair getLegs() const;
    void setLegs(double a, double b);

    void Init(double a, double b);
    void Read();
    void Display() const;
    std::string toString() const;

    double Hypotenuse() const;
    double Area() const;

    static int getCount();
};

#endif
//////////////////////////////////////////////////////////////////////////////
// RightAngled.cpp
// Файл реалізації

#include "RightAngled.h"

int RightAngled::count = 0;

RightAngled::RightAngled() : legs(0, 0) { count++; }
RightAngled::RightAngled(double a, double b) : legs(a, b) { count++; }
RightAngled::RightAngled(const RightAngled& other) : legs(other.legs) { count++; }
RightAngled::~RightAngled() { count--; }
Pair RightAngled::getLegs() const { return legs; }
void RightAngled::setLegs(double a, double b) { legs.setFirst(a); legs.setSecond(b); }
void RightAngled::Init(double a, double b) { legs.Init(a, b); }
void RightAngled::Read() {
    std::cout << "Введiть катети трикутника:\n";
    legs.Read();
}
void RightAngled::Display() const {
    std::cout << "Прямокутний трикутник з катетами: ";
    legs.Display();
}
std::string RightAngled::toString() const { return "Прямокутний трикутник з катетами: " + static_cast<std::string>(legs); }
double RightAngled::Hypotenuse() const { return std::sqrt(std::pow(legs.getFirst(), 2) + std::pow(legs.getSecond(), 2)); }
double RightAngled::Area() const { return 0.5 * legs.getFirst() * legs.getSecond(); }
int RightAngled::getCount() { return count; }
