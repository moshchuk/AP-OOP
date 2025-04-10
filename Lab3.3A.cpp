// main.cpp
#include <iostream>
#include "BaseBS.h"
#include "DerBSPub.h"
#include "DerBSPriv.h"

#pragma pack(push, 1)
struct PackedBaseBitStringSize {
    BaseBitString bs;
};
struct PackedDerivedBitStringPublicSize {
    DerivedBitStringPublic dbs;
};
struct PackedDerivedBitStringPrivateSize {
    DerivedBitStringPrivate dbs;
};
#pragma pack(pop)

int main() {
    setlocale(LC_CTYPE, "ukr");

    std::cout << "Розмiр BaseBitString (без #pragma pack(1)): " << sizeof(BaseBitString) << " байт" << std::endl;
    std::cout << "Розмiр DerivedBitStringPublic (без #pragma pack(1)): " << sizeof(DerivedBitStringPublic) << " байт" << std::endl;
    std::cout << "Розмiр DerivedBitStringPrivate (без #pragma pack(1)): " << sizeof(DerivedBitStringPrivate) << " байт" << std::endl;
    std::cout << "Розмiр BaseBitString (з #pragma pack(1)): " << sizeof(PackedBaseBitStringSize) << " байт" << std::endl;
    std::cout << "Розмiр DerivedBitStringPublic (з #pragma pack(1)): " << sizeof(PackedDerivedBitStringPublicSize) << " байт" << std::endl;
    std::cout << "Розмiр DerivedBitStringPrivate (з #pragma pack(1)): " << sizeof(PackedDerivedBitStringPrivateSize) << " байт" << std::endl;
    std::cout << std::endl;

    std::cout << "--- Робота з BaseBitString ---" << std::endl;
    BaseBitString base1, base2(10, 20);
    BaseBitString base3 = base2;
    std::cout << "base1: " << base1 << std::endl;
    std::cout << "base2: " << base2 << std::endl;
    std::cout << "base3: " << base3 << std::endl;
    base1.Read();
    base1.Display();
    std::cout << "base1 toString(): " << base1.toString() << std::endl;
    std::cout << std::endl;

    std::cout << "--- Робота з DerivedBitStringPublic (відкрите успадкування) ---" << std::endl;
    DerivedBitStringPublic pub1, pub2(1, 2), pub3;
    std::cout << "pub1: " << pub1 << std::endl;
    std::cout << "pub2: " << pub2 << std::endl;
    pub3 = pub2.Not();
    std::cout << "Not pub2: " << pub3 << std::endl;
    std::cin >> pub1;
    std::cout << "Введений pub1: " << pub1 << std::endl;
    std::cout << "pub1++: " << pub1++ << std::endl;
    std::cout << "pub1: " << pub1 << std::endl;
    std::cout << "++pub2: " << ++pub2 << std::endl;
    std::cout << "pub2: " << pub2 << std::endl;
    std::cout << "pub1 toString(): " << std::string(pub1) << std::endl;
    std::cout << std::endl;

    std::cout << "--- Робота з DerivedBitStringPrivate (закрите успадкування) ---" << std::endl;
    DerivedBitStringPrivate priv1, priv2(3, 4), priv3;
    priv1.Display();
    priv2.Display();
    priv3 = priv2.Not();
    priv3.Display();
    std::cin >> priv1;
    priv1.Display();
    std::cout << "priv1++: "; priv1++; priv1.Display();
    std::cout << "++priv2: "; ++priv2; priv2.Display();
    std::cout << "priv1 toString(): " << std::string(priv1) << std::endl;
    std::cout << "priv2 toString(): " << priv2.toString() << std::endl;
    std::cout << std::endl;

    return 0;
}
// DerBSPriv.h - похідний клас (приватний)
#ifndef DERBSPRIV_H
#define DERBSPRIV_H

#include "BaseBS.h"
#include <string>
#include <iostream>
#include <sstream>

class DerivedBitStringPrivate : private BaseBitString {
public:
    DerivedBitStringPrivate();
    DerivedBitStringPrivate(long h, long l);
    DerivedBitStringPrivate(const DerivedBitStringPrivate& other);

    DerivedBitStringPrivate Not() const;
    DerivedBitStringPrivate And(const DerivedBitStringPrivate& other) const;
    DerivedBitStringPrivate Or(const DerivedBitStringPrivate& other) const;

    DerivedBitStringPrivate& operator++();    
    DerivedBitStringPrivate operator++(int);  
    DerivedBitStringPrivate& operator--();    
    DerivedBitStringPrivate operator--(int);  
    DerivedBitStringPrivate& operator=(const DerivedBitStringPrivate& other);

 
    void Read();
    void Display() const;
    std::string toString() const;

    operator std::string() const;

};

std::ostream& operator<<(std::ostream& os, const DerivedBitStringPrivate& bs);
std::istream& operator>>(std::istream& is, DerivedBitStringPrivate& bs);

#endif
// DerBSPriv.cpp
#include "DerBSPriv.h"

using namespace std;

DerivedBitStringPrivate::DerivedBitStringPrivate() : BaseBitString() {}

DerivedBitStringPrivate::DerivedBitStringPrivate(long h, long l) : BaseBitString(h, l) {}

DerivedBitStringPrivate::DerivedBitStringPrivate(const DerivedBitStringPrivate& other) : BaseBitString(other) {}

DerivedBitStringPrivate DerivedBitStringPrivate::Not() const {
    return DerivedBitStringPrivate(~high, ~low);
}

DerivedBitStringPrivate DerivedBitStringPrivate::And(const DerivedBitStringPrivate& other) const {
    return DerivedBitStringPrivate(high & other.high, low & other.low);
}

DerivedBitStringPrivate DerivedBitStringPrivate::Or(const DerivedBitStringPrivate& other) const {
    return DerivedBitStringPrivate(high | other.high, low | other.low);
}

DerivedBitStringPrivate& DerivedBitStringPrivate::operator++() {
    if (++low == 0) {
        ++high;
    }
    return *this;
}

DerivedBitStringPrivate DerivedBitStringPrivate::operator++(int) {
    DerivedBitStringPrivate temp(*this);
    ++(*this);
    return temp;
}

DerivedBitStringPrivate& DerivedBitStringPrivate::operator--() {
    if (--low == -1) {
        --high;
    }
    return *this;
}

DerivedBitStringPrivate DerivedBitStringPrivate::operator--(int) {
    DerivedBitStringPrivate temp(*this);
    --(*this);
    return temp;
}

DerivedBitStringPrivate& DerivedBitStringPrivate::operator=(const DerivedBitStringPrivate& other) {
    if (this == &other) {
        return *this;
    }
    high = other.high;
    low = other.low;
    return *this;
}

void DerivedBitStringPrivate::Read() {
    BaseBitString::Read();
}

void DerivedBitStringPrivate::Display() const {
    BaseBitString::Display(); 
}

string DerivedBitStringPrivate::toString() const {
    return BaseBitString::toString(); 
}

DerivedBitStringPrivate::operator string() const {
    return toString();
}

istream& operator>>(istream& is, DerivedBitStringPrivate& bs) {
    bs.Read();
    return is;
}

ostream& operator<<(ostream& os, const DerivedBitStringPrivate& bs) {
    bs.Display();
    return os;
}
// DerBSPub.cpp
#include "DerBSPub.h"

using namespace std;

DerivedBitStringPublic::DerivedBitStringPublic() : BaseBitString() {}

DerivedBitStringPublic::DerivedBitStringPublic(long h, long l) : BaseBitString(h, l) {}

DerivedBitStringPublic::DerivedBitStringPublic(const DerivedBitStringPublic& other) : BaseBitString(other) {}

DerivedBitStringPublic DerivedBitStringPublic::Not() const {
    return DerivedBitStringPublic(~high, ~low);
}

DerivedBitStringPublic DerivedBitStringPublic::And(const DerivedBitStringPublic& other) const {
    return DerivedBitStringPublic(high & other.high, low & other.low);
}

DerivedBitStringPublic DerivedBitStringPublic::Or(const DerivedBitStringPublic& other) const {
    return DerivedBitStringPublic(high | other.high, low | other.low);
}

DerivedBitStringPublic& DerivedBitStringPublic::operator++() {
    if (++low == 0) {
        ++high;
    }
    return *this;
}

DerivedBitStringPublic DerivedBitStringPublic::operator++(int) {
    DerivedBitStringPublic temp(*this);
    ++(*this);
    return temp;
}

DerivedBitStringPublic& DerivedBitStringPublic::operator--() {
    if (--low == -1) {
        --high;
    }
    return *this;
}

DerivedBitStringPublic DerivedBitStringPublic::operator--(int) {
    DerivedBitStringPublic temp(*this);
    --(*this);
    return temp;
}

DerivedBitStringPublic& DerivedBitStringPublic::operator=(const DerivedBitStringPublic& other) {
    if (this == &other) {
        return *this;
    }
    high = other.high;
    low = other.low;
    return *this;
}

DerivedBitStringPublic::operator string() const {
    return toString();
}
// DerBSPub.h - похідний клас (публічний)
#ifndef DERBSPUB_H
#define DERBSPUB_H

#include "BaseBS.h"
#include <string>

class DerivedBitStringPublic : public BaseBitString {
public:
   
    DerivedBitStringPublic();
    DerivedBitStringPublic(long h, long l);
    DerivedBitStringPublic(const DerivedBitStringPublic& other);

    DerivedBitStringPublic Not() const;
    DerivedBitStringPublic And(const DerivedBitStringPublic& other) const;
    DerivedBitStringPublic Or(const DerivedBitStringPublic& other) const;

    DerivedBitStringPublic& operator++();   
    DerivedBitStringPublic operator++(int);  
    DerivedBitStringPublic& operator--();    
    DerivedBitStringPublic operator--(int);  
    DerivedBitStringPublic& operator=(const DerivedBitStringPublic& other);

    operator std::string() const;
};

#endif 
// BaseBS.h - Базовий клас
#ifndef BASEBS_H
#define BASEBS_H

#include <iostream>
#include <string>
#include <sstream>

class BaseBitString {
protected:
    long high;
    long low;

public:

    BaseBitString();
    BaseBitString(long h, long l);
    BaseBitString(const BaseBitString& other);

    void Init(long h, long l);
    void Read();
    void Display() const;
    std::string toString() const;

    long getHigh() const;
    long getLow() const;
    void setHigh(long h);
    void setLow(long l);

    friend std::ostream& operator<<(std::ostream& os, const BaseBitString& bs);
    friend std::istream& operator>>(std::istream& is, BaseBitString& bs);
};

#endif 
// BaseBS.cpp
#include "BaseBS.h"

using namespace std;

BaseBitString::BaseBitString() : high(0), low(0) {}

BaseBitString::BaseBitString(long h, long l) : high(h), low(l) {}

BaseBitString::BaseBitString(const BaseBitString& other) : high(other.high), low(other.low) {}

long BaseBitString::getHigh() const { return high; }
long BaseBitString::getLow() const { return low; }
void BaseBitString::setHigh(long h) { high = h; }
void BaseBitString::setLow(long l) { low = l; }

void BaseBitString::Init(long h, long l) {
    high = h;
    low = l;
}

void BaseBitString::Read() {
    cout << "Введiть старшi 32 бiти: ";
    cin >> high;
    cout << "Введiть молодшi 32 бiти: ";
    cin >> low;
}

void BaseBitString::Display() const {
    cout << "BaseBitString: " << toString() << endl;
}

string BaseBitString::toString() const {
    stringstream ss;
    ss << "High: " << high << " Low: " << low;
    return ss.str();
}

istream& operator>>(istream& is, BaseBitString& bs) {
    cout << "Введiть старшi 32 бiти: ";
    is >> bs.high;
    cout << "Введiть молодшi 32 бiти: ";
    is >> bs.low;
    return is;
}

ostream& operator<<(ostream& os, const BaseBitString& bs) {
    os << "High: " << bs.high << " Low: " << bs.low;
    return os;
}
