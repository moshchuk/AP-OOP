// Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle : public Point {
private:
    Point P1, P2, P3;

public:
    Triangle();
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    Triangle(const Triangle& other);

    void Read();
    void Display() const;
    std::string toString() const;

    Triangle& operator=(const Triangle& other);
    Triangle& operator++();
    Triangle operator++(int);
    Triangle& operator--();
    Triangle operator--(int);

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

void Triangle::Read() {
    std::cout << "Введiть вершини трикутника:\n";
    P1.Read();
    P2.Read();
    P3.Read();
}

void Triangle::Display() const {
    std::cout << toString() << std::endl;
}

std::string Triangle::toString() const {
    return "Трикутник(" + P1.toString() + ", " + P2.toString() + ", " + P3.toString() + ")";
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        P1 = other.P1;
        P2 = other.P2;
        P3 = other.P3;
    }
    return *this;
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
    if (fabs(a - b) < 1e-6 && fabs(b - c) < 1e-6) return "Рiвностороннiй";
    if (fabs(a - b) < 1e-6 || fabs(b - c) < 1e-6 || fabs(a - c) < 1e-6) return "Рiвнобедрений";
    if (fabs(a * a + b * b - c * c) < 1e-6 || fabs(a * a + c * c - b * b) < 1e-6 || fabs(b * b + c * c - a * a) < 1e-6)
        return "Прямокутний";
    return "Рiзностороннiй";
}
// Point.cpp
#include "Point.h"

Point::Point() : x(0), y(0) {}
Point::Point(double x, double y) : x(x), y(y) {}
Point::Point(const Point& other) : Object(other), x(other.x), y(other.y) {}

void Point::setX(double value) { x = value; }
void Point::setY(double value) { y = value; }
double Point::getX() const { return x; }
double Point::getY() const { return y; }

void Point::Read() {
    std::cout << "Введiть координати точки (x y): ";
    std::cin >> x >> y;
}

void Point::Display() const {
    std::cout << toString();
}

std::string Point::toString() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

Point& Point::operator++() {
    ++x; ++y;
    return *this;
}

Point Point::operator++(int) {
    Point temp = *this;
    ++(*this);
    return temp;
}

Point& Point::operator--() {
    --x; --y;
    return *this;
}

Point Point::operator--(int) {
    Point temp = *this;
    --(*this);
    return temp;
}

double Point::distanceTo(const Point& other) const {
    return std::hypot(x - other.x, y - other.y);
}

double Point::distanceToOrigin() const {
    return std::hypot(x, y);
}

void Point::toPolar(double& r, double& theta) const {
    r = distanceToOrigin();
    theta = atan2(y, x);
}
// Point.h
#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <cmath>
#include "Object.h"

class Point : public Object {
private:
    double x, y;

public:
    Point();
    Point(double x, double y);
    Point(const Point& other);

    void setX(double value);
    void setY(double value);
    double getX() const;
    double getY() const;

    void Read();
    void Display() const;
    std::string toString() const;

    Point& operator=(const Point& other);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

    Point& operator++();
    Point operator++(int);
    Point& operator--();
    Point operator--(int);

    double distanceTo(const Point& other) const;
    double distanceToOrigin() const;
    void toPolar(double& r, double& theta) const;
};

#endif
// Object.cpp
#include "Object.h"

int Object::count = 0;

Object::Object() {
    ++count;
}

Object::~Object() {
    --count;
}

int Object::getCount() {
    return count;
}
// Object.h
#ifndef OBJECT_H
#define OBJECT_H

class Object {
protected:
    static int count;

public:
    Object();
    virtual ~Object();
    static int getCount();
};

#endif

// main.cpp
#include "Triangle.h"
#include <iostream>
#include <iomanip>

#pragma pack(push, 1)
class PackedTriangle : public Triangle {};
#pragma pack(pop)

int main() {
    setlocale(LC_ALL, "ukr");

    Triangle t1;
    t1.Read();
    t1.Display();

    std::cout << "\nПериметр: " << t1.perimeter();
    std::cout << "\nПлоща: " << t1.area();
    std::cout << "\nТип: " << t1.triangleType();
    std::cout << "\nКути: A = " << t1.get_A() << ", B = " << t1.get_B() << ", C = " << t1.get_C();
    std::cout << "\nВисоти: hA = " << t1.getHeightA() << ", hB = " << t1.getHeightB() << ", hC = " << t1.getHeightC();

    std::cout << "\nРядкове представлення: " << t1.toString();

    Triangle t2 = t1;
    ++t2;
    std::cout << "\nПiсля iнкремента: " << t2.toString();

    --t2;
    std::cout << "\nПiсля декремента: " << t2.toString();

    std::cout << "\nКiлькiсть створених об'єктiв: " << Object::getCount();

    std::cout << "\nРозмiр класу Triangle без pack(1): " << sizeof(Triangle);
    std::cout << "\nРозмiр класу Triangle з pack(1): " << sizeof(PackedTriangle);

    return 0;
}
