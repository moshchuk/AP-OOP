// String.h
#ifndef STRING_H
#define STRING_H

#include "Array.h"
#include <string>

class String : public Array {
public:
    String();
    String(const std::string& str);
    String(const String& other);
    String& operator=(const String& other);

    int getLength() const;
    int find(const String& substr) const;
    void remove(int pos, int len);
    void insert(int pos, const String& substr);
    void concat(const String& other);

    operator std::string() const;

    friend std::istream& operator>>(std::istream& in, String& str);
    friend std::ostream& operator<<(std::ostream& out, const String& str);
};

#endif
// Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <algorithm>

class Array {
protected:
    static const int MAX_SIZE = 256;
    char data[MAX_SIZE];

    bool rangeCheck(int index) const;

public:
    Array();
    Array(int len, char fill = 0);
    Array(const Array& other);

    char& operator[](int index);
    const char& operator[](int index) const;

    friend std::ostream& operator<<(std::ostream& out, const Array& arr);
    friend std::istream& operator>>(std::istream& in, Array& arr);
};

#endif
// Array.cpp
#include "Array.h"
#include <stdexcept>

Array::Array() {
    std::fill(data, data + MAX_SIZE, 0);
}

Array::Array(int len, char fill) {
    if (len < 0 || len >= MAX_SIZE) {
        std::cerr << "Недопустима довжина масиву!" << std::endl;
        exit(1);
    }
    data[0] = len;
    std::fill(data + 1, data + 1 + len, fill);
    std::fill(data + 1 + len, data + MAX_SIZE, 0);
}

Array::Array(const Array& other) {
    std::copy(other.data, other.data + MAX_SIZE, data);
}

bool Array::rangeCheck(int index) const {
    return index >= 0 && index < MAX_SIZE;
}

char& Array::operator[](int index) {
    if (!rangeCheck(index)) {
        std::cerr << "Недопустимий індекс доступу!" << std::endl;
        exit(1);
    }
    return data[index];
}

const char& Array::operator[](int index) const {
    if (!rangeCheck(index)) {
        std::cerr << "Недопустимий індекс доступу!" << std::endl;
        exit(1);
    }
    return data[index];
}

std::ostream& operator<<(std::ostream& out, const Array& arr) {
    for (int i = 0; i < Array::MAX_SIZE; ++i) {
        out << arr.data[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, Array& arr) {
    std::string input;
    in >> input;
    if (input.length() >= Array::MAX_SIZE) {
        std::cerr << "Вхідний рядок задовгий!" << std::endl;
        exit(1);
    }
    arr.data[0] = input.length();
    for (int i = 1; i <= input.length(); ++i) {
        arr.data[i] = input[i - 1];
    }
    return in;
}

// String.cpp
#include "String.h"
#include <iostream>
#include <cstring>

String::String() : Array() {}

String::String(const std::string& str) {
    if (str.length() > MAX_SIZE - 1) {
        std::cerr << "Рядок задовгий!" << std::endl;
        exit(1);
    }
    data[0] = static_cast<char>(str.length());
    for (int i = 1; i <= str.length(); ++i) {
        data[i] = str[i - 1];
    }
}

String::String(const String& other) : Array(other) {}

String& String::operator=(const String& other) {
    if (this != &other) {
        std::copy(other.data, other.data + MAX_SIZE, data);
    }
    return *this;
}

int String::getLength() const {
    return static_cast<unsigned char>(data[0]);
}

int String::find(const String& substr) const {
    int n = getLength();
    int m = substr.getLength();

    for (int i = 1; i <= n - m + 1; ++i) {
        bool match = true;
        for (int j = 1; j <= m; ++j) {
            if (data[i + j - 1] != substr.data[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }
    return -1;
}

void String::remove(int pos, int len) {
    int l = getLength();
    if (pos < 1 || pos + len - 1 > l) {
        std::cerr << "Некоректна позицiя видалення!" << std::endl;
        exit(1);
    }
    for (int i = pos + len; i <= l; ++i) {
        data[i - len] = data[i];
    }
    data[0] = static_cast<char>(l - len);
}

void String::insert(int pos, const String& substr) {
    int l = getLength();
    int sl = substr.getLength();
    if (pos < 1 || pos > l + 1 || l + sl > MAX_SIZE - 1) {
        std::cerr << "Некоректна вставка!" << std::endl;
        exit(1);
    }
    for (int i = l; i >= pos; --i) {
        data[i + sl] = data[i];
    }
    for (int i = 1; i <= sl; ++i) {
        data[pos + i - 1] = substr.data[i];
    }
    data[0] = static_cast<char>(l + sl);
}

void String::concat(const String& other) {
    int l = getLength();
    int ol = other.getLength();
    if (l + ol > MAX_SIZE - 1) {
        std::cerr << "Результат перевищує максимальну довжину!" << std::endl;
        exit(1);
    }
    for (int i = 1; i <= ol; ++i) {
        data[l + i] = other.data[i];
    }
    data[0] = static_cast<char>(l + ol);
}

String::operator std::string() const {
    return std::string(data + 1, data + 1 + getLength());
}

std::istream& operator>>(std::istream& in, String& str) {
    std::string temp;
    in >> temp;
    str = String(temp);
    return in;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
    out << std::string(str);
    return out;
}
// main.cpp
#include "String.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "ukr");
    String a("Привiт"), b("Свiт");

    std::cout << "Рядок a: " << a << "\n";
    std::cout << "Рядок b: " << b << "\n";

    a.concat(b);
    std::cout << "Пiсля зчеплення: " << a << "\n";

    String sub("Свiт");
    int pos = a.find(sub);
    std::cout << "Пошук 'Свiт': позицiя = " << pos << "\n";

    a.remove(7, 3);
    std::cout << "Пiсля видалення 'Свiт': " << a << "\n";

    a.insert(7, sub);
    std::cout << "Пiсля вставки 'Свiт': " << a << "\n";

    return 0;
}
