// Factory.cpp
#include "Factory.h"
SymString* Factory::createSymString(const std::string& id, const std::string& val) {
    return new SymString(id, val);
}

OctString* Factory::createOctString(const std::string& id, const std::string& val) {
    return new OctString(id, val);
}

void Factory::destroy(Object* obj) {
    delete obj;
}
// Factory.h
#ifndef FACTORY_H
#define FACTORY_H

#include "SymString.h"
#include "OctString.h"

class Factory {
public:
    static SymString* createSymString(const std::string& id, const std::string& val);
    static OctString* createOctString(const std::string& id, const std::string& val);
    static void destroy(Object* obj);
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

int Object::getCount()
{
    return 0;
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
// OctString.cpp
#include "OctString.h"
#include <sstream>

OctString::OctString() : SymString() {}

OctString::OctString(const std::string& id, const std::string& octVal) : SymString(id, octVal) {}

OctString::OctString(const OctString& other) : SymString(other) {}

OctString& OctString::operator=(const OctString& other) {
    SymString::operator=(other);
    return *this;
}

void OctString::Show() const {
    std::cout << "OctString [" << id << "]: " << value << std::endl;
}

void OctString::ShowDec() const {
    int decValue = std::stoi(value, nullptr, 8);
    std::cout << "Decimal: " << decValue << std::endl;
}

OctString operator+(const OctString& o1, const OctString& o2) {
    int v1 = std::stoi(o1.value, nullptr, 8);
    int v2 = std::stoi(o2.value, nullptr, 8);
    int sum = v1 + v2;

    std::stringstream ss;
    ss << std::oct << sum;
    return OctString(o1.id + "_" + o2.id, ss.str());
}
// OctString.h
#ifndef OCTSTRING_H
#define OCTSTRING_H

#include "SymString.h"

class OctString : public SymString {
public:
    OctString();
    OctString(const std::string& id, const std::string& octVal);
    OctString(const OctString& other);
    OctString& operator=(const OctString& other);

    void Show() const override;
    void ShowDec() const override;

    friend OctString operator+(const OctString& o1, const OctString& o2);
};

#endif
// SymString.cpp
#include "SymString.h"

SymString::SymString() : id(""), value("") {}

SymString::SymString(const std::string& id, const std::string& val) : id(id), value(val) {}

SymString::SymString(const SymString& other) : id(other.id), value(other.value) {}

SymString& SymString::operator=(const SymString& other) {
    if (this != &other) {
        id = other.id;
        value = other.value;
    }
    return *this;
}

void SymString::Show() const {
    std::cout << "SymString [" << id << "]: " << value << std::endl;
}

void SymString::ShowDec() const {
    std::cout << "Decimal value not supported for SymString." << std::endl;
}

SymString operator+(const SymString& s1, const SymString& s2) {
    return SymString(s1.id + "_" + s2.id, s1.value + s2.value);
}
// SymString.h
#ifndef SYMSTRING_H
#define SYMSTRING_H

#include "Object.h"
#include <string>
#include <iostream>

class SymString : public Object {
protected:
    std::string id;
    std::string value;
public:
    SymString();
    SymString(const std::string& id, const std::string& val);
    SymString(const SymString& other);
    SymString& operator=(const SymString& other);

    virtual void Show() const;
    virtual void ShowDec() const;

    friend SymString operator+(const SymString& s1, const SymString& s2);
};

#endif
// main.cpp
#include "Factory.h"
#include <iostream>
#include <vector>

int main() {
    setlocale(LC_CTYPE, "ukr");

    std::vector<Object*> objects;
    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Створити SymString\n";
        std::cout << "2. Створити OctString\n";
        std::cout << "3. Показати всi об'єкти\n";
        std::cout << "4. Показати десяткове значення OctString\n";
        std::cout << "5. Об'єднати два OctString (+)\n";
        std::cout << "6. Вийти\nВаш вибiр: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, val;
            std::cout << "Введiть ID i значення: ";
            std::cin >> id >> val;
            objects.push_back(Factory::createSymString(id, val));
        }
        else if (choice == 2) {
            std::string id, val;
            std::cout << "Введiть ID i вiсiмкове значення: ";
            std::cin >> id >> val;
            objects.push_back(Factory::createOctString(id, val));
        }
        else if (choice == 3) {
            for (auto obj : objects) {
                dynamic_cast<SymString*>(obj)->Show();
            }
        }
        else if (choice == 4) {
            for (auto obj : objects) {
                if (auto o = dynamic_cast<OctString*>(obj)) {
                    o->Show();
                    o->ShowDec();
                }
            }
        }
        else if (choice == 5) {
            int i1, i2;
            std::cout << "Iндекси об'єктiв OctString для додавання: ";
            std::cin >> i1 >> i2;
            if (i1 < objects.size() && i2 < objects.size()) {
                auto o1 = dynamic_cast<OctString*>(objects[i1]);
                auto o2 = dynamic_cast<OctString*>(objects[i2]);
                if (o1 && o2) {
                    OctString* res = new OctString(*o1 + *o2);
                    res->Show();
                    res->ShowDec();
                    objects.push_back(res);
                }
            }
        }
    } while (choice != 6);

    for (auto obj : objects) {
        Factory::destroy(obj);
    }

    std::cout << "Загальна кiлькiсть об'єктiв: " << Object::getCount() << std::endl;
    return 0;
}
