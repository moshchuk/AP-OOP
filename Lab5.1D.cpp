// BitString.cpp
#include "BitString.h"

BitString::BitString() : high(0), low(0) {}
BitString::BitString(long h, long l) : high(h), low(l) {}

long BitString::getHigh() const { return high; }
long BitString::getLow() const { return low; }
void BitString::setHigh(long h) { high = h; }
void BitString::setLow(long l) { low = l; }

void BitString::Init(long h, long l) {
    high = h;
    low = l;
}

void BitString::Read() {
    std::cout << "Введiть старшi 32 бiти: ";
    std::cin >> high;
    std::cout << "Введiть молодшi 32 бiти: ";
    std::cin >> low;
}

void BitString::Display() const {
    std::cout << toString() << std::endl;
}

std::string BitString::toString() const {
    std::ostringstream oss;
    oss << "High: " << high << " Low: " << low;
    return oss.str();
}

BitString BitString::Not() const {
    return BitString(~high, ~low);
}

BitString BitString::And(const BitString& other) const {
    return BitString(high & other.high, low & other.low);
}

BitString BitString::Or(const BitString& other) const {
    return BitString(high | other.high, low | other.low);
}

BitString& BitString::operator++() {
    if (++low == 0) ++high;
    return *this;
}

BitString BitString::operator++(int) {
    BitString temp(*this);
    ++(*this);
    return temp;
}

BitString& BitString::operator--() {
    if (--low == -1) --high;
    return *this;
}

BitString BitString::operator--(int) {
    BitString temp(*this);
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const BitString& bs) {
    os << bs.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BitString& bs) {
    is >> bs.high >> bs.low;
    return is;
}

BitString::operator std::string() const {
    return toString();
}
// BitString.h
#ifndef BITSTRING_H
#define BITSTRING_H
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class BitString {
private:
    long high;
    long low;

public:
    BitString();
    BitString(long h, long l);

    long getHigh() const;
    long getLow() const;
    void setHigh(long h);
    void setLow(long l);

    void Init(long h, long l);
    void Read();
    void Display() const;
    std::string toString() const;

    BitString Not() const;
    BitString And(const BitString& other) const;
    BitString Or(const BitString& other) const;

    BitString& operator++();
    BitString operator++(int);
    BitString& operator--();
    BitString operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const BitString& bs);
    friend std::istream& operator>>(std::istream& is, BitString& bs);

    operator std::string() const;
};

#endif
// Pair.h
#ifndef PAIR_H
#define PAIR_H
#pragma once

#include <iostream>
#include <stdexcept>

class Pair {
protected:
    long first;
    long second;

public:
    Pair();
    Pair(long f, long s);

    long getFirst() const;
    long getSecond() const;
    void setFirst(long f);
    void setSecond(long s);

    void Init(long f, long s);
    void Read();
    void Display() const;

    friend std::ostream& operator<<(std::ostream& os, const Pair& p);
    friend std::istream& operator>>(std::istream& is, Pair& p);

    bool operator>(const Pair& other) const;
};

Pair makePair(long f, long s);

#endif
// Pair.cpp
#include "Pair.h"
#include <iostream>
#include <stdexcept>

Pair::Pair() : first(0), second(0) {}
Pair::Pair(long f, long s) : first(f), second(s) {
    if (f < 0 || s < 0) throw std::invalid_argument("Negative value in Pair constructor");
}

long Pair::getFirst() const { return first; }
long Pair::getSecond() const { return second; }
void Pair::setFirst(long f) {
    if (f < 0) throw std::invalid_argument("First must be non-negative");
    first = f;
}
void Pair::setSecond(long s) {
    if (s < 0) throw std::invalid_argument("Second must be non-negative");
    second = s;
}

void Pair::Init(long f, long s) {
    if (f < 0 || s < 0) throw std::runtime_error("Init values must be non-negative");
    first = f;
    second = s;
}

void Pair::Read() {
    std::cout << "\nВведiть перше число: ";
    std::cin >> first;
    std::cout << "Введiть друге число: ";
    std::cin >> second;
    if (first < 0 || second < 0) throw std::out_of_range("Неприпустимi значення у Read()");
}

void Pair::Display() const {
    std::cout << "Pair(" << first << ", " << second << ")\n";
}

std::ostream& operator<<(std::ostream& os, const Pair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Pair& p) {
    is >> p.first >> p.second;
    if (p.first < 0 || p.second < 0) throw std::invalid_argument("Invalid input for Pair");
    return is;
}

bool Pair::operator>(const Pair& other) const {
    return (first > other.first) || (first == other.first && second > other.second);
}

Pair makePair(long f, long s) {
    if (f < 0 || s < 0) throw std::invalid_argument("makePair received negative values");
    return Pair(f, s);
}
// Triad.h
#ifndef TRIAD_H
#define TRIAD_H
#pragma once

#include "Pair.h"

class Triad : public Pair {
protected:
    long third;

public:
    Triad();
    Triad(long f, long s, long t);

    long getThird() const;
    void setThird(long t);

    void Init(long f, long s, long t);
    void Read();
    void Display() const;

    bool operator>(const Triad& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Triad& t);
    friend std::istream& operator>>(std::istream& is, Triad& t);
};

Triad makeTriad(long f, long s, long t);

#endif
// Triad.cpp
#include "Triad.h"
#include <iostream>
#include <stdexcept>

Triad::Triad() : Pair(), third(0) {}
Triad::Triad(long f, long s, long t) : Pair(f, s), third(t) {
    if (t < 0) throw std::invalid_argument("Third must be non-negative");
}

long Triad::getThird() const { return third; }
void Triad::setThird(long t) {
    if (t < 0) throw std::invalid_argument("Third must be non-negative");
    third = t;
}

void Triad::Init(long f, long s, long t) {
    if (f < 0 || s < 0 || t < 0) throw std::runtime_error("Init values must be non-negative");
    first = f;
    second = s;
    third = t;
}

void Triad::Read() {
    std::cout << "\nВведiть три числа: ";
    std::cin >> first >> second >> third;
    if (first < 0 || second < 0 || third < 0) throw std::out_of_range("Неприпустимi значення у Read()");
}

void Triad::Display() const {
    std::cout << "Triad(" << first << ", " << second << ", " << third << ")\n";
}

bool Triad::operator>(const Triad& other) const {
    return (first > other.first) ||
        (first == other.first && second > other.second) ||
        (first == other.first && second == other.second && third > other.third);
}

std::ostream& operator<<(std::ostream& os, const Triad& t) {
    os << "(" << t.first << ", " << t.second << ", " << t.third << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Triad& t) {
    is >> t.first >> t.second >> t.third;
    if (t.first < 0 || t.second < 0 || t.third < 0) throw std::invalid_argument("Invalid input for Triad");
    return is;
}

Triad makeTriad(long f, long s, long t) {
    if (f < 0 || s < 0 || t < 0) throw std::invalid_argument("makeTriad received negative values");
    return Triad(f, s, t);
}
// main.cpp
#include <iostream>
#include "Pair.h"
#include "Triad.h"
#include "BitString.h"

int main() {
    setlocale(LC_ALL, "ukr");

    try {
        Pair p1, p2;
        std::cout << "Введiть першу пару:\n";
        std::cin >> p1;
        std::cout << "Введiть другу пару:\n";
        std::cin >> p2;
        std::cout << "Перша пара: " << p1 << "\nДруга пара: " << p2;
        std::cout << "\nЧи перша пара бiльша? " << (p1 > p2 ? "Так" : "Нi") << std::endl;

        Triad t1, t2;
        std::cout << "\nВведiть першу трiйку:\n";
        std::cin >> t1;
        std::cout << "Введiть другу трiйку:\n";
        std::cin >> t2;
        std::cout << "Перша трiйка: " << t1 << "\nДруга трiйка: " << t2;
        std::cout << "\nЧи перша трiйка бiльша? " << (t1 > t2 ? "Так" : "Нi") << std::endl;

        BitString a, b, c;
        std::cout << "\nВведiть перший бiтовий рядок:\n";
        std::cin >> a;
        std::cout << "Введiть другий бiтовий рядок:\n";
        std::cin >> b;

        std::cout << "\nNOT першого: " << a.Not() << std::endl;
        std::cout << "AND: " << a.And(b) << std::endl;
        std::cout << "OR: " << a.Or(b) << std::endl;
        std::cout << "Префiкс iнкремент: " << ++a << std::endl;
        std::cout << "Постфiкс iнкремент: " << a++ << std::endl;
        std::cout << "Пiсля iнкрементiв: " << a << std::endl;
        std::cout << "Префiкс декремент: " << --b << std::endl;
        std::cout << "Постфiкс декремент: " << b-- << std::endl;
        std::cout << "Пiсля декрементiв: " << b << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
    return 0;
}
