#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

template <class T>
class vector {
    T* v;
    int size;
public:
    vector(int newsize);
    vector(const vector& x);
    ~vector();
    T extr(const char*);
    vector& sort(const char*);
    double norma();
    friend vector<T> operator + <>(vector<T>& x, vector<T>& y);
    vector& operator += (vector& y);
    T& operator [] (int index);
    vector& operator = (const vector& x);
    friend istream& operator >> <>(istream& is, vector& x);
    friend ostream& operator << <>(ostream& os, vector& x);
};

template <class T>
vector<T>::vector(int newsize) {
    v = new T[size = newsize];
    for (int i = 0; i < size; i++)
        v[i] = T();
}

template <class T>
vector<T>::vector(const vector<T>& x) {
    v = new T[size = x.size];
    for (int i = 0; i < size; i++)
        v[i] = x.v[i];
}

template <class T>
vector<T>::~vector() {
    delete[] v;
}

template <class T>
T vector<T>::extr(const char* MinOrMax) {
    T ext = v[0];
    for (int i = 0; i < size; i++) {
        if (!strcmp(MinOrMax, "min")) {
            if (v[i] < ext) ext = v[i];
        }
        else {
            if (v[i] > ext) ext = v[i];
        }
    }
    return ext;
}

template <class T>
vector<T>& vector<T>::sort(const char* UpOrDown) {
    T temp;
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if ((!strcmp(UpOrDown, "up") && v[i] > v[j]) ||
                (strcmp(UpOrDown, "up") && v[i] < v[j])) {
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
    return *this;
}

template <class T>
double vector<T>::norma() {
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum += v[i] * v[i];
    return sqrt(sum);
}

template <class T>
vector<T> operator + (vector<T>& x, vector<T>& y) {
    if (x.size != y.size)
        throw exception("Розміри векторів повинні бути однакові");
    vector<T> z(x.size);
    for (int i = 0; i < x.size; i++)
        z.v[i] = x.v[i] + y.v[i];
    return z;
}

template <class T>
vector<T>& vector<T>::operator += (vector<T>& y) {
    for (int i = 0; i < size; i++)
        v[i] += y.v[i];
    return *this;
}

template <class T>
T& vector<T>::operator [] (int index) {
    if (index < 0 || index >= size)
        throw exception("Індекс поза межами");
    return v[index];
}

template <class T>
vector<T>& vector<T>::operator = (const vector<T>& x) {
    if (this != &x) {
        delete[] v;
        v = new T[size = x.size];
        for (int i = 0; i < size; i++)
            v[i] = x.v[i];
    }
    return *this;
}

template <class T>
istream& operator >> (istream& is, vector<T>& x) {
    for (int i = 0; i < x.size; i++) {
        cout << "елемент[" << i << "] = ";
        is >> x.v[i];
    }
    return is;
}

template <class T>
ostream& operator << (ostream& os, vector<T>& x) {
    for (int i = 0; i < x.size; i++)
        os << x.v[i] << ' ';
    os << endl;
    return os;
}

template <typename T>
T average(T* arr, int size) {
    T sum = T();
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum / size;
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    try {
        int n;
        cout << "Введiть кiлькiсть елементiв у векторах: ";
        cin >> n;

        vector<int> A(n), B(n), C(n), D(n);

        cout << "Введiть елементи вектора A:\n";
        cin >> A;
        cout << "Введiть елементи вектора B:\n";
        cin >> B;

        C = A + B;
        cout << "Сума векторiв A + B:\n" << C;

        D += A;
        D += B;
        cout << "Накопичена сума D:\n" << D;

        cout << "Мiнiмальний елемент D: " << D.extr("min") << endl;
        D.sort("up");
        cout << "Вектор D пiсля сортування за зростанням:\n" << D;
        cout << "Норма вектора D: " << D.norma() << endl;

        int* masiv = new int[n];
        for (int i = 0; i < n; i++) masiv[i] = D[i];
        cout << "Середнє значення: " << average(masiv, n) << endl;
        delete[] masiv;
    }
    catch (exception& e) {
        cerr << "Помилка: " << e.what() << endl;
    }
    return 0;
}
