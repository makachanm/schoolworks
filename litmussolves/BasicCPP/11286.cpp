#include <iostream>

class Point {
private:
    int x;
    int y;

public:
    Point() {
        this->x = 0;
        this->y = 0;
    }
    Point(int t) : x(t), y(t) { }
    Point(int xv, int yv) : x(xv), y(yv) { }
    Point(const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }
    Point(int m, const Point& p) {
        this->x = (p.x) * m;
        this->y = (p.y) * m;
    }

    void print_coords() {
        std::cout << "[" << this->x << ", " << this->y << "]" << std::endl;
    }
};

int main()
{
    Point pt1;
    Point pt2(1);
    Point pt3(2, 3);
    Point pt4(pt3); //<--복사 생성자를 통해 구현 해 보는 것을 추천
    Point pt5(2, pt3); //p3의 좌표값 곱하기 2

    pt1.print_coords();
    pt2.print_coords();
    pt3.print_coords();
    pt4.print_coords();
    pt5.print_coords();
}
