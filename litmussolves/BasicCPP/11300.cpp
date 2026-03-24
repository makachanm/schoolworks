#include <iostream>

class Shape {
public:
    virtual void leng() {}
    virtual void area() {}
};

class Rectangle : public Shape {
private:
    int w, h;

public:
    Rectangle(int x, int y) :
        w(x), h(y)
    { }

    void leng() {
        std::cout << (w * 2) + (h * 2) << " ";
    }

    void area() {
        std::cout << (w * h) << std::endl;
    }
};

class Circle : public Shape {
private:
    int rad;

public:
    Circle(int r) :
        rad(r)
    { }

    virtual void leng() {
        std::cout << (2 * rad * 3.14) << " ";
    }

    virtual void area() {
        std::cout << (rad * rad * 3.14) << std::endl;
    }
};

int main() {
    int a, b, r;
    std::cin >> a >> b >> r;
    Shape* rect = new Rectangle{ a, b };
    Shape* circ = new Circle{ r };

    rect->leng();
    rect->area();
    circ->leng();
    circ->area();

delete rect;
delete circ;

    return 0;
}