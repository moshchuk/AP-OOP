#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class BitString {
private:
    long high; // Старші 32 біти
    long low;  // Молодші 32 біти

public:
    BitString() : high(0), low(0) {}
    BitString(long h, long l) : high(h), low(l) {}

    long getHigh() const { return high; }
    long getLow() const { return low; }
    void setHigh(long h) { high = h; }
    void setLow(long l) { low = l; }

    void Init(long h, long l) {
        high = h;
        low = l;
    }

    void Read() {
        cout << "Введiть старшi 32 бiти: ";
        cin >> high;
        cout << "Введiть молодшi 32 бiти: ";
        cin >> low;
    }

    void Display() const {
        cout << "BitString: " << toString() << endl;
    }

    // Метод перетворення до літерного рядка
    string toString() const {
        stringstream ss;
        ss << "High: " << high << " Low: " << low;
        return ss.str();
    }

    BitString Not() const {
        return BitString(~high, ~low);
    }

    BitString And(const BitString& other) const {
        return BitString(high & other.high, low & other.low);
    }

    BitString Or(const BitString& other) const {
        return BitString(high | other.high, low | other.low);
    }
};


int main() {
    
    setlocale(LC_CTYPE, "ukr");
    BitString a, b, c;

    cout << "Введiть перший бiтовий рядок:" << endl;
    a.Read();

    cout << "Введiть другий бiтовий рядок:" << endl;
    b.Read();

    cout << "Перший рядок: ";
    a.Display();

    cout << "Другий рядок: ";
    b.Display();

    c = a.Not();
    cout << "Операцiя NOT: ";
    c.Display();

    c = a.And(b);
    cout << "Операцiя AND: ";
    c.Display();

    c = a.Or(b);
    cout << "Операцiя OR: ";
    c.Display();

    return 0;
}
