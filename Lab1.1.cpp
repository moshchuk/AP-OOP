//////////////////////////////////////////////////////////////////////////////
// Time.h 
// Заголовний файл – визначення класу

#pragma once
#include <iostream>
using namespace std;

class Time
{
private:
    int first;  // години
    int second; // хвилини

public:
    int GetFirst() const { return first; }
    int GetSecond() const { return second; }
    void SetFirst(int value);
    void SetSecond(int value);

    void Init(int h, int m);

    void Read();
    void Display() const;

    // Метод перетворення у хвилини
    int Minutes() const;
};

Time makeTime(int h, int m);
//////////////////////////////////////////////////////////////////////////////
// Time.cpp 
// Файл реалізації – реалізація методів класу

#include "Time.h"

void Time::SetFirst(int value)
{
    first = (value >= 0) ? value : 0;
}

void Time::SetSecond(int value)
{
    second = (value >= 0 && value < 60) ? value : 0;
}

void Time::Init(int h, int m)
{
    SetFirst(h);
    SetSecond(m);
}

void Time::Read()
{
    int h, m;
    cout << "Введiть години: ";
    cin >> h;
    cout << "Введiть хвилини: ";
    cin >> m;
    Init(h, m);
}

void Time::Display() const
{
    cout << "Час: " << first << " годин " << second << " хвилин" << endl;
}

int Time::Minutes() const
{
    return first * 60 + second;
}

Time makeTime(int h, int m)
{
    if (h < 0 || m < 0 || m >= 60)
    {
        cerr << "Помилка: некоректнi значення часу!" << endl;
        exit(1);
    }
    Time t;
    t.Init(h, m);
    return t;
}
//////////////////////////////////////////////////////////////////////////////
// main.cpp 
// Головний файл проекту – функція main
#include "Time.h"

int main()
{
    setlocale(LC_CTYPE, "ukr");
    Time t1;
    t1.Read();
    t1.Display();
    cout << "Час у хвилинах: " << t1.Minutes() << endl;

    return 0;
}
