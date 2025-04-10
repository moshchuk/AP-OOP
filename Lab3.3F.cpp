// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cmath>

class Point {
protected:
    double x, y;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);
    ~Point();

    Point& operator=(const Point& other);

    void moveX(double dx);
    void moveY(double dy);
    double distanceToOrigin() const;
    double distanceTo(const Point& other) const;
    void toPolar(double& r, double& angle) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Point& operator++();    
    Point operator++(int);  
    Point& operator--();    
    Point operator--(int);  

    operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};

#endif
// Point.cpp
#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const Point& other) : x(other.x), y(other.y) {}
Point::~Point() {}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

void Point::moveX(double dx) { x += dx; }
void Point::moveY(double dy) { y += dy; }

double Point::distanceToOrigin() const {
    return std::sqrt(x * x + y * y);
}

double Point::distanceTo(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

void Point::toPolar(double& r, double& angle) const {
    r = distanceToOrigin();
    angle = atan2(y, x);
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

Point& Point::operator++() {
    ++x;
    ++y;
    return *this;
}

Point Point::operator++(int) {
    Point temp = *this;
    ++(*this);
    return temp;
}

Point& Point::operator--() {
    --x;
    --y;
    return *this;
}

Point Point::operator--(int) {
    Point temp = *this;
    --(*this);
    return temp;
}

Point::operator std::string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}
// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle : public Point {
private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& a, const Point& b, const Point& c);
    Triangle(const Triangle& other);
    ~Triangle();

    Triangle& operator=(const Triangle& other);

    double getA() const;
    double getB() const;
    double getC() const;

    double get_A() const;
    double get_B() const;
    double get_C() const;

    double getHeightA() const;
    double getHeightB() const;
    double getHeightC() const;

    double perimeter() const;
    double area() const;
    std::string triangleType() const;

    void Read();
    void Display() const;

    operator std::string() const;

    Triangle& operator++();    
    Triangle operator++(int);  
    Triangle& operator--();    
    Triangle operator--(int);  

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
    friend std::istream& operator>>(std::istream& is, Triangle& t);
};

#endif
// Triangle.cpp
#include "Triangle.h"
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

Triangle::Triangle() : P1(), P2(), P3() {}
Triangle::Triangle(const Point& a, const Point& b, const Point& c) : P1(a), P2(b), P3(c) {}
Triangle::Triangle(const Triangle& other) : P1(other.P1), P2(other.P2), P3(other.P3) {}
Triangle::~Triangle() {}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        P1 = other.P1;
        P2 = other.P2;
        P3 = other.P3;
    }
    return *this;
}

double Triangle::getA() const { return P2.distanceTo(P3); }
double Triangle::getB() const { return P1.distanceTo(P3); }
double Triangle::getC() const { return P1.distanceTo(P2); }

double Triangle::get_A() const {
    double a = getA(), b = getB(), c = getC();
    return acos((b * b + c * c - a * a) / (2 * b * c)) * 180.0 / M_PI;
}

double Triangle::get_B() const {
    double a = getA(), b = getB(), c = getC();
    return acos((a * a + c * c - b * b) / (2 * a * c)) * 180.0 / M_PI;
}

double Triangle::get_C() const {
    double a = getA(), b = getB(), c = getC();
    return acos((a * a + b * b - c * c) / (2 * a * b)) * 180.0 / M_PI;
}

double Triangle::perimeter() const {
    return getA() + getB() + getC();
}

double Triangle::area() const {
    double a = getA(), b = getB(), c = getC();
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::getHeightA() const { return (2 * area()) / getA(); }
double Triangle::getHeightB() const { return (2 * area()) / getB(); }
double Triangle::getHeightC() const { return (2 * area()) / getC(); }

std::string Triangle::triangleType() const {
    double a = getA(), b = getB(), c = getC();
    if (a == b && b == c) return "Рiвностороннiй";
    if (a == b || b == c || a == c) return "Рiвнобедрений";
    if (std::abs(a * a + b * b - c * c) < 1e-6 || std::abs(a * a + c * c - b * b) < 1e-6 || std::abs(b * b + c * c - a * a) < 1e-6)
        return "Прямокутний";
    return "Звичайний";
}

void Triangle::Read() {
    std::cout << "Введiть 3 вершини трикутника:\n";
    std::cin >> P1 >> P2 >> P3;
}

void Triangle::Display() const {
    std::cout << *this << std::endl;
}

Triangle::operator std::string() const {
    return "Triangle(" + std::string(P1) + ", " + std::string(P2) + ", " + std::string(P3) + ")";
}

Triangle& Triangle::operator++() {
    ++P1; ++P2; ++P3;
    return *this;
}

Triangle Triangle::operator++(int) {
    Triangle temp = *this;
    ++(*this);
    return temp;
}

Triangle& Triangle::operator--() {
    --P1; --P2; --P3;
    return *this;
}

Triangle Triangle::operator--(int) {
    Triangle temp = *this;
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    os << "Трикутник: " << t.P1 << ", " << t.P2 << ", " << t.P3;
    return os;
}

std::istream& operator>>(std::istream& is, Triangle& t) {
    is >> t.P1 >> t.P2 >> t.P3;
    return is;
}
// main.cpp
#include "Triangle.h"
#include <iostream>
#include <iomanip>

#pragma pack(1)
struct PackedTriangle : public Triangle {};

int main() {
    setlocale(LC_CTYPE, "ukr");

    Triangle T1;
    std::cout << "Введення трикутника:\n";
    std::cin >> T1;

    std::cout << "\n=== Iнформація ===\n";
    std::cout << T1 << std::endl;
    std::cout << "Периметр: " << T1.perimeter() << std::endl;
    std::cout << "Площа: " << T1.area() << std::endl;
    std::cout << "Тип: " << T1.triangleType() << std::endl;

    std::cout << "\n=== Перевантаження ++ та -- ===\n";
    Triangle T2 = T1++;
    std::cout << "Пiсля T1++: " << T1 << std::endl;
    std::cout << "Копiя T2: " << T2 << std::endl;

    --T1;
    std::cout << "Пiсля --T1: " << T1 << std::endl;

    std::cout << "\nРозмiр класу Triangle: " << sizeof(Triangle) << " байт\n";
    std::cout << "Розмiр PackedTriangle (#pragma pack(1)): " << sizeof(PackedTriangle) << " байт\n";

    return 0;
}
