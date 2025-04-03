// Triangle.cpp
#include "Triangle.h"
#include <iostream>
#include <cmath>

int Triangle::count = 0;

Triangle::Triangle() : P1(), P2(), P3() { count++; }
Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : P1(p1), P2(p2), P3(p3) { count++; }
Triangle::Triangle(const Triangle& other) : P1(other.P1), P2(other.P2), P3(other.P3) { count++; }
Triangle::~Triangle() { count--; }

int Triangle::getCount() { return count; }

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
// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle {
private:
    Point P1, P2, P3;
    static int count;

public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    Triangle(const Triangle& other);
    ~Triangle();

    static int getCount();

    void Read();
    void Display() const;
    std::string toString() const;

    double getA() const;
    double getB() const;
    double getC() const;

    double area() const;
    double perimeter() const;
    std::string triangleType() const;
};

#endif
// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cmath>

class Point {
private:
    double x, y;
    static int count;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);
    ~Point();

    static int getCount();

    void Read();
    void Display() const;
    std::string toString() const;

    double distanceTo(const Point& other) const;
    double distanceToOrigin() const;

    void moveX(double dx);
    void moveY(double dy);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Point& operator++();   
    Point operator++(int); 
    Point& operator--();   
    Point operator--(int); 
};

#endif
// Point.cpp
#include "Point.h"

int Point::count = 0;

Point::Point() : x(0), y(0) { count++; }
Point::Point(double x, double y) : x(x), y(y) { count++; }
Point::Point(const Point& other) : x(other.x), y(other.y) { count++; }
Point::~Point() { count--; }

int Point::getCount() { return count; }

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

double Point::distanceToOrigin() const {
    return std::sqrt(x * x + y * y);
}

void Point::moveX(double dx) { x += dx; }
void Point::moveY(double dy) { y += dy; }

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

Point& Point::operator++() {
    x++; y++;
    return *this;
}

Point Point::operator++(int) {
    Point temp = *this;
    ++(*this);
    return temp;
}

Point& Point::operator--() {
    x--; y--;
    return *this;
}

Point Point::operator--(int) {
    Point temp = *this;
    --(*this);
    return temp;
}
// main.cpp
#include "Triangle.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    std::cout << "Кiлькiсть об'єктiв Point: " << Point::getCount() << std::endl;
    std::cout << "Кiлькiсть об'єктiв Triangle: " << Triangle::getCount() << std::endl;

    Triangle triangle;
    triangle.Read();
    triangle.Display();

    std::cout << "Периметр: " << triangle.perimeter() << std::endl;
    std::cout << "Площа: " << triangle.area() << std::endl;
    std::cout << "Тип трикутника: " << triangle.triangleType() << std::endl;

    std::cout << "Кiлькiсть об'єктiв Point: " << Point::getCount() << std::endl;
    std::cout << "Кiлькiсть об'єктiв Triangle: " << Triangle::getCount() << std::endl;

    return 0;
}
