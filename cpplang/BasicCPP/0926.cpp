/* 이름쓰기이름쓰기이름쓰기이름쓰기이름쓰기이름쓰기이름쓰기 */
#include <iostream>

class Point {
private:
    int x;
    int y;

public:
    /*
    Point(int xv, int yv) : x(xv) , y(yv) {
        if(this->x < 0 && this->x > 100) this->x = 0;
        if(this->y < 0 && this->y > 100) this->y = 0;
    }
    */

    bool Init(int xv, int yv) { 
        return this->set_x(xv) && this->set_y(yv);
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    bool set_x(int xv) {
        if (xv < 0 || xv > 100) return false;
        
        this->x = xv;
        return true;
    }

    bool set_y(int yv) {
        if (yv < 0 || yv > 100) return false;
        
        this->y = yv;
        return true;
    }

    void print() {
        std::cout << "x: " << this->x << " y: " << this->y << std::endl;
    }
};

class Rectangle {
private:
    Point top_left;
    Point bottom_right;

public:
    bool Init(Point& tl, Point& br) {
        if (tl.get_x() > br.get_y() && tl.get_y() > br.get_y()) return false;
        this->top_left = tl;
        this->bottom_right = br;

        return true;
    }

    int Area() {
        return (this->bottom_right.get_x() - this->top_left.get_x()) * (this->bottom_right.get_y() - this->top_left.get_y());
    }

    int Perimeter() {
        return (2 * (this->bottom_right.get_x() - this->top_left.get_x())) + (2 * (this->bottom_right.get_y() - this->top_left.get_y()));
    }

    void Print() {
        std::cout << "Top-Left" << std::endl;
        this->top_left.print();

        std::cout << "Bottom-Right" << std::endl;
        this->bottom_right.print();
    }
};

int main() {
    int x1, x2;

    std::cin >> x1 >> x2;
    Point p1;
    if(!p1.Init(x1, x2))
    std::cout << "error: out-of-range" << std::endl;

    std::cin >> x1 >> x2;
    Point p2;
    if(!p2.Init(x1, x2))
    std::cout << "error: out-of-range" << std::endl;

    Rectangle rec;
    if(!rec.Init(p2, p1))
    std::cout << "error: out-of-rectangle" << std::endl;
    if(!rec.Init(p1, p2))
    std::cout << "error: out-of-rectangle" << std::endl;

    rec.Print();
    std::cout << "Area " << rec.Area() << std::endl;
    std::cout << "Perimeter " << rec.Perimeter() << std::endl;
    return 0;
}