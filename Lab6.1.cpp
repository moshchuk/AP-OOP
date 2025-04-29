//main.cpp
#include "Array.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdexcept>
using namespace std;

Array processArray(double* arr, int size) {
    Array result;

    for (int i = 0; i < size; i++) {
        result.push_back(arr[i]);
    }

    double first_negative = 0;
    bool found_negative = false;
    for (int i = 0; i < result.size(); i++) {
        if (result[i] < 0) {
            first_negative = result[i];
            found_negative = true;
            break;
        }
    }

    if (found_negative) {
        for (int i = 0; i < result.size(); i++) {
            if (static_cast<int>(result[i]) % 2 == 0)
                result[i] *= first_negative;
        }
    }

    double sum = 0;
    double abs_sum = 0;
    for (int i = 0; i < result.size(); i++) {
        sum += result[i];
        abs_sum += abs(result[i]);
    }

    result.push_back(sum);
    result.push_back(abs_sum / result.size());

    return result;
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    srand((unsigned)time(NULL));

    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;

    double* a = new double[n];
    for (int i = 0; i < n; i++) {
        a[i] = -50 + rand() % 101; 
    }

    Array result = processArray(a, n);

    cout << "Оброблений масив:\n" << result;

    delete[] a;
    return 0;
}
// Array.h
#pragma once
#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

class Array {
public:
    typedef unsigned int UINT;
    typedef double value_type;
    typedef double* iterator;
    typedef const double* const_iterator;
    typedef double& reference;
    typedef const double& const_reference;
    typedef std::size_t size_type;

private:
    static const size_type minsize = 10;
    size_type Size;
    size_type Count;
    size_type First;
    value_type* elems;

public:
    Array(const size_type& n = minsize) throw(bad_alloc, invalid_argument);
    Array(const Array&) throw(bad_alloc);
    Array(const iterator first, const iterator last) throw(bad_alloc, invalid_argument);
    Array(const size_type first, const size_type last) throw(bad_alloc, invalid_argument);
    ~Array();
    Array& operator=(const Array&);

    iterator begin() { return elems; }
    const_iterator begin() const { return elems; }
    iterator end() { return elems + Count; }
    const_iterator end() const { return elems + Count; }

    size_type size() const;
    bool empty() const;
    size_type capacity() const;
    void resize(size_type newsize) throw(bad_alloc);

    reference operator[](size_type) throw(out_of_range);
    const_reference operator[](size_type) const throw(out_of_range);
    reference front() { return elems[0]; }
    const_reference front() const { return elems[0]; }
    reference back() { return elems[size() - 1]; }
    const_reference back() const { return elems[size() - 1]; }

    void push_back(const value_type& v);
    void pop_back();               
    void clear() { Count = 0; }
    void swap(Array& other);
    void assign(const value_type& v); 

    friend ostream& operator<<(ostream& out, const Array& a);
    friend istream& operator>>(istream& in, Array& a);
};
// Array.cpp
#include "Array.h"

Array::Array(const size_type& n) throw(bad_alloc, invalid_argument) {
    First = 0;
    Count = Size = n;
    elems = new value_type[Size];
    for (UINT i = 0; i < Size; i++)
        elems[i] = 0;
}

Array::Array(const iterator first, const iterator last) throw(bad_alloc, invalid_argument) {
    First = 0;
    if (first <= last) {
        Count = Size = (last - first) + 1;
        elems = new value_type[Size];
        for (UINT i = 0; i < Size; ++i)
            elems[i] = 0;
    }
    else {
        throw invalid_argument("Invalid range");
    }
}

Array::Array(const size_type first, const size_type last) throw(bad_alloc, invalid_argument) {
    if (first <= last) {
        First = first;
        Count = Size = (last - first) + 1;
        elems = new value_type[Size];
        for (UINT i = 0; i < Size; ++i)
            elems[i] = 0;
    }
    else {
        throw invalid_argument("Invalid range");
    }
}

Array::Array(const Array& t) throw(bad_alloc)
    : Size(t.Size), Count(t.Count), First(t.First), elems(new value_type[Size]) {
    for (UINT i = 0; i < Size; ++i)
        elems[i] = t.elems[i];
}

Array& Array::operator=(const Array& t) {
    Array tmp(t);
    swap(tmp);
    return *this;
}

Array::~Array() {
    delete[] elems;
    elems = nullptr;
}

void Array::push_back(const value_type& v) {
    if (Count == Size)
        resize(Size * 2);
    elems[Count++] = v;
}

void Array::pop_back() {
    if (Count > 0)
        --Count;
}

void Array::assign(const value_type& v) {
    for (size_type i = 0; i < Count; ++i)
        elems[i] = v;
}

Array::reference Array::operator[](size_type index) throw(out_of_range) {
    if ((First <= index) && (index < First + Size))
        return elems[index - First];
    else
        throw out_of_range("Index out of range!");
}

Array::const_reference Array::operator[](size_type index) const throw(out_of_range) {
    if ((First <= index) && (index < First + Size))
        return elems[index - First];
    else
        throw out_of_range("Index out of range!");
}

void Array::resize(size_type newsize) throw(bad_alloc) {
    if (newsize > capacity()) {
        value_type* data = new value_type[newsize];
        for (size_type i = 0; i < Count; ++i)
            data[i] = elems[i];
        delete[] elems;
        elems = data;
        Size = newsize;
    }
}

void Array::swap(Array& other) {
    std::swap(elems, other.elems);
    std::swap(Size, other.Size);
    std::swap(Count, other.Count);
    std::swap(First, other.First);
}

Array::size_type Array::capacity() const {
    return Size;
}

Array::size_type Array::size() const {
    return Count;
}

bool Array::empty() const {
    return Count == 0;
}

ostream& operator<<(ostream& out, const Array& tmp) {
    for (size_t j = 0; j < tmp.Count; j++)
        out << tmp[j] << " ";
    out << endl;
    return out;
}

istream& operator>>(istream& in, Array& tmp) {
    for (size_t j = 0; j < tmp.Count; j++)
        in >> tmp[j];
    return in;
}
