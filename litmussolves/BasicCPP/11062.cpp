#include <iostream>
using namespace std;

class Point {
private:
   int x, y;

public:
   Point(int x, int y) :
      x(x), y(y)
   { }

   Point operator+(const Point& u) {
      Point p((this->x + u.x), (this->y + u.y));
      return p;
   }

   Point operator-(const Point& u) {
      Point p((this->x - u.x), (this->y - u.y));
      return p;
   }

   friend ostream& operator<<(ostream& out, const Point& u);
   friend istream& operator>>(istream& in, Point& u);
};

ostream& operator<<(ostream& out, const Point& u) {
   out << "[" << u.x << ", " << u.y << "]";
   return out; 
}

istream& operator>>(istream& in, Point& u) {
   in >> u.x >> u.y;
   return in;
}

int main()
{
    int x1, x2, y1, y2;
    cin >> x1 >> y1;
    cin >> x2 >> y2;

    Point p1(x1, y1);
    Point p2(x2, y2);
    Point p3 = p1+p2;
    Point p4 = p1-p2;

    cout << p1 <<  endl << p2 << endl << p3 << endl << p4 << endl;

    return 0;
}