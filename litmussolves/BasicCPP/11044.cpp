#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int a, int b): x(a), y(b) { }
    Point(const Point& p): x(p.x), y(p.y) { }

    void print() {
        cout << "(" << this->x << ", " << this->y << ")" << endl; 
    }

    void move(int x, int y) {
        this->x += x;
        this->y += y;
    }
};

int main() {
    int x, y, a, b;
    cin >> x >> y;

    Point p1(x, y);
    Point p2 = p1;

    p2.print();

    cin >> a >> b;
    p2.move(a, b);     // 점 위치 이동 후 출력 

    p2.print();

    return 0;
}