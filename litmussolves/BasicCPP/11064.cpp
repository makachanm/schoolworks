#include <iostream>
using namespace std;

class Point {
private:
   int x, y;

public:
   friend ostream& operator<<(ostream& out, const Point& u);
   friend istream& operator>>(istream& in, Point& u);
};

ostream& operator<<(ostream& out, const Point& u) {
   out << "[" << u.x << ", " << u.y << "]" << endl;
   return out; 
}

istream& operator>>(istream& in, Point& u) {
   in >> u.x >> u.y;
   return in;
}

int main()
{
    Point pos1;
    Point pos2;

    cin>>pos1;
    cin>>pos2;

    cout<<pos1;
    cout<<pos2;

    return 0;
}