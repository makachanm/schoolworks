#include <iostream>
using namespace std;

class Rectangle {
    friend class Shape;
private:
    int width;
    int height;

   // Shape s;

public:
    Rectangle(int w, int h):
        width(w), height(h)
    { }
};

class Circle {
    friend class Shape;
private:
    int radius;

    //Shape s;

public:
    Circle(int r): 
        radius(r)
    { }

};

class Shape {
public:
    Shape() { }

    void Circumference(const Rectangle& r) {
        cout << 2 * (r.width + r.height) << " "; 
    }

    void Circumference(const Circle& r) {
        cout << 2 * 3.14 * (r.radius) << " "; 
    }

    void Area(const Rectangle& r) {
        cout << r.width * r.height << endl;
    }

    void Area(const Circle& r) {
        cout << 3.14 * r.radius * r.radius << endl;
    }
};

int main() {
    int x, y, r;
   cin>>x>>y>>r;

    Rectangle Rec(x, y);
    Circle Cir(r);
    Shape S;

    S.Circumference(Rec);
    S.Area(Rec);

    S.Circumference(Cir);
    S.Area(Cir);

    return 0;
}