#include <iostream>
using namespace std;

class Adder {
private:
    static int x;

public:
    Adder() { }

    void add(int x) {
        this->x += x;
    }

    static int printSum() {
        //cout << x << endl;
        return x;
    }
};

int Adder::x = 0;

int main() {
    int count, n;
    Adder A[100];
    cin >> count;

    for(int i = 0; i < count; i++) {
        cin >> n;
        A[i].add(n);
    }
    cout << Adder::printSum() << endl;

    return 0;
}