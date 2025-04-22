// RightAngled.h
#pragma once
#ifndef RIGHTANGLED_H
#define RIGHTANGLED_H

#include "Pair.h"
#include <cmath>

class RightAngled : public Pair {
public:
    RightAngled() throw();
    RightAngled(double a, double b) throw(std::invalid_argument);
    RightAngled(const std::string& str) throw(MyException);
    RightAngled(const RightAngled& other) throw();

    RightAngled& operator=(const RightAngled& other) throw();

    double Hypotenuse() const throw();
    double Area() const throw();

    friend std::ostream& operator<<(std::ostream& os, const RightAngled& r);
    friend std::istream& operator>>(std::istream& is, RightAngled& r);
};

#endif
// RightAngled.cpp
#include "RightAngled.h"

RightAngled::RightAngled() : Pair() {}
RightAngled::RightAngled(double a, double b) : Pair(a, b) {}
RightAngled::RightAngled(const std::string& str) : Pair(str) {}
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
// Pair.h
#pragma once
#ifndef PAIR_H
#define PAIR_H

#include "Object.h"
#include "MyExceptions.h"
#include <iostream>
#include <string>

class Pair : public Object {
protected:
    double first;
    double second;

public:
    Pair() throw();
    Pair(double a, double b) throw(std::invalid_argument);
    Pair(const std::string& str) throw(MyException);
    Pair(const Pair& other) throw();

    double getFirst() const throw();
    double getSecond() const throw();
    void setFirst(double a) throw(MyOutOfRange);
    void setSecond(double b) throw(MyOutOfRange);

    Pair& operator=(const Pair& other) throw();
    Pair operator++() throw();
    Pair operator++(int) throw();
    Pair operator--() throw();
    Pair operator--(int) throw();

    explicit operator std::string() const throw();

    friend std::ostream& operator<<(std::ostream& os, const Pair& p);
    friend std::istream& operator>>(std::istream& is, Pair& p);
};

#endif
// Pair.cpp
#include "Pair.h"
#include <sstream>

Pair::Pair() : first(0), second(0) {}

Pair::Pair(double a, double b) {
    if (a < 0 || b < 0)
        throw std::invalid_argument("Числа не можуть бути вiд’ємними");
    first = a;
    second = b;
}

Pair::Pair(const std::string& str) {
    std::stringstream ss(str);
    if (!(ss >> first >> second)) {
        throw MyException("Помилка розбору рядка до чисел");
    }
}

Pair::Pair(const Pair& other) : Object(other), first(other.first), second(other.second) {}

double Pair::getFirst() const { return first; }
double Pair::getSecond() const { return second; }

void Pair::setFirst(double a) {
    if (a < 0)
        throw MyOutOfRange("Перше число не може бути вiд’ємним");
    first = a;
}

void Pair::setSecond(double b) {
    if (b < 0)
        throw MyOutOfRange("Друге число не може бути вiд’ємним");
    second = b;
}

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
// MyExceptions.h
#pragma once
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class MyException : public std::exception {
    std::string message;
public:
    MyException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MyOutOfRange : public std::out_of_range {
public:
    MyOutOfRange(const std::string& msg) : std::out_of_range(msg) {}
};

#endif
// main.cpp
#include "RightAngled.h"
#include "Pair.h"
#include "MyExceptions.h"
#include <iostream>
#include <iomanip>

#pragma pack(push, 1)
class PackedPair : public Pair {};
#pragma pack(pop)

int main() {
    setlocale(LC_CTYPE, "ukr");

    try {
        RightAngled triangle;
        std::cout << "Введiть два додатнi числа (катети прямокутного трикутника): ";
        std::cin >> triangle;

        std::cout << triangle << "\n";
        std::cout << "Гiпотенуза: " << triangle.Hypotenuse() << "\n";
        std::cout << "Площа: " << triangle.Area() << "\n";
    }
    catch (MyException e) {
        std::cerr << "MyException (за значенням): " << e.what() << "\n";
    }

    try {
        Pair p(-1, 2); 
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "std::invalid_argument (за посиланням): " << e.what() << "\n";
    }

    try {
        Pair p;
        double a;
        std::cout << "Введiть значення для першого елемента (демонстрацiя винятку): ";
        std::cin >> a;
        p.setFirst(a); 
    }
    catch (MyOutOfRange& e) {
        std::cerr << "MyOutOfRange (за посиланням): " << e.what() << "\n";
    }

    std::cout << "Кiлькiсть створених об’єктiв: " << Object::getCount() << "\n";
    std::cout << "Розмiр Pair без pack: " << sizeof(Pair) << " байт\n";
    std::cout << "Розмiр Pair з #pragma pack(1): " << sizeof(PackedPair) << " байт\n";

    return 0;
}
