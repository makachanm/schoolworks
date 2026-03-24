#include <iostream>
using namespace std;

class Point {
private:
   int x, y;

public:
   Point(int x, int y) :
      x(x), y(y)
   { }

   void ShowPos() {
      cout << "[" << this->x << ", " << this->y << "]" << endl;
   }

   Point operator+(const Point& ref) {
      Point p((this->x + ref.x), (this->y + ref.y));
      return p; 
   }
};

template<typename T>
T Add(T t1, T t2) {
   return t1 + t2;
}

template<typename T>
void SwapData(T &t1, T &t2) {
   T temp = t1;
   t1 = t2;
   t2 = temp;
}

int main()

{
    int x1, x2, y1, y2;

    cin>>x1>>y1;
    Point pos1(x1,y1);

    cin>>x2>>y2;
    Point pos2(x2,y2);

    Point pos3 = Add(pos1,pos2);

    SwapData(pos1,pos2);

    pos1.ShowPos();
    pos2.ShowPos();
    pos3.ShowPos();

    int a, b, c;
    cin >> a >> b;

    c = Add(a, b);

    cout << a << ' ' << b << ' ' << c << endl;
    SwapData(a, b);
    cout << a << ' ' << b << ' ' << c << endl;

    return 0;
}