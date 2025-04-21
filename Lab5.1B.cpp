// main.cpp
#include <iostream>
#include "BitString.h"
#include "BitStringException.h"

using namespace std;

int main() {
    setlocale(LC_CTYPE, "ukr");

    try {
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

        cout << "\nРозмiр класу BitString без #pragma pack: " << sizeof(BitString) << " байт" << endl;
    }
    catch (BitStringException& ex) {
        cerr << "BitString error (by reference): " << ex.what() << endl;
    }
    catch (const std::exception& ex) {
        cerr << "Standard error (by const ref): " << ex.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error occurred." << endl;
    }

    return 0;
}
// BitString.h
#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>
#include <string>
#include <sstream>
#include "BitStringException.h"

class BitString {
private:
    long high;
    long low;

public:
    BitString();
    BitString(long h, long l);
    BitString(const BitString& other);

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

    BitString& operator++();    // prefix
    BitString operator++(int);  // postfix
    BitString& operator--();    // prefix
    BitString operator--(int);  // postfix

    friend std::ostream& operator<<(std::ostream& os, const BitString& bs);
    friend std::istream& operator>>(std::istream& is, BitString& bs);

    operator std::string() const;
};

#endif
// BitString.cpp
#include "BitString.h"
#include <limits>

using namespace std;

BitString::BitString() : high(0), low(0) {}
BitString::BitString(long h, long l) : high(h), low(l) {}
BitString::BitString(const BitString& other) : high(other.high), low(other.low) {}

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
    if (low == LONG_MAX) {
        if (high == LONG_MAX) {
            throw BitStringException("Cannot increment: overflow.");
        }
        low = 0;
        ++high;
    }
    else {
        ++low;
    }
    return *this;
}

BitString BitString::operator++(int) {
    BitString temp(*this);
    ++(*this);
    return temp;
}

BitString& BitString::operator--() {
    if (low == 0) {
        if (high == 0) {
            throw BitStringException("Cannot decrement: underflow.");
        }
        low = LONG_MAX;
        --high;
    }
    else {
        --low;
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
// BitStringException.h
#ifndef BITSTRINGEXCEPTION_H
#define BITSTRINGEXCEPTION_H

#include <stdexcept>
#include <string>

class BitStringException : public std::runtime_error {
public:
    explicit BitStringException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif
