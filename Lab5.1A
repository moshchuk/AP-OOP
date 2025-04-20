// TimeException.h
#pragma once
#include <exception>
#include <stdexcept>
#include <string>

class MyTimeException : public std::exception {
    std::string message;
public:
    MyTimeException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MyInvalidArgument : public std::invalid_argument {
public:
    MyInvalidArgument(const std::string& msg) : std::invalid_argument(msg) {}
};
// Time.h
#pragma once
#include <iostream>
#include <string>
#include "TimeException.h"

class Time {
private:
    int first;  
    int second; 

public:
    Time() throw();
    Time(int h, int m) throw(std::invalid_argument);
    Time(const Time& other) throw();

    Time& operator=(const Time& other) throw();

    friend std::istream& operator>>(std::istream& is, Time& t);
    friend std::ostream& operator<<(std::ostream& os, const Time& t);

    operator std::string() const throw();

    Time& operator++();    
    Time operator++(int);   
    Time& operator--();     
    Time operator--(int);   

    int GetFirst() const throw() { return first; }
    int GetSecond() const throw() { return second; }
    void SetFirst(int value) throw(std::invalid_argument);
    void SetSecond(int value) throw(MyInvalidArgument&);

    int Minutes() const throw(MyTimeException*);

    void Init(int h, int m) throw(std::invalid_argument);
};

Time makeTime(int h, int m);
// Time.cpp
#include "Time.h"
#include <cstdlib> 
#include <exception>

Time::Time() throw() : first(0), second(0) {}

Time::Time(int h, int m) throw(std::invalid_argument) {
    SetFirst(h);
    try {
        SetSecond(m);
    }
    catch (MyInvalidArgument& e) {
        std::cerr << "Помилка в конструкторі: " << e.what() << std::endl;
        throw;
    }
}

Time::Time(const Time& other) throw() : first(other.first), second(other.second) {}

Time& Time::operator=(const Time& other) throw() {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, Time& t) {
    std::cout << "Введiть години: ";
    is >> t.first;
    std::cout << "Введiть хвилини: ";
    is >> t.second;
    t.SetFirst(t.first);
    t.SetSecond(t.second);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
    os << t.first << " годин " << t.second << " хвилин";
    return os;
}

Time::operator std::string() const throw() {
    return std::to_string(first) + " годин " + std::to_string(second) + " хвилин";
}

Time& Time::operator++() {
    SetFirst(++first);
    return *this;
}

Time Time::operator++(int) {
    Time temp = *this;
    SetSecond(second + 1);
    return temp;
}

Time& Time::operator--() {
    SetFirst(--first);
    return *this;
}

Time Time::operator--(int) {
    Time temp = *this;
    SetSecond(second - 1);
    return temp;
}

void Time::SetFirst(int value) throw(std::invalid_argument) {
    if (value < 0) throw std::invalid_argument("Години не можуть бут вiд’ємними");
    first = value;
}

void Time::SetSecond(int value) throw(MyInvalidArgument&) {
    if (value < 0 || value >= 60) {
        MyInvalidArgument e("Хвилини повиннi бути в межах [0; 59]");
        throw e;
    }
    second = value;
}

int Time::Minutes() const throw(MyTimeException*) {
    if (first == 0 && second == 0) {
        throw new MyTimeException("Час не встановлено!");
    }
    return first * 60 + second;
}

void Time::Init(int h, int m) throw(std::invalid_argument) {
    SetFirst(h);
    SetSecond(m);
}

Time makeTime(int h, int m) {
    try {
        if (h < 0 || m < 0 || m >= 60) {
            throw std::bad_exception();
        }
    }
    catch (std::bad_exception& e) {
        std::cerr << "bad_exception: Некоректнi аргументи: " << e.what() << std::endl;
        exit(1);
    }
    return Time(h, m);
}
// main.cpp
#include "Time.h"
#include <iostream>

int main() {
    setlocale(LC_CTYPE, "ukr");

    Time t1;
    Time t2(10, 30);
    Time t3 = t2;
    Time t4 = makeTime(12, 45);
    Time arr[2] = { t1, t2 };

#pragma pack(1)
    std::cout << "Розмiр класу з #pragma pack(1): " << sizeof(Time) << std::endl;
#pragma pack()
    std::cout << "Розмiр класу без #pragma pack(1): " << sizeof(Time) << std::endl;

    std::cin >> t1;
    std::cout << "t1: " << t1 << std::endl;

    std::string s = static_cast<std::string>(t1);
    std::cout << "t1 як рядок: " << s << std::endl;

    std::cout << "t1++: " << t1++ << std::endl;
    std::cout << "++t1: " << ++t1 << std::endl;
    std::cout << "t1--: " << t1-- << std::endl;
    std::cout << "--t1: " << --t1 << std::endl;

    try {
        std::cout << "t1 у хвилинах: " << t1.Minutes() << std::endl;
    }
    catch (MyTimeException* e) {
        std::cerr << "MyTimeException: " << e->what() << std::endl;
        delete e;
    }

    std::cout << "Масив arr:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        std::cout << arr[i] << std::endl;
    }

    try {
        Time t5(-3, 30);
    }
    catch (std::invalid_argument& e) {
        std::cerr << "std::invalid_argument: " << e.what() << std::endl;
    }

    try {
        Time t6;
        t6.SetSecond(70);
    }
    catch (MyInvalidArgument& e) {
        std::cerr << "MyInvalidArgument: " << e.what() << std::endl;
    }

    return 0;
}
