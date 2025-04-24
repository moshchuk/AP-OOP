// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include "TriangleException.h"

class Triangle {
private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& a, const Point& b, const Point& c) noexcept(false);
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

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
    if (a == b || b == c || c == a)
        throw TriangleException("Two or more points are identical. Not a valid triangle.");
    P1 = a; P2 = b; P3 = c;
}

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

double Triangle::getA() const { return P1.distanceTo(P2); }
double Triangle::getB() const { return P2.distanceTo(P3); }
double Triangle::getC() const { return P3.distanceTo(P1); }

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

double Triangle::getHeightA() const {
    return 2 * area() / getA();
}
double Triangle::getHeightB() const {
    return 2 * area() / getB();
}
double Triangle::getHeightC() const {
    return 2 * area() / getC();
}

double Triangle::perimeter() const {
    return getA() + getB() + getC();
}

double Triangle::area() const {
    double s = perimeter() / 2;
    return std::sqrt(s * (s - getA()) * (s - getB()) * (s - getC()));
}

std::string Triangle::triangleType() const {
    double a = getA(), b = getB(), c = getC();
    if (a == b && b == c)
        return "Equilateral";
    else if (a == b || b == c || a == c)
        return "Isosceles";
    else
        return "Scalene";
}

void Triangle::Read() {
    std::cin >> P1 >> P2 >> P3;
    if (P1 == P2 || P2 == P3 || P1 == P3)
        throw TriangleException("Invalid triangle: duplicate points.");
}

void Triangle::Display() const {
    std::cout << *this << "\n";
}

Triangle::operator std::string() const {
    return std::string(P1) + ", " + std::string(P2) + ", " + std::string(P3);
}

Triangle& Triangle::operator++() {
    ++P1; ++P2; ++P3; return *this;
}
Triangle Triangle::operator++(int) {
    Triangle temp = *this; ++(*this); return temp;
}
Triangle& Triangle::operator--() {
    --P1; --P2; --P3; return *this;
}
Triangle Triangle::operator--(int) {
    Triangle temp = *this; --(*this); return temp;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t) {
    return os << t.P1 << ", " << t.P2 << ", " << t.P3;
}
std::istream& operator>>(std::istream& is, Triangle& t) {
    is >> t.P1 >> t.P2 >> t.P3;
    return is;
}
// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <string>

class Point {
protected:
    double x, y;

public:
    Point() noexcept;
    Point(double x, double y) noexcept(false);
    Point(const Point& other) noexcept;
    virtual ~Point();

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

Point::Point() noexcept : x(0), y(0) {}
Point::Point(double x, double y) {
    if (x < -1e6 || y < -1e6) throw std::out_of_range("Coordinate value too small.");
    this->x = x; this->y = y;
}
Point::Point(const Point& other) noexcept : x(other.x), y(other.y) {}
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
    ++x; ++y; return *this;
}

Point Point::operator++(int) {
    Point temp = *this; ++(*this); return temp;
}

Point& Point::operator--() {
    --x; --y; return *this;
}

Point Point::operator--(int) {
    Point temp = *this; --(*this); return temp;
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
// TriangleException.h
#ifndef TRIANGLEEXCEPTION_H
#define TRIANGLEEXCEPTION_H

#include <stdexcept>
#include <string>

class TriangleException : public std::exception {
    std::string message;
public:
    explicit TriangleException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

#endif
// main.cpp
#include <iostream>
#include "Point.h"
#include "Triangle.h"
#include "TriangleException.h"

using namespace std;

void handleExceptionByValue() {
    try {
        cout << "\n[handleExceptionByValue] Введiть 3 однаковi точки:" << endl;
        Triangle t;
        t.Read();
        t.Display();
    }
    catch (TriangleException e) {  
        cout << "Exception (by value): " << e.what() << endl;
    }
}

void handleExceptionByReference() {
    try {
        cout << "\n[handleExceptionByReference] Створення трикутника з однаковими точками:" << endl;
        Point p(1, 1);
        Triangle t(p, p, p);  
        t.Display();
    }
    catch (const TriangleException& e) {  
        cout << "Exception (by reference): " << e.what() << endl;
    }
}

void handleExceptionByPointer() {
    try {
        cout << "\n[handleExceptionByPointer] Передача через покажчик:" << endl;
        throw new TriangleException("Pointer-based TriangleException thrown.");
    }
    catch (TriangleException* e) {  
        cout << "Exception (by pointer): " << e->what() << endl;
        delete e;
    }
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    try {
        cout << "=== Демонстрацiя класiв Point та Triangle ===\n";

        Point A(0, 0), B(4, 0), C(0, 3);
        Triangle T(A, B, C);

        cout << "\nТрикутник: " << T << endl;
        cout << "Сторони: A=" << T.getA() << ", B=" << T.getB() << ", C=" << T.getC() << endl;
        cout << "Кути: A=" << T.get_A() << ", B=" << T.get_B() << ", C=" << T.get_C() << endl;
        cout << "Периметр: " << T.perimeter() << endl;
        cout << "Площа: " << T.area() << endl;
        cout << "Тип: " << T.triangleType() << endl;

        cout << "\nОператор iнкременту (префiксний):\n";
        ++T;
        T.Display();

        cout << "\nОператор декременту (постфiксний):\n";
        T--;
        T.Display();
    }
    catch (const TriangleException& e) {
        cerr << "Головна помилка: " << e.what() << endl;
    }

    handleExceptionByValue();
    handleExceptionByReference();
    handleExceptionByPointer();

    return 0;
}
