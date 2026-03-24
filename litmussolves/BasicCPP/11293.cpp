#include <iostream>
using namespace std;

class Rectangle {
protected:
    int width; 
    int height;

public: 
    Rectangle(int w, int h) : width(w), height(h) { }

    void ShowCircumference() {
        cout << (this->width + this->height) * 2 << " ";
    }

    void ShowArea() {
        cout << (this->width * this->height) << endl;
    }
};

class Hexahedron : public Rectangle {
private:
    int hheight;

public:
    Hexahedron(int x, int y, int z):
        Rectangle(x, y), hheight(z)
    { }

    void ShowCircumference() {
        cout << (this->width + this->height + this->hheight) * 4 << " ";
    }

    void ShowArea() {
        cout << (this->width * this->height * this->hheight) << endl;       
    }
};

int main()
{
    int width, height, depth;
    cin>> width >> height >> depth;

    Rectangle rec(width,height);

    rec.ShowCircumference();                       // 직사각형의 둘레 출력
    rec.ShowArea();                                       // 직사각형의 넓이 출력

    Hexahedron hex(width,height, depth);
    hex.ShowCircumference();                      // 육면체의 둘레 출력
    hex.ShowArea();                                      // 육면체의 넓이 출력

    return 0;
}