// main.cpp
#include "date.h"

int main() {
    setlocale(LC_CTYPE, "ukr");
    Date date1;
    Date date2(18, DECEMBER, 2025);
    Date date3 = date2;

    std::cout << "Дата 1: " << date1 << std::endl;
    std::cout << "Дата 2: " << date2 << std::endl;
    std::cout << "Дата 3: " << date3 << std::endl;

    date1.setDay(1);
    date1.setMonth(JANUARY);
    date1.setYear(2024);

    std::cout << "Дата 1 пiсля модифiкацiї: " << date1 << std::endl;
    std::cout << "Кiлькiсть днiв у мiсяцi Дати 1: " << date1.getDaysInMonth() << std::endl;
    std::cout << "Дата 2 як рядок: " << std::string(date2) << std::endl;

    Date date4;
    std::cout << "Введiть дату (день мiсяць рiк): ";
    std::cin >> date4;
    if (std::cin.fail()) {
        std::cout << "Некоректний формат введення!" << std::endl;
    }
    else {
        std::cout << "Введена дата: " << date4 << std::endl;
    }

    return 0;
}
// date.h
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

enum Month {
    JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE,
    JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
};

struct MonthInfo {
    std::string name;
    int days;
};

class Date {
private:
    int day;
    Month month;
    int year;
    MonthInfo* months;
    static MonthInfo staticMonths[12];
    bool useStaticArray;

public:
    Date();
    Date(int day, Month month, int year, bool useStatic = false);
    Date(const Date& other);
    ~Date();

    int getDay() const;
    Month getMonth() const;
    int getYear() const;
    void setDay(int day);
    void setMonth(Month month);
    void setYear(int year);

    Date& operator=(const Date& other);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);
    operator std::string() const;

    int getDaysInMonth() const;
    static void setStaticMonths(const MonthInfo months[12]);
    bool isLeapYear() const;
};

#endif
// date.cpp
#include "date.h"

MonthInfo Date::staticMonths[12] = {
    {"Сiчень", 31}, {"Лютий", 28}, {"Березень", 31}, {"Квiтень", 30},
    {"Травень", 31}, {"Червень", 30}, {"Липень", 31}, {"Серпень", 31},
    {"Вересень", 30}, {"Жовтень", 31}, {"Листопад", 30}, {"Грудень", 31}
};

Date::Date() : day(1), month(JANUARY), year(1970), months(nullptr), useStaticArray(false) {
    months = new MonthInfo[12];
    for (int i = 0; i < 12; ++i) {
        months[i] = staticMonths[i];
    }
}

Date::Date(int day, Month month, int year, bool useStatic) : day(day), month(month), year(year), useStaticArray(useStatic) {
    if (!useStatic) {
        months = new MonthInfo[12];
        for (int i = 0; i < 12; ++i) {
            months[i] = staticMonths[i];
        }
    }
    else {
        months = staticMonths;
    }
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year), useStaticArray(other.useStaticArray) {
    if (!useStaticArray) {
        months = new MonthInfo[12];
        for (int i = 0; i < 12; ++i) {
            months[i] = other.months[i];
        }
    }
    else {
        months = staticMonths;
    }
}

Date::~Date() {
    if (months && !useStaticArray) {
        delete[] months;
    }
}

int Date::getDay() const {
    return day;
}

Month Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

void Date::setDay(int day) {
    this->day = day;
}

void Date::setMonth(Month month) {
    this->month = month;
}

void Date::setYear(int year) {
    this->year = year;
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
        useStaticArray = other.useStaticArray;
        if (!useStaticArray) {
            for (int i = 0; i < 12; ++i) {
                months[i] = other.months[i];
            }
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << " " << date.months[date.month].name << " " << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    int monthInt;
    is >> date.day >> monthInt >> date.year;

    if (monthInt >= JANUARY && monthInt <= DECEMBER) {
        date.month = static_cast<Month>(monthInt);
    }
    else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

Date::operator std::string() const {
    return std::to_string(day) + " " + months[month].name + " " + std::to_string(year);
}

int Date::getDaysInMonth() const {
    int days = months[month].days;
    if (month == FEBRUARY && isLeapYear()) {
        days = 29;
    }
    return days;
}

void Date::setStaticMonths(const MonthInfo months[12]) {
    for (int i = 0; i < 12; ++i) {
        Date::staticMonths[i] = months[i];
    }
}

bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
