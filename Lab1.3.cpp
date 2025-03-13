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
    long high; // Старші 32 біти
    long low;  // Молодші 32 біти

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
};

#endif // BITSTRING_H
//////////////////////////////////////////////////////////////////////////////
// Lab1.3.cpp 
// Головний файл проекту – функція main
#include <iostream>
#include "BitString.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "ukr");
    BitString a, b, c;

    cout << "Введiть перший бiтовий рядок:" << endl;
    a.Read();

    cout << "Введiть другий бiтовий рядок:" << endl;
    b.Read();

    cout << "Перший рядок: ";
    a.Display();

    cout << "Другий рядок: ";
    b.Display();

    c = a.Not();
    cout << "Операцiя NOT: ";
    c.Display();

    c = a.And(b);
    cout << "Операцiя AND: ";
    c.Display();

    c = a.Or(b);
    cout << "Операцiя OR: ";
    c.Display();

    return 0;
}
