//////////////////////////////////////////////////////////////////////////////
// Lab2.3.cpp 
// Головний файл проекту – функція main
#include <iostream>
#include "BitString.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "ukr");
    BitString a, b, c;

    cout << "Введiть перший бiтовий рядок:" << endl;
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
//////////////////////////////////////////////////////////////////////////////
// BitString.h 
// Заголовний файл 
#ifndef BITSTRING_H
#define BITSTRING_H

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
//////////////////////////////////////////////////////////////////////////////
// BitString.cpp 
// Файл реалізації – реалізація методів класу
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
