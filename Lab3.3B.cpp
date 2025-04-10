// Pair.cpp
#include "Pair.h"
#include <iostream>

Pair::Pair() : first(0), second(0) {}
Pair::Pair(long f, long s) : first(f), second(s) {}

long Pair::getFirst() const { return first; }
long Pair::getSecond() const { return second; }
void Pair::setFirst(long f) { first = f; }
void Pair::setSecond(long s) { second = s; }

void Pair::Init(long f, long s) {
    first = f;
    second = s;
}

void Pair::Read() {
    std::cout << "Введiть перше число: ";
    std::cin >> first;
    std::cout << "Введiть друге число: ";
    std::cin >> second;
}

void Pair::Display() const {
    std::cout << "Pair(" << first << ", " << second << ")" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Pair& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Pair& p) {
    std::cout << "Введiть перше число: ";
    is >> p.first;
    std::cout << "Введiть друге число: ";
    is >> p.second;
    return is;
}

bool Pair::operator>(const Pair& other) const {
    return (first > other.first) || (first == other.first && second > other.second);
}

Pair makePair(long f, long s) {
    if (f < 0 || s < 0) {
        std::cerr << "Некоректнi значення для Pair!" << std::endl;
        exit(1);
    }
    return Pair(f, s);
}
// Pair.h
#ifndef PAIR_H
#define PAIR_H
#pragma once

#include <iostream>

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
// Triad.cpp
#include "Triad.h"
#include <iostream>

Triad::Triad() : Pair(), third(0) {}
Triad::Triad(long f, long s, long t) : Pair(f, s), third(t) {}

long Triad::getThird() const { return third; }
void Triad::setThird(long t) { third = t; }

void Triad::Init(long f, long s, long t) {
    first = f;
    second = s;
    third = t;
}

void Triad::Read() {
    std::cout << "Введiть три числа: ";
    std::cin >> first >> second >> third;
}

void Triad::Display() const {
    std::cout << "Triad(" << first << ", " << second << ", " << third << ")" << std::endl;
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
    std::cout << "Введiть перше число: ";
    is >> t.first;
    std::cout << "Введiть друге число: ";
    is >> t.second;
    std::cout << "Введiть третє число: ";
    is >> t.third;
    return is;
}

Triad makeTriad(long f, long s, long t) {
    if (f < 0 || s < 0 || t < 0) {
        std::cerr << "Некоректнi значення для Triad!" << std::endl;
        exit(1);
    }
    return Triad(f, s, t);
}
// Triad.h
#pragma once
#ifndef TRIAD_H
#define TRIAD_H

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
// BitString.h
#ifndef BITSTRING_H
#define BITSTRING_H
#pragma once

#include <iostream>
#include <string>
#include <sstream>

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

    BitString& operator++();    // Префіксний інкремент
    BitString operator++(int);  // Постфіксний інкремент
    BitString& operator--();    // Префіксний декремент
    BitString operator--(int);  // Постфіксний декремент

    friend std::ostream& operator<<(std::ostream& os, const BitString& bs);
    friend std::istream& operator>>(std::istream& is, BitString& bs);

    operator std::string() const;
};

#endif // BITSTRING_H

// BitString.cpp 
#include "BitString.h"

using namespace std;

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
    cout << "Введiть старшi 32 бiти: ";
    cin >> high;
    cout << "Введiть молодшi 32 бiти: ";
    cin >> low;
}

void BitString::Display() const {
    cout << "BitString: " << toString() << endl;
}

string BitString::toString() const {
    stringstream ss;
    ss << "High: " << high << " Low: " << low;
    return ss.str();
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
    if (++low == 0) { // Якщо low переповнився, збільшуємо high
        ++high;
    }
    return *this;
}

BitString BitString::operator++(int) {
    BitString temp(*this);
    ++(*this);
    return temp;
}

BitString& BitString::operator--() {
    if (--low == -1) { // Якщо low став -1 (переповнення), зменшуємо high
        --high;
    }
    return *this;
}

BitString BitString::operator--(int) {
    BitString temp(*this);
    --(*this);
    return temp;
}

istream& operator>>(istream& is, BitString& bs) {
    cout << "Введiть старшi 32 бiти: ";
    is >> bs.high;
    cout << "Введiть молодшi 32 бiти: ";
    is >> bs.low;
    return is;
}

ostream& operator<<(ostream& os, const BitString& bs) {
    os << "High: " << bs.high << " Low: " << bs.low;
    return os;
}

BitString::operator string() const {
    return toString();
}
// main.cpp
#include <iostream>
#include "Pair.h"
#include "Triad.h"
#include "BitString.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ukr");

    Pair p1, p2;
    cout << "Введiть першу пару:" << endl;
    cin >> p1;
    cout << "Введiть другу пару:" << endl;
    cin >> p2;
    cout << "Перша пара: " << p1 << endl;
    cout << "Друга пара: " << p2 << endl;
    cout << "Чи перша пара бiльша за другу? " << (p1 > p2 ? "Так" : "Нi") << endl;

    Triad t1, t2;
    cout << "\nВведiть першу трiйку:" << endl;
    cin >> t1;
    cout << "Введiть другу трiйку:" << endl;
    cin >> t2;
    cout << "Перша трiйка: " << t1 << endl;
    cout << "Друга трiйка: " << t2 << endl;
    cout << "Чи перша трiйка бiльша за другу? " << (t1 > t2 ? "Так" : "Нi") << endl;

    BitString a, b, c;
    cout << "\nВведiть перший бiтовий рядок:" << endl;
    cin >> a;

    cout << "Введiть другий бiтовий рядок:" << endl;
    cin >> b;

    cout << "Перший рядок: " << a << endl;
    cout << "Другий рядок: " << b << endl;

    c = a.Not();
    cout << "Операцiя NOT: " << c << endl;

    c = a.And(b);
    cout << "Операцiя AND: " << c << endl;

    c = a.Or(b);
    cout << "Операцiя OR: " << c << endl;

    cout << "Префiксний iнкремент першого рядка: " << ++a << endl;
    cout << "Постфiксний iнкремент першого рядка: " << a++ << endl;
    cout << "Стан першого рядка пiсля iнкрементiв: " << a << endl;

    cout << "Префiксний декремент другого рядка: " << --b << endl;
    cout << "Постфiксний декремент другого рядка: " << b-- << endl;
    cout << "Стан другого рядка пiсля декрементiв: " << b << endl;

    return 0;
}
