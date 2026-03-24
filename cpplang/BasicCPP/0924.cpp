#include <iostream>

class Rectangle {
private:
    int width;
    int height;

public:
    void Init(int w, int h) {
        width = w;
        height = h;
    }

    void Print() {
        std::cout << width << " " << height << " " << (width * height) << std::endl;
    }
};

class Triangle {
private:
    double width;
    double height;

public:
    void Init(double w, double h) {
        width = w;
        height = h;
    }

    void Print() {
        std::cout << width << " " << height << " " << ((width * height) / 2) << std::endl;
    }
};

class Shape {
private:
    Rectangle* rect;
    Triangle* tri;

public:
    Shape() {
        rect = new Rectangle();
        tri = new Triangle();
    }

    void InputRect(int x, int y) {
        rect->Init(x, y);
    }

    void InputTri(int x, int y) {
        tri->Init(x, y);
    }

    void PrintRect() {
        rect->Print();
    }

    void PrintTri() {
        tri->Print();
    }
};

int main() {
    Shape* x = new Shape();

    int menu;
    int w, h;
    bool run = true;

    while(run) {
        std::cin >> menu;
        switch (menu)
        {
        case 0:
            run = false;
            break;

        case 1:
            std::cin >> w >> h;
            x->InputRect(w, h);
            break;

        case 2:
            std::cin >> w >> h;
            x->InputTri(w, h);
            break;

        case 3:
            x->PrintRect();
            break;

        case 4:
            x->PrintTri();
            break;
        }
    }

    return 0;
}