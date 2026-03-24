#include <iostream>
using namespace std;

class Rectangle {
private:
    int width;
    int height;

public:
    Rectangle(int w, int h):
        width(w), height(h)
    { }

    void SetLength(int w, int h) {
        this->width = w;
        this->height = h;
    }

    void printInfo() const {
        cout << 2 * (width + height) << " " << width * height << endl;
    }
};

int main() {
    int x1, y1, x2, y2;
    cin>>x1 >> y1;

    Rectangle R1(x1, y1);
    const Rectangle R2(x1, y1);

    cin >> x2 >> y2;

    R1.SetLength(x2, y2);
    R1.printInfo();
    R2.printInfo();
    return 0;
}