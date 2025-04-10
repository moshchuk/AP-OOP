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
// BitString.h
#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>
#include <string>
#include <sstream>
#include "Object.h"

class BitString : public Object {
private:
    long high;
    long low;

public:
    BitString();
    BitString(long h, long l);
    BitString(const BitString& other);
    BitString& operator=(const BitString& other);

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
// BitString.cpp
#include "BitString.h"

using namespace std;

BitString::BitString() : high(0), low(0) {}
BitString::BitString(long h, long l) : high(h), low(l) {}
BitString::BitString(const BitString& other) : Object(other), high(other.high), low(other.low) {}

BitString& BitString::operator=(const BitString& other) {
    if (this != &other) {
        high = other.high;
        low = other.low;
    }
    return *this;
}

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
#include "BitString.h"
#include "Object.h"

using namespace std;

#pragma pack(push, 1)
class PackedBitString : public BitString {};
#pragma pack(pop)

int main() {
    setlocale(LC_ALL, "ukr");

    cout << "Кiлькiсть створених об'єктiв: " << Object::getCount() << endl;

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

    cout << "\nРозмiр BitString: " << sizeof(BitString) << " байт" << endl;
    cout << "Розмiр PackedBitString: " << sizeof(PackedBitString) << " байт" << endl;

    cout << "\nКiлькiсть створених об'єктiв: " << Object::getCount() << endl;

    return 0;
}
