#include <iostream>

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

    Point operator+(const Point& u) {
        Point p(this->x + u.x, this->y + u.y);
        return p;
    }

    Point operator-(const Point& u) {
        Point p(this->x - u.x, this->y - u.y);
        return p;
    }

    Point& operator++() {
        this->x+=1; 
        this->y+=1;

        return *this;
    }

    Point& operator--() {
        this->x-=1; 
        this->y-=1;

        return *this;
    }

    friend Point operator*(const Point& u1, const Point& u2);
    friend const Point operator++(Point& u, int);
    friend const Point operator--(Point& u, int);
};

Point operator*(const Point& u1, const Point& u2) {
    Point p(u1.x * u2.x, u1.y * u2.y);
    return p;
}

const Point operator++(Point& u, int) {
    const Point r(u.x, u.y);
    u.x++;
    u.y++;

    return r;
}

const Point operator--(Point& u, int) {
    const Point r(u.x, u.y);
    u.x--;
    u.y--;

    return r;
}

int main() {
    std::cout << "p1" << std::endl;
    Point p1(1, 2);
    Point p2(3, 4);

    Point p3 = p1 + p2;
    Point p4 = p2 - p1;
    Point p5 = p1 * p2;

    Point p6 = p1 + p2 + p1 + p2;

    p3.show();
    p4.show();
    p5.show();
    p6.show();

    std::cout << "x1" << std::endl;
    Point x1(3, 4);
    Point x2(5, 6);

    Point x3 = --(--(--x1));
    Point x4 = ++(++x2);

    x1.show();
    x2.show();
    x3.show();
    x4.show();

    std::cout << "t1" << std::endl;
    Point t1(3, 4);
    Point t2(5, 6);

    Point t3 = t1--;
    Point t4 = t2++;

    std::cout << "before" << std::endl;
    t3.show();
    t4.show();
    std::cout << "after" << std::endl;
    t1.show();
    t2.show();

    return 0;
}