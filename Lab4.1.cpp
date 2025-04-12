// Sphere.h
#pragma once
#include "Shape.h"

class Sphere : public Shape {
    double r;
public:
    Sphere(double r);
    double volume() const override;
    void print() const override;
};
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
    cout << "Sphere: ";
}
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
    cout << "Tetrahedron: ";
}
// Tetrahedron.h
#pragma once
#include "Shape.h"

class Tetrahedron : public Shape {
    double a;
public:
    Tetrahedron(double a);
    double volume() const override;
    void print() const override;
};
// Shape.h
#pragma once
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double volume() const = 0;
    virtual void print() const = 0;
    virtual ~Shape() {}
};
// Pyramid.h
#pragma once
#include "Shape.h"

class Pyramid : public Shape {
    double x, y, h;
public:
    Pyramid(double x, double y, double h);
    double volume() const override;
    void print() const override;
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
    cout << "Pyramid: ";
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
    cout << "Parallelepiped: ";
}
// main.cpp
#include <iostream>
#include <vector>
#include "Parallelepiped.h"
#include "Pyramid.h"
#include "Tetrahedron.h"
#include "Sphere.h"
using namespace std;

int main() {
    vector<Shape*> shapes;

    shapes.push_back(new Parallelepiped(2, 3, 4));
    shapes.push_back(new Pyramid(3, 4, 5));
    shapes.push_back(new Tetrahedron(6));
    shapes.push_back(new Sphere(3));

    for (Shape* shape : shapes) {
        shape->print();
        cout << "Volume = " << shape->volume() << endl;
    }

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}
