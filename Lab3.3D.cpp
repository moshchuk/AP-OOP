// RightAngled.h
#pragma once
#ifndef RIGHTANGLED_H
#define RIGHTANGLED_H

#include "Pair.h"
#include <cmath>

class RightAngled : public Pair {
public:
    RightAngled();
    RightAngled(double a, double b);
    RightAngled(const RightAngled& other);

    RightAngled& operator=(const RightAngled& other);

    double Hypotenuse() const;
    double Area() const;

    friend std::ostream& operator<<(std::ostream& os, const RightAngled& r);
    friend std::istream& operator>>(std::istream& is, RightAngled& r);
};

#endif
// RightAngled.cpp
#include "RightAngled.h"

RightAngled::RightAngled() : Pair(0, 0) {}
RightAngled::RightAngled(double a, double b) : Pair(a, b) {}
RightAngled::RightAngled(const RightAngled& other) : Pair(other) {}

RightAngled& RightAngled::operator=(const RightAngled& other) {
    if (this != &other) {
        setFirst(other.getFirst());
        setSecond(other.getSecond());
    }
    return *this;
}

double RightAngled::Hypotenuse() const {
    return std::sqrt(std::pow(getFirst(), 2) + std::pow(getSecond(), 2));
}

double RightAngled::Area() const {
    return 0.5 * getFirst() * getSecond();
}

std::ostream& operator<<(std::ostream& os, const RightAngled& r) {
    os << "Прямокутний трикутник з катетами: (" << r.getFirst() << ", " << r.getSecond() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, RightAngled& r) {
    double a, b;
    is >> a >> b;
    r.setFirst(a);
    r.setSecond(b);
    return is;
}
// Pair.cpp
#include "Pair.h"

Pair::Pair() : first(0), second(0) {}
Pair::Pair(double a, double b) : first(a), second(b) {}
Pair::Pair(const Pair& other) : first(other.first), second(other.second) {}

double Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }
void Pair::setFirst(double a) { first = a; }
void Pair::setSecond(double b) { second = b; }

Pair& Pair::operator=(const Pair& other) {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

Pair Pair::operator++() { return Pair(++first, ++second); }
Pair Pair::operator++(int) { return Pair(first++, second++); }
Pair Pair::operator--() { return Pair(--first, --second); }
Pair Pair::operator--(int) { return Pair(first--, second--); }

Pair::operator std::string() const {
    return "(" + std::to_string(first) + ", " + std::to_string(second) + ")";
}

std::ostream& operator<<(std::ostream& os, const Pair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Pair& p) {
    is >> p.first >> p.second;
    return is;
}
// Pair.h
#pragma once
#ifndef PAIR_H
#define PAIR_H

#include <iostream>
#include <string>

class Pair {
private:
    double first;
    double second;

public:
    Pair();
    Pair(double a, double b);
    Pair(const Pair& other);

    double getFirst() const;
    double getSecond() const;
    void setFirst(double a);
    void setSecond(double b);

    Pair& operator=(const Pair& other);
    Pair operator++();
    Pair operator++(int);
    Pair operator--();
    Pair operator--(int);

    explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const Pair& p);
    friend std::istream& operator>>(std::istream& is, Pair& p);
};

#endif
// main.cpp
#include <iostream>
#include "RightAngled.h"

#pragma pack(push, 1)
class PackedRightAngled : public RightAngled {};
#pragma pack(pop)

int main() {
    setlocale(LC_CTYPE, "ukr");

    RightAngled triangle;
    std::cout << "Введiть катети трикутника: ";
    std::cin >> triangle;
    std::cout << triangle << std::endl;

    std::cout << "Гiпотенуза: " << triangle.Hypotenuse() << std::endl;
    std::cout << "Площа: " << triangle.Area() << std::endl;

    Pair p1(3, 4), p2;
    p2 = p1;
    std::cout << "Пара чисел: " << p2 << std::endl;
    std::cout << "Префiксний iнкремент: " << ++p2 << std::endl;
    std::cout << "Постфiксний iнкремент: " << p2++ << std::endl;
    std::cout << "Пiсля iнкремента: " << p2 << std::endl;
    std::cout << "Префiксний декремент: " << --p2 << std::endl;
    std::cout << "Постфiксний декремент: " << p2-- << std::endl;
    std::cout << "Пiсля декремента: " << p2 << std::endl;

    std::cout << "\nРозмiр класу RightAngled: " << sizeof(RightAngled) << " байт" << std::endl;
    std::cout << "Розмiр PackedRightAngled: " << sizeof(PackedRightAngled) << " байт" << std::endl;

    return 0;
}
