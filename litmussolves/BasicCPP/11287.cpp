#include <iostream>

class Point {
private:
    int* x;
    int* y;

public:
    Point() {
        this->x = new int(0);
        this->y = new int(0);
    }
    Point(int t) { 
        this->x = new int(t);
        this->y = new int(t);
    }
    Point(int xv, int yv) { 
        this->x = new int(xv);
        this->y = new int(yv);
    }
    Point(const Point& p) {
        this->x = new int;
        this->y = new int;

        this->x = p.x;
        this->y = p.y;
    }
    Point(int m, const Point& p) {
        this->x = new int((*p.x) * m);
        this->y = new int((*p.y) * m);
    }

    void print_coords() {
        std::cout << "[" << *this->x << ", " << *this->y << "]" << std::endl;
    }
};

int main()
{
    Point pt1;
    Point pt2(1);
    Point pt3(2, 3);
    Point pt4(pt3); //<--깊은 복사 생성자 구현 필요
    Point pt5(2, pt3);

    pt1.print_coords();
    pt2.print_coords();
    pt3.print_coords();
    pt4.print_coords();
    pt5.print_coords();
}