// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cmath>

class Point {
private:
    double x, y;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);
    ~Point();

    void Read();
    void Display() const;
    std::string toString() const;
    double distanceTo(const Point& other) const;
};

#endif
// Point.cpp
#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const Point& other) : x(other.x), y(other.y) {}
Point::~Point() {}

void Point::Read() {
    std::cout << "Введiть координати точки (x y): ";
    std::cin >> x >> y;
}

void Point::Display() const {
    std::cout << "(" << x << ", " << y << ")";
}

std::string Point::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <string>

class Triangle {
private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    Triangle(const Triangle& other);
    ~Triangle();

    void Read();
    void Display() const;
    std::string toString() const;

    double getA() const;
    double getB() const;
    double getC() const;
    double get_A() const;
    double get_B() const;
    double get_C() const;
    double getHeightA() const;
    double getHeightB() const;
    double getHeightC() const;
    double area() const;
    double perimeter() const;
    std::string triangleType() const;
};

#endif
// Triangle.cpp
#include "Triangle.h"
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

Triangle::Triangle() : P1(), P2(), P3() {}
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : P1(p1), P2(p2), P3(p3) {}
Triangle::Triangle(const Triangle& other) : P1(other.P1), P2(other.P2), P3(other.P3) {}
Triangle::~Triangle() {}

void Triangle::Read() {
    std::cout << "Введiть вершини трикутника:\n";
    P1.Read();
    P2.Read();
    P3.Read();
}

void Triangle::Display() const {
    std::cout << "Трикутник з вершинами: " << P1.toString() << ", " << P2.toString() << ", " << P3.toString() << std::endl;
}

std::string Triangle::toString() const {
    return "Трикутник(" + P1.toString() + ", " + P2.toString() + ", " + P3.toString() + ")";
}

double Triangle::getA() const { return P2.distanceTo(P3); }
double Triangle::getB() const { return P1.distanceTo(P3); }
double Triangle::getC() const { return P1.distanceTo(P2); }

double Triangle::get_A() const {
    double a = getA(), b = getB(), c = getC();
    return acos((b * b + c * c - a * a) / (2 * b * c)) * (180.0 / M_PI);
}

double Triangle::get_B() const {
    double a = getA(), b = getB(), c = getC();
    return acos((a * a + c * c - b * b) / (2 * a * c)) * (180.0 / M_PI);
}

double Triangle::get_C() const {
    double a = getA(), b = getB(), c = getC();
    return acos((a * a + b * b - c * c) / (2 * a * b)) * (180.0 / M_PI);
}

double Triangle::getHeightA() const {
    return (2 * area()) / getA();
}

double Triangle::getHeightB() const {
    return (2 * area()) / getB();
}

double Triangle::getHeightC() const {
    return (2 * area()) / getC();
}

double Triangle::area() const {
    double a = getA(), b = getB(), c = getC();
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::perimeter() const {
    return getA() + getB() + getC();
}

std::string Triangle::triangleType() const {
    double a = getA(), b = getB(), c = getC();
    if (a == b && b == c) return "Рiвностороннiй";
    if (a == b || b == c || a == c) return "Рiвнобедрений";
    if (std::abs(a * a + b * b - c * c) < 1e-6 || std::abs(a * a + c * c - b * b) < 1e-6 || std::abs(b * b + c * c - a * a) < 1e-6)
        return "Прямокутний";
    return "Звичайний";
}
// main.cpp
#include "Triangle.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");
    Triangle triangle;
    triangle.Read();
    triangle.Display();
    std::cout << "Периметр: " << triangle.perimeter() << std::endl;
    std::cout << "Площа: " << triangle.area() << std::endl;
    std::cout << "Тип трикутника: " << triangle.triangleType() << std::endl;
    std::cout << "Кути: A = " << triangle.get_A() << ", B = " << triangle.get_B() << ", C = " << triangle.get_C() << std::endl;
    std::cout << "Висоти: hA = " << triangle.getHeightA() << ", hB = " << triangle.getHeightB() << ", hC = " << triangle.getHeightC() << std::endl;
    return 0;
}
