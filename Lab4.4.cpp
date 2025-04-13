// Complex.cpp
#include "complex.h"
#include <iostream>
using namespace std;

Complex::Complex() { a = b = 0; }

Complex::Complex(double x, double y) {
    a = x;
    b = y;
}

void Complex::input() {
    cout << "Введiть дiйсну та уявну частини: ";
    cin >> a >> b;
}

void Complex::output() {
    cout << "Комплексне число: " << a << (b >= 0 ? "+" : "") << b << "i\n";
}

Complex* Complex::add(Pair* p) {
    Complex* c = dynamic_cast<Complex*>(p);
    return new Complex(a + c->a, b + c->b);
}

Complex* Complex::sub(Pair* p) {
    Complex* c = dynamic_cast<Complex*>(p);
    return new Complex(a - c->a, b - c->b);
}

Complex* Complex::mul(Pair* p) {
    Complex* c = dynamic_cast<Complex*>(p);
    return new Complex(a * c->a - b * c->b, a * c->b + b * c->a);
}

Complex* Complex::div(Pair* p) {
    Complex* c = dynamic_cast<Complex*>(p);
    double denom = c->a * c->a + c->b * c->b;
    return new Complex((a * c->a + b * c->b) / denom, (b * c->a - a * c->b) / denom);
}

bool Complex::equal(Pair* p) {
    Complex* c = dynamic_cast<Complex*>(p);
    return a == c->a && b == c->b;
}

Complex Complex::conj() {
    return Complex(a, -b);
}
// Rational.cpp
#include "rational.h"
#include <iostream>
using namespace std;

int gcd(int x, int y) {
    return y == 0 ? x : gcd(y, x % y);
}

Rational::Rational() {
    a = 0;
    b = 1;
}

Rational::Rational(int num, int denom) {
    a = num;
    b = denom;
    Reduce();
}

void Rational::Reduce() {
    int g = gcd(static_cast<int>(a), static_cast<int>(b));
    a /= g;
    b /= g;
}

void Rational::input() {
    cout << "Введiть чисельник та знаменник: ";
    cin >> a >> b;
    Reduce();
}

void Rational::output() {
    cout << "Рацiональний дріб: " << static_cast<int>(a) << "/" << static_cast<int>(b) << endl;
}

Rational* Rational::add(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    Rational* res = new Rational(static_cast<int>(a * r->b + b * r->a), static_cast<int>(b * r->b));
    res->Reduce();
    return res;
}

Rational* Rational::sub(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    Rational* res = new Rational(static_cast<int>(a * r->b - b * r->a), static_cast<int>(b * r->b));
    res->Reduce();
    return res;
}

Rational* Rational::mul(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    Rational* res = new Rational(static_cast<int>(a * r->a), static_cast<int>(b * r->b));
    res->Reduce();
    return res;
}

Rational* Rational::div(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    Rational* res = new Rational(static_cast<int>(a * r->b), static_cast<int>(b * r->a));
    res->Reduce();
    return res;
}

bool Rational::equal(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    return a == r->a && b == r->b;
}

bool Rational::great(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    return a * r->b > b * r->a;
}

bool Rational::less(Pair* p) {
    Rational* r = dynamic_cast<Rational*>(p);
    return a * r->b < b * r->a;
}

double Rational::value() {
    return a / b;
}
// Complex.h
#pragma once
#include "pair.h"

class Complex : public Pair {
public:
    Complex();
    Complex(double x, double y);

    void input() override;
    void output() override;

    Complex* add(Pair* p) override;
    Complex* sub(Pair* p) override;
    Complex* mul(Pair* p) override;
    Complex* div(Pair* p) override;
    bool equal(Pair* p) override;

    Complex conj();
};
// Pair.h
#pragma once

class Pair {
protected:
    double a, b;
public:
    virtual void input() = 0;
    virtual void output() = 0;
    virtual Pair* add(Pair* p) = 0;
    virtual Pair* sub(Pair* p) = 0;
    virtual Pair* mul(Pair* p) = 0;
    virtual Pair* div(Pair* p) = 0;
    virtual bool equal(Pair* p) = 0;
    virtual ~Pair() {}
};
// Rational.h
#pragma once
#include "pair.h"

class Rational : public Pair {
    void Reduce();
public:
    Rational();
    Rational(int num, int denom);

    void input() override;
    void output() override;

    Rational* add(Pair* p) override;
    Rational* sub(Pair* p) override;
    Rational* mul(Pair* p) override;
    Rational* div(Pair* p) override;
    bool equal(Pair* p) override;

    bool great(Pair* p);
    bool less(Pair* p);
    double value();
};
// main.cpp
#include <iostream>
#include "complex.h"
#include "rational.h"

using namespace std;

void show(Pair& obj) {
    obj.output();
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    while (true) {
        cout << "\nОберiть тип об'єкта для операцiй:\n";
        cout << "1 - Комплекснi числа\n";
        cout << "2 - Рацiональнi дроби\n";
        cout << "0 - Вихiд\n";
        cout << "Ваш вибiр: ";
        int type;
        cin >> type;

        if (type == 0) {
            cout << "Завершення програми.\n";
            break;
        }

        Pair* p1 = nullptr;
        Pair* p2 = nullptr;
        Pair* result = nullptr;

        if (type == 1) {
            p1 = new Complex();
            p2 = new Complex();
        }
        else if (type == 2) {
            p1 = new Rational();
            p2 = new Rational();
        }
        else {
            cout << "Невiрний вибiр. Спробуйте ще раз.\n";
            continue;
        }

        cout << "Введення першого об'єкта:\n";
        p1->input();
        cout << "Введення другого об'єкта:\n";
        p2->input();

        cout << "\nРезультати операцiй:\n";

        result = p1->add(p2);
        cout << "Додавання: ";
        show(*result);
        delete result;

        result = p1->sub(p2);
        cout << "Вiднiмання: ";
        show(*result);
        delete result;

        result = p1->mul(p2);
        cout << "Множення: ";
        show(*result);
        delete result;

        result = p1->div(p2);
        cout << "Дiлення: ";
        show(*result);
        delete result;

        cout << "Чи рiвнi об'єкти? " << (p1->equal(p2) ? "Так" : "Нi") << endl;

        cout << "Тип об'єкта p1: " << typeid(*p1).name() << "\n";

        delete p1;
        delete p2;
    }

    return 0;
}
