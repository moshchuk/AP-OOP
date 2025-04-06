// main.cpp
#include "Alcohol.h"
#include <iostream>
using namespace std;

int main() {
    setlocale(LC_CTYPE, "ukr");
    Liquid water("Вода", 1.0);
    Alcohol vodka("Горiлка", 0.95, 40.0);

    water.print();
    vodka.print();

    Liquid* ptr = new Alcohol("Вiскi", 0.94, 45.0);
    ptr->print();
    delete ptr;

    Liquid liquids[2] = {
        Liquid("Молоко", 1.03),
        Liquid("Олiя", 0.92)
    };

    for (const auto& l : liquids) {
        l.print();
    }

    Liquid* drinks[2];
    drinks[0] = new Alcohol("Брендi", 0.96, 38);
    drinks[1] = new Alcohol("Ром", 0.97, 42);

    for (int i = 0; i < 2; ++i) {
        drinks[i]->print();
        delete drinks[i];
    }

    Alcohol customDrink;
    std::cin >> customDrink;
    std::cout << customDrink << std::endl;

    Liquid processed = Liquid::processLiquid(water);
    processed.print();

    return 0;
}
// Alcohol.cpp
#include "Alcohol.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Alcohol::Alcohol() : Liquid(), strength(0.0) {}

Alcohol::Alcohol(const std::string& n, double d, double s) : Liquid(n, d) {
    if (s < 0 || s > 100) {
        cerr << "Помилка: мiцнiсть має бути в межах [0, 100].\n";
        exit(1);
    }
    strength = s;
}

Alcohol::Alcohol(const Alcohol& other) : Liquid(other), strength(other.strength) {}

double Alcohol::getStrength() const {
    return strength;
}

void Alcohol::setStrength(double s) {
    if (s < 0 || s > 100) {
        cerr << "Помилка: мiцнiсть має бути в межах [0, 100].\n";
        exit(1);
    }
    strength = s;
}

string Alcohol::toString() const {
    return Liquid::toString() + ", Мiцнiсть: " + to_string(strength) + "%";
}

void Alcohol::print() const {
    cout << toString() << endl;
}

ostream& operator<<(ostream& out, const Alcohol& a) {
    out << a.toString();
    return out;
}

istream& operator>>(istream& in, Alcohol& a) {
    string n;
    double d, s;

    cout << "Введiть назву напою: ";
    in >> ws;
    getline(in, n);

    cout << "Введiть густину: ";
    in >> d;
    if (d <= 0) {
        cerr << "Помилка: густина має бути бiльшою за 0.\n";
        exit(1);
    }

    cout << "Введiть мiцнiсть: ";
    in >> s;
    if (s < 0 || s > 100) {
        cerr << "Помилка: мiцнiсть має бути в межах [0, 100].\n";
        exit(1);
    }

    a.setName(n);
    a.setDensity(d);
    a.setStrength(s);
    return in;
}
// Alcohol.h
#pragma once
#include "Liquid.h"

class Alcohol : public Liquid {
private:
    double strength;

public:
    Alcohol();
    Alcohol(const std::string& n, double d, double s);
    Alcohol(const Alcohol& other);
    ~Alcohol() override = default;

    double getStrength() const;
    void setStrength(double s);

    std::string toString() const override;
    void print() const override;

    friend std::ostream& operator<<(std::ostream& out, const Alcohol& a);
    friend std::istream& operator>>(std::istream& in, Alcohol& a);
};
// Liquid.h
#pragma once
#include <iostream>
#include <string>

class Liquid {
protected:
    std::string name;
    double density;

public:
    Liquid();
    Liquid(const std::string& n, double d);
    Liquid(const Liquid& other);
    virtual ~Liquid() = default;

    const std::string& getName() const;
    double getDensity() const;

    void setName(const std::string& n);
    void setDensity(double d);

    virtual std::string toString() const;
    virtual void print() const;

    static Liquid processLiquid(const Liquid& l);

    friend std::ostream& operator<<(std::ostream& out, const Liquid& l);
    friend std::istream& operator>>(std::istream& in, Liquid& l);
};
// Liquid.cpp
#include "Liquid.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Liquid::Liquid() : name(""), density(0.0) {}

Liquid::Liquid(const std::string& n, double d) {
    if (d <= 0) {
        cerr << "Помилка: густина має бути бiльшою за 0.\n";
        exit(1);
    }
    name = n;
    density = d;
}

Liquid::Liquid(const Liquid& other) : name(other.name), density(other.density) {}

const string& Liquid::getName() const {
    return name;
}

double Liquid::getDensity() const {
    return density;
}

void Liquid::setName(const std::string& n) {
    name = n;
}

void Liquid::setDensity(double d) {
    if (d <= 0) {
        cerr << "Помилка: густина має бути бiльшою за 0.\n";
        exit(1);
    }
    density = d;
}

string Liquid::toString() const {
    return "Назва: " + name + ", Густина: " + to_string(density);
}

void Liquid::print() const {
    cout << toString() << endl;
}

Liquid Liquid::processLiquid(const Liquid& l) {
    cout << "Обробка рiдини...\n";
    return l;
}

ostream& operator<<(ostream& out, const Liquid& l) {
    out << l.toString();
    return out;
}

istream& operator>>(istream& in, Liquid& l) {
    string n;
    double d;

    cout << "Введiть назву рiдини: ";
    in >> ws;
    getline(in, n);

    cout << "Введiть густину: ";
    in >> d;

    if (d <= 0) {
        cerr << "Помилка: густина має бути бiльшою за 0.\n";
        exit(1);
    }

    l.setName(n);
    l.setDensity(d);
    return in;
}
