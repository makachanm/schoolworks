#include <iostream>
using namespace std;

class Point {
private:
    double x, y;

public:     
    Point(double x, double y):
        x(x), y(y)
    { }

    void show() {
        std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
    }

    Point operator+=(const Point& u) {
        this->x+= u.x; this->y += u.y;
        return *this;
    }

    Point operator-=(const Point& u) {
        this->x -= u.x; this->y -= u.y;
        return *this;
    }

    void ShowPosition() {
        cout << "[" << this->x << ", " << this->y << "]" << endl;
    }

    friend Point operator*(const Point& u1, const Point& u2);
    friend Point operator*(const Point& u1, double x);
    friend Point operator*(double x, const Point& u1);
};

Point operator*(const Point& u1, const Point& u2) {
    Point p(u1.x * u2.x, u1.y * u2.y);
    return p;
}

Point operator*(const Point& u1, double x) {
    Point p(u1.x * x, u1.y * x);
    return p;
}

Point operator*(double x, const Point& u1) {
    Point p(u1.x * x, u1.y * x);
    return p;
}

int main()
{
    int x1, x2, y1, y2;
    int a, b;

    cin >> x1 >> y1;
    cin >> x2 >> y2;
     cin >> a >> b;

    Point p1(x1, y1);
    Point p2(x2, y2);

    p1.ShowPosition();
     p2.ShowPosition();

     p1+=p2;

     p1.ShowPosition();

     p1-=p2;
     p1-=p2;

     p1.ShowPosition();

     Point p3 = p2*a;
     Point p4 = a*p2*b;

     p3.ShowPosition();
     p4.ShowPosition();

     return 0;
}