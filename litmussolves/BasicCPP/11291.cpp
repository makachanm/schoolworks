#include <iostream>
using namespace std;

class Circle {
private:
    int radius;

public:
    Circle(int r): radius(r) { }

    void SetRadius(int r) {
        this->radius = r;
    }

    void printInfo() const {
        float round = 2 * 3.14 * this->radius;
        float area = 3.14 * (this->radius * this->radius);

        cout << round << " " << area << endl; 
    }
};

int main() {
    int r1, r2;
    cin>>r1;

    Circle Cir1(r1);
    const Circle Cir2(r1);

    cin >> r2;

    Cir1.SetRadius(r2);

    Cir1.printInfo();
    Cir2.printInfo();

    return 0;
}