//////////////////////////////////////////////////////////////////////////////
// Triangle.h 
// Заголовний файл 
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include <cmath>
#include <iostream>

class Triangle {
public:
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
        double distanceTo(const Point& other) const;
    };

private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    void Init(const Point& p1, const Point& p2, const Point& p3);
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
//////////////////////////////////////////////////////////////////////////////
// Triangle.cpp 
// Файл реалізації – реалізація методів класу
#include "triangle.h"

Triangle::Point::Point() : x(0), y(0) {}

Triangle::Point::Point(double x, double y) : x(x), y(y) {}

void Triangle::Point::Init(double x, double y) {
    this->x = x;
    this->y = y;
}

void Triangle::Point::Read() {
    std::cout << "Введiть координату X: ";
    std::cin >> x;
    std::cout << "Введiть координату Y: ";
    std::cin >> y;
}

void Triangle::Point::Display() const {
    std::cout << "Точка: (" << x << ", " << y << ")" << std::endl;
}

std::string Triangle::Point::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double Triangle::Point::getX() const { return x; }

double Triangle::Point::getY() const { return y; }

void Triangle::Point::setX(double x) { this->x = x; }

void Triangle::Point::setY(double y) { this->y = y; }

double Triangle::Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

Triangle::Triangle() : P1(), P2(), P3() {}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : P1(p1), P2(p2), P3(p3) {}

void Triangle::Init(const Point& p1, const Point& p2, const Point& p3) {
    P1 = p1;
    P2 = p2;
    P3 = p3;
}

void Triangle::Read() {
    std::cout << "Введiть координати першої вершини:" << std::endl;
    P1.Read();
    std::cout << "Введiть координати другої вершини:" << std::endl;
    P2.Read();
    std::cout << "Введiть координати третьої вершини:" << std::endl;
    P3.Read();
}

void Triangle::Display() const {
    std::cout << "Трикутник з вершинами:" << std::endl;
    P1.Display();
    P2.Display();
    P3.Display();
}

std::string Triangle::toString() const {
    return "Трикутник: " + P1.toString() + ", " + P2.toString() + ", " + P3.toString();
}

double Triangle::getA() const {
    return P2.distanceTo(P3);
}

double Triangle::getB() const {
    return P1.distanceTo(P3);
}

double Triangle::getC() const {
    return P1.distanceTo(P2);
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
    if (std::abs(a * a + b * b - c * c) < 1e-6 ||
        std::abs(a * a + c * c - b * b) < 1e-6 ||
        std::abs(b * b + c * c - a * a) < 1e-6)
        return "Прямокутний";
    return "Загальний";
}
//////////////////////////////////////////////////////////////////////////////
// Lab1.8.cpp 
// головний файл
#include "triangle.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    Triangle triangle;
    triangle.Read();
    triangle.Display();

    std::cout << "Площа: " << triangle.area() << std::endl;
    std::cout << "Периметр: " << triangle.perimeter() << std::endl;
    std::cout << "Вид трикутника: " << triangle.triangleType() << std::endl;

    return 0;
}
