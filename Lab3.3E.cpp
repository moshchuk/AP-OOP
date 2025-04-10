// RightAngled.cpp
#include "RightAngled.h"

RightAngled::RightAngled() : Pair(0, 0) {}
RightAngled::RightAngled(double a, double b) : Pair(a, b) {}
RightAngled::RightAngled(const RightAngled& other) : Pair(other) {}

RightAngled& RightAngled::operator=(const RightAngled& other) {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

double RightAngled::Hypotenuse() const {
    return std::sqrt(first * first + second * second);
}

double RightAngled::Area() const {
    return 0.5 * first * second;
}

std::ostream& operator<<(std::ostream& os, const RightAngled& r) {
    os << "Прямокутний трикутник з катетами: (" << r.first << ", " << r.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, RightAngled& r) {
    is >> r.first >> r.second;
    return is;
}
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
// Pair.cpp
#include "Pair.h"

Pair::Pair() : first(0), second(0) {}
Pair::Pair(double a, double b) : first(a), second(b) {}
Pair::Pair(const Pair& other) : Object(other), first(other.first), second(other.second) {}

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

#include "Object.h"
#include <iostream>
#include <string>

class Pair : public Object {
protected:
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
// Object.h
#pragma once
#ifndef OBJECT_H
#define OBJECT_H

class Object {
protected:
    static int count;
public:
    Object();
    Object(const Object&);
    virtual ~Object();
    static int getCount();
};

#endif
// Object.cpp
#include "Object.h"

int Object::count = 0;

Object::Object() {
    ++count;
}

Object::Object(const Object&) {
    ++count;
}

Object::~Object() {
    --count;
}

int Object::getCount() {
    return count;
}
// main.cpp
#include "RightAngled.h"
#include <iostream>
#include <iomanip>

#pragma pack(push, 1)
class PackedPair : public Pair {};
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

    std::cout << "Кiлькiсть створених об'єктiв: " << Object::getCount() << std::endl;

    std::cout << "Розмiр Pair без pack: " << sizeof(Pair) << " байт" << std::endl;
    std::cout << "Розмiр Pair з #pragma pack(1): " << sizeof(PackedPair) << " байт" << std::endl;

    return 0;
}
