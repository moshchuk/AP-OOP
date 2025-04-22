// ExceptionClasses.h
#ifndef EXCEPTIONCLASSES_H
#define EXCEPTIONCLASSES_H

#include <stdexcept>
#include <string>

class InvalidBitValue : public std::invalid_argument {
public:
    InvalidBitValue(const std::string& msg) : std::invalid_argument(msg) {}
};

class BitStringException {
    std::string message;
public:
    BitStringException(const std::string& msg) : message(msg) {}
    const std::string& what() const { return message; }
};

#endif
// Object.h
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
//  BitString.h
#pragma once

#include "Object.h"
#include "ExceptionClasses.h"

#include <iostream>
#include <string>

class BitString : public Object {
private:
    long high;
    long low;

public:
    BitString() noexcept;
    BitString(long h, long l);
    BitString(const BitString& other) noexcept;
    BitString(const std::string& str);

    BitString& operator=(const BitString& other) noexcept;

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

    BitString& operator++();      // префіксний інкремент
    BitString operator++(int);    // постфіксний інкремент
    BitString& operator--();      // префіксний декремент
    BitString operator--(int);    // постфіксний декремент

    friend std::istream& operator>>(std::istream& is, BitString& bs);
    friend std::ostream& operator<<(std::ostream& os, const BitString& bs);

    operator std::string() const;
};
//  BitString.cpp
#include "BitString.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

BitString::BitString() noexcept : high(0), low(0) {}

BitString::BitString(long h, long l) {
    if (h < 0 || l < 0)
        throw std::out_of_range("Неможливо задати вiд'ємнi бiти!");
    high = h;
    low = l;
}

BitString::BitString(const BitString& other) noexcept
    : Object(other), high(other.high), low(other.low) {
}

BitString::BitString(const string& str) {
    try {
        size_t spacePos = str.find(' ');
        if (spacePos == string::npos)
            throw BitStringException("Неправильний формат рядка ініціалізації!");

        high = stol(str.substr(0, spacePos));
        low = stol(str.substr(spacePos + 1));

        if (high < 0 || low < 0)
            throw BitStringException("Біти не можуть бути від’ємними!");
    }
    catch (const std::exception& e) {
        throw BitStringException("Неправильний формат рядка ініціалізації!");
    }
}

BitString& BitString::operator=(const BitString& other) noexcept {
    if (this != &other) {
        high = other.high;
        low = other.low;
    }
    return *this;
}

long BitString::getHigh() const { return high; }
long BitString::getLow() const { return low; }

void BitString::setHigh(long h) {
    if (h < 0)
        throw InvalidBitValue("Старші біти не можуть бути від’ємними");
    high = h;
}

void BitString::setLow(long l) {
    if (l < 0)
        throw InvalidBitValue("Молодші біти не можуть бути від’ємними");
    low = l;
}

void BitString::Init(long h, long l) {
    setHigh(h);
    setLow(l);
}

void BitString::Read() {
    cout << "Введiть старшi 32 бiти: ";
    cin >> high;
    cout << "Введiть молодшi 32 бiти: ";
    cin >> low;

    if (high < 0 || low < 0)
        throw BitStringException("Недопустиме значення для BitString (від’ємне)");
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

istream& operator>>(istream& is, BitString& bs) {
    is >> bs.high >> bs.low;
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
#include "BitString.h"
#include "ExceptionClasses.h"

using namespace std;

#pragma pack(push, 1)
class PackedBitString : public BitString {};
#pragma pack(pop)

int main() {
    setlocale(LC_ALL, "ukr");

    cout << "Кiлькiсть створених об'єктiв: " << Object::getCount() << endl;

    try {
        BitString a, b;

        cout << "\nВведення об'єкта a (через Read()):" << endl;
        a.Read();

        cout << "\nВведення об'єкта b (через оператор >>):" << endl;
        cin >> b;

        cout << "\nОб'єкт a: "; a.Display();
        cout << "Об'єкт b: " << b << endl;

        BitString c = a.Not();
        cout << "\nNOT a: " << c << endl;

        c = a.And(b);
        cout << "AND: " << c << endl;

        c = a.Or(b);
        cout << "OR: " << c << endl;

        cout << "\nIнкременти/декременти об'єкта a:" << endl;
        cout << "++a: " << ++a << endl;
        cout << "a++: " << a++ << endl;
        cout << "--a: " << --a << endl;
        cout << "a--: " << a-- << endl;

        cout << "\nПеретворення до рядка: " << string(a) << endl;

        cout << "\nСтворення через рядковий конструктор:" << endl;
        BitString d("12345 67890");
        cout << d << endl;

        cout << "\nРозмiр BitString: " << sizeof(BitString) << " байт" << endl;
        cout << "Розмiр PackedBitString: " << sizeof(PackedBitString) << " байт" << endl;

    }
    catch (InvalidBitValue& ex) {
        cout << "InvalidBitValue exception: " << ex.what() << endl;
    }
    catch (BitStringException& ex) {
        cout << "BitStringException (власний): " << ex.what() << endl;
    }
    catch (std::exception& ex) {
        cout << "Standard exception: " << ex.what() << endl;
    }
    catch (...) {
        cout << "Невідомий виняток!" << endl;
    }

    cout << "\nКiлькiсть створених об'єктiв: " << Object::getCount() << endl;

    return 0;
}
