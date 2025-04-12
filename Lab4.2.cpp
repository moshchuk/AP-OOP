// Sphere.cpp
#include "Sphere.h"
#include <cmath>

#define M_PI 3.14159265358979323846

Sphere::Sphere(double r)
    : r(r) {
}

double Sphere::volume() const {
    return (4.0 * M_PI * r * r * r) / 3.0;
}

void Sphere::print() const {
    cout << "Куля: ";
}

const char* Sphere::getType() const {
    return "Куля";
}
// Sphere.h
#pragma once
#include "Shape.h"

class Sphere : public Shape {
    double r;
public:
    Sphere(double r);
    double volume() const override;
    void print() const override;
    const char* getType() const override;
};
// Tetrahedron.h
#pragma once
#include "Shape.h"

class Tetrahedron : public Shape {
    double a;
public:
    Tetrahedron(double a);
    double volume() const override;
    void print() const override;
    const char* getType() const override;
};
// Tetrahedron.cpp
#include "Tetrahedron.h"
#include <cmath>

Tetrahedron::Tetrahedron(double a)
    : a(a) {
}

double Tetrahedron::volume() const {
    return (a * a * a * sqrt(2)) / 12.0;
}

void Tetrahedron::print() const {
    cout << "Тетраедр: ";
}

const char* Tetrahedron::getType() const {
    return "Тетраедр";
}
// Pyramid.h
#pragma once
#include "Shape.h"

class Pyramid : public Shape {
    double x, y, h;
public:
    Pyramid(double x, double y, double h);
    double volume() const override;
    void print() const override;
    const char* getType() const override;
};
// Pyramid.cpp
#include "Pyramid.h"

Pyramid::Pyramid(double x, double y, double h)
    : x(x), y(y), h(h) {
}

double Pyramid::volume() const {
    return x * y * h / 3.0;
}

void Pyramid::print() const {
    cout << "Пiраміда: ";
}

const char* Pyramid::getType() const {
    return "Пiраміда";
}
// Parallelepiped.h
#pragma once
#include "Shape.h"

class Parallelepiped : public Shape {
    double x, y, z;
public:
    Parallelepiped(double x, double y, double z);
    double volume() const override;
    void print() const override;
    const char* getType() const override;
};
// Parallelepiped.cpp
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(double x, double y, double z)
    : x(x), y(y), z(z) {
}

double Parallelepiped::volume() const {
    return x * y * z;
}

void Parallelepiped::print() const {
    cout << "Паралелепiпед: ";
}

const char* Parallelepiped::getType() const {
    return "Паралелепiпед";
}
// Shape.h 
#pragma once
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double volume() const = 0;
    virtual void print() const = 0;
    virtual const char* getType() const = 0;
    virtual ~Shape() {}
};
// main.cpp
#include <iostream>
#include <vector>
#include "Parallelepiped.h"
#include "Pyramid.h"
#include "Tetrahedron.h"
#include "Sphere.h"

using namespace std;

void showMenu() {
    cout << "\nМеню:\n";
    cout << "1. Додати Паралелепiпед\n";
    cout << "2. Додати Пiрамiду\n";
    cout << "3. Додати Тетреадр\n";
    cout << "4. Додати Куля\n";
    cout << "5. Показати всi об'єкти\n";
    cout << "0. Вихiд\n";
    cout << "Ваш вибiр: ";
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    vector<Shape*> shapes;
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            double x, y, z;
            cout << "Введiть x, y, z: ";
            cin >> x >> y >> z;
            shapes.push_back(new Parallelepiped(x, y, z));
        }
        else if (choice == 2) {
            double x, y, h;
            cout << "Введiть x, y, h: ";
            cin >> x >> y >> h;
            shapes.push_back(new Pyramid(x, y, h));
        }
        else if (choice == 3) {
            double a;
            cout << "Введiть a: ";
            cin >> a;
            shapes.push_back(new Tetrahedron(a));
        }
        else if (choice == 4) {
            double r;
            cout << "Введiть r: ";
            cin >> r;
            shapes.push_back(new Sphere(r));
        }
        else if (choice == 5) {
            if (shapes.empty()) {
                cout << "Список порожнiй.\n";
            }
            else {
                for (size_t i = 0; i < shapes.size(); ++i) {
                    cout << i + 1 << ") ";
                    shapes[i]->print();
                    cout << "Volume = " << shapes[i]->volume();
                    cout << " | Type: " << shapes[i]->getType() << endl;
                }
            }
        }
        else if (choice != 0) {
            cout << "Невiрний вибiр. Спробуйте знову.\n";
        }
    } while (choice != 0);

    for (Shape* shape : shapes)
        delete shape;

    return 0;
}
