//////////////////////////////////////////////////////////////////////////////
// Triangle.h 
// Заголовний файл 
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle {
private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    void Init(const Point& p1, const Point& p2, const Point& p3);
    void Read();
    void Display() const;
    std::string toString() const;
    const Point& getP1() const;
    const Point& getP2() const;
    const Point& getP3() const;
    void setP1(const Point& p1);
    void setP2(const Point& p2);
    void setP3(const Point& p3);
    double getA() const;
    double getB() const;
    double getC() const;
    double getAngleA() const;
    double getAngleB() const;
    double getAngleC() const;
    double area() const;
    double perimeter() const;
    std::string triangleType() const;
};

#endif
//////////////////////////////////////////////////////////////////////////////
// Triangle.cpp 
// Файл реалізації – реалізація методів класу

#include "triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle() : P1(), P2(), P3() {}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : P1(p1), P2(p2), P3(p3) {}

void Triangle::Init(const Point& p1, const Point& p2, const Point& p3) {
    P1 = p1;
    P2 = p2;
    P3 = p3;
}

void Triangle::Read() {
    std::cout << "Введiть координати вершини 1:" << std::endl;
    P1.Read();
    std::cout << "Введiть координати вершини 2:" << std::endl;
    P2.Read();
    std::cout << "Введiть координати вершини 3:" << std::endl;
    P3.Read();
}

void Triangle::Display() const {
    std::cout << "Трикутник з вершинами:" << std::endl;
    P1.Display();
    P2.Display();
    P3.Display();
}

std::string Triangle::toString() const {
    return "Трикутник з вершинами: " + P1.toString() + ", " + P2.toString() + ", " + P3.toString();
}

const Point& Triangle::getP1() const { return P1; }
const Point& Triangle::getP2() const { return P2; }
const Point& Triangle::getP3() const { return P3; }

void Triangle::setP1(const Point& p1) { P1 = p1; }
void Triangle::setP2(const Point& p2) { P2 = p2; }
void Triangle::setP3(const Point& p3) { P3 = p3; }

double Triangle::getA() const {
    return P2.distanceTo(P3);
}

double Triangle::getB() const {
    return P1.distanceTo(P3);
}

double Triangle::getC() const {
    return P1.distanceTo(P2);
}

double Triangle::getAngleA() const {
    double a = getA(), b = getB(), c = getC();
    return std::acos((b * b + c * c - a * a) / (2 * b * c));
}

double Triangle::getAngleB() const {
    double a = getA(), b = getB(), c = getC();
    return std::acos((a * a + c * c - b * b) / (2 * a * c));
}

double Triangle::getAngleC() const {
    double a = getA(), b = getB(), c = getC();
    return std::acos((a * a + b * b - c * c) / (2 * a * b));
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
    if (a * a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b) return "Прямокутний";
    return "Iнший";
}
//////////////////////////////////////////////////////////////////////////////
// Point.h 
// Заголовний файл 
#ifndef POINT_H
#define POINT_H

#include <string>
#include <cmath>

class Point {
private:
    double x, y;

public:
    Point();
    Point(double x, double y);
    void Init(double x, double y);
    void Read();
    void Display() const;
    std::string toString() const;
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void moveX(double dx);
    void moveY(double dy);
    double distanceToOrigin() const;
    double distanceTo(const Point& other) const;
    void toPolar(double& r, double& phi) const;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

#endif
//////////////////////////////////////////////////////////////////////////////
// Point.cpp 
// Файл реалізації – реалізація методів класу

#include "point.h"
#include <iostream>
#include <cmath>

Point::Point() : x(0), y(0) {}

Point::Point(double x, double y) : x(x), y(y) {}

void Point::Init(double x, double y) {
    this->x = x;
    this->y = y;
}

void Point::Read() {
    std::cout << "Введiть координату X: ";
    std::cin >> x;
    std::cout << "Введiть координату Y: ";
    std::cin >> y;
}

void Point::Display() const {
    std::cout << "Точка: (" << x << ", " << y << ")" << std::endl;
}

std::string Point::toString() const {
    return "Точка: (" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double Point::getX() const { return x; }
double Point::getY() const { return y; }

void Point::setX(double x) { this->x = x; }
void Point::setY(double y) { this->y = y; }

void Point::moveX(double dx) { x += dx; }
void Point::moveY(double dy) { y += dy; }

double Point::distanceToOrigin() const {
    return std::sqrt(x * x + y * y);
}

double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

void Point::toPolar(double& r, double& phi) const {
    r = distanceToOrigin();
    phi = std::atan2(y, x);
}

bool Point::operator==(const Point& other) const {
    return (x == other.x && y == other.y);
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}
