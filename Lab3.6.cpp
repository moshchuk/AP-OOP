// B1.cpp
#include "B.1.h"

B1::B1(int val) : b1(val) {}
B1::~B1() {}
void B1::show() {
    cout << "class B1:" << endl;
    cout << "B1::b1 = " << b1 << endl << endl;
}
// B1.h
#pragma once
#include <iostream>
using namespace std;

class B1 {
protected:
    int b1;
public:
    B1(int val);
    ~B1();
    void show();
};
// B2.cpp
#include "B.2.h"

B2::B2(int val) : b2(val) {}
B2::~B2() {}
void B2::show() {
    cout << "class B2:" << endl;
    cout << "B2::b2 = " << b2 << endl << endl;
}
// B2.h
#pragma once
#include <iostream>
using namespace std;

class B2 {
protected:
    int b2;
public:
    B2(int val);
    ~B2();
    void show();
};
// D1.cpp
#include "D.1.h"

D1::D1(int val, int b1_val) : B1(b1_val), d1(val) {}
D1::~D1() {}
void D1::show() {
    cout << "class D1:" << endl;
    B1::show();
    cout << "D1::d1 = " << d1 << endl << endl;
}
// D1.h
#pragma once
#include "B.1.h"

class D1 : public B1 {
protected:
    int d1;
public:
    D1(int val, int b1_val);
    ~D1();
    void show();
};
// D2.cpp
#include "D.2.h"

D2::D2(int val, int d1_val, int b1_val, int b2_val)
    : D1(d1_val, b1_val), B2(b2_val), d2(val) {
}
D2::~D2() {}
void D2::show() {
    cout << "class D2:" << endl;
    D1::show();
    B2::show();
    cout << "D2::d2 = " << d2 << endl << endl;
}
// D2.h
#pragma once
#include "D.1.h"
#include "B.2.h"

class D2 : private D1, private B2 {
protected:
    int d2;
public:
    D2(int val, int d1_val, int b1_val, int b2_val);
    ~D2();
    void show();
};
// D3.cpp
#include "D.3.h"

D3::D3(int val, int d2_val, int d1_val, int b1_val, int b2_val)
    : D2(d2_val, d1_val, b1_val, b2_val), d3(val) {
}
D3::~D3() {}
void D3::show() {
    cout << "class D3:" << endl;
    D2::show();
    cout << "D3::d3 = " << d3 << endl << endl;
}
// D3.h
#pragma once
#include "D.2.h"

class D3 : public D2 {
    int d3;
public:
    D3(int val, int d2_val, int d1_val, int b1_val, int b2_val);
    ~D3();
    void show();
};
// main.cpp
#include <iostream>
#include <Windows.h>
#include "B.1.h"
#include "B.2.h"
#include "D.1.h"
#include "D.2.h"
#include "D.3.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    B1 obj_b1(11);
    cout << "sizeof(B1) = " << sizeof(B1) << endl;
    obj_b1.show();

    B2 obj_b2(22);
    cout << "sizeof(B2) = " << sizeof(B2) << endl;
    obj_b2.show();

    D1 obj_d1(33, 44);
    cout << "sizeof(D1) = " << sizeof(D1) << endl;
    obj_d1.show();

    D2 obj_d2(55, 66, 77, 88);
    cout << "sizeof(D2) = " << sizeof(D2) << endl;
    obj_d2.show();

    D3 obj_d3(99, 101, 102, 103, 104);
    cout << "sizeof(D3) = " << sizeof(D3) << endl;
    obj_d3.show();

    return 0;
}
