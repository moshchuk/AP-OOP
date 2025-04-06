// main.cpp
#include "Pair.h"
#include "RightAngled.h"

Pair processPair(const Pair& p);

int main() {
    setlocale(LC_CTYPE, "ukr");
    cout << "=== Перевiрка класу Pair ===" << endl;
    Pair p1(3, 4), p2;
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "Добуток p1 = " << p1.product() << endl;

    Pair p3 = processPair(p2);
    cout << "Повернуто з функцiї: " << p3 << endl;

    cout << "\n=== Перевiрка класу RightAngled ===" << endl;
    RightAngled t1(3, 4), t2;
    cin >> t2;

    cout << "t1 = " << t1 << endl;
    cout << "t2 = " << t2 << endl;
    cout << "Гiпотенуза t1 = " << t1.hypotenuse() << endl;
    cout << "Площа t1 = " << t1.area() << endl;

    Pair* basePtr = &t1;
    cout << "Вказiвник на базовий клас (похiдний об'єкт): " << *basePtr << endl;

    RightAngled triangles[2] = { RightAngled(5, 12), t2 };
    for (int i = 0; i < 2; ++i) {
        cout << "Трикутник #" << i + 1 << ": " << triangles[i] << endl;
    }

    return 0;
}
// Utils.cpp
#include "Pair.h"

Pair processPair(const Pair& p) {
    cout << "Обробка пари: " << p << endl;
    return Pair(p.getA() + 1, p.getB() + 1);
}
// RightAngled.cpp
#include "RightAngled.h"
#include <cmath>
#include <sstream>

RightAngled::RightAngled(double x, double y) : Pair(x, y) {}

RightAngled::RightAngled(const RightAngled& r) : Pair(r) {}

RightAngled::~RightAngled() {}

double RightAngled::hypotenuse() const {
    return sqrt(a * a + b * b);
}

double RightAngled::area() const {
    return 0.5 * a * b;
}

RightAngled::operator string() const {
    stringstream ss;
    ss << "Катети: (" << a << ", " << b << "), Гiпотенуза: " << hypotenuse()
        << ", Площа: " << area();
    return ss.str();
}

ostream& operator<<(ostream& out, const RightAngled& r) {
    return out << (string)r;
}

istream& operator>>(istream& in, RightAngled& r) {
    double x, y;
    cout << "Введiть катет a: ";
    in >> x;
    cout << "Введiть катет b: ";
    in >> y;
    r.setA(x);
    r.setB(y);
    return in;
}
// RightAngled.h
#pragma once
#include "Pair.h"

class RightAngled : public Pair {
public:
    RightAngled(double x = 1, double y = 1);
    RightAngled(const RightAngled& r);
    ~RightAngled();

    double hypotenuse() const;
    double area() const;

    operator string() const;

    friend ostream& operator<<(ostream& out, const RightAngled& r);
    friend istream& operator>>(istream& in, RightAngled& r);
};
// Pair.h
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Pair {
protected:
    double a, b;

public:
    Pair(double x = 1, double y = 1);
    Pair(const Pair& p);
    virtual ~Pair();

    double getA() const;
    double getB() const;
    void setA(double x);
    void setB(double y);

    double product() const;

    operator string() const;

    friend ostream& operator<<(ostream& out, const Pair& p);
    friend istream& operator>>(istream& in, Pair& p);
};
// Pair.cpp
#include "Pair.h"
#include <sstream>
#include <cstdlib>

Pair::Pair(double x, double y) {
    if (x == 0 || y == 0) {
        cerr << "Помилка: значення не можуть бути нулем." << endl;
        exit(1);
    }
    a = x;
    b = y;
}

Pair::Pair(const Pair& p) : a(p.a), b(p.b) {}

Pair::~Pair() {}

double Pair::getA() const { return a; }
double Pair::getB() const { return b; }

void Pair::setA(double x) {
    if (x == 0) {
        cerr << "Помилка: значення не може бути нулем." << endl;
        exit(1);
    }
    a = x;
}

void Pair::setB(double y) {
    if (y == 0) {
        cerr << "Помилка: значення не може бути нулем." << endl;
        exit(1);
    }
    b = y;
}

double Pair::product() const {
    return a * b;
}

Pair::operator string() const {
    stringstream ss;
    ss << "(" << a << ", " << b << ")";
    return ss.str();
}

ostream& operator<<(ostream& out, const Pair& p) {
    return out << (string)p;
}

istream& operator>>(istream& in, Pair& p) {
    double x, y;
    cout << "Введiть перше число (a): ";
    in >> x;
    cout << "Введiть друге число (b): ";
    in >> y;
    p.setA(x);
    p.setB(y);
    return in;
}
