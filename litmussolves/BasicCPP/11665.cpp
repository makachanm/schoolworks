#include <iostream>
using namespace std;

template <typename T>
class Point {
private:
   T x, y;

public:
   Point(T x1, T y1) :
      x(x1), y(y1)
   { }

   void show() {
      cout << "[" << this->x << ", " << this->y << "]" << endl;
   }

   void swap() {
      T temp = this->y;
      this->y = this->x;
      this->x = temp;
   }

   void move(int n) {
      this->x = (this->x * n);
      this->y = (this->y * n);
   }

   void add(const Point<T>& ref) {
      this->x = (this->x + ref.x);
      this->y = (this->y + ref.y);
   }
};

int main() {
    int x1, y1, x2, y2, n;
    cin>>x1>>y1;

    Point<int> pos1(x1,y1);
    cin>>x2>>y2;

    Point<int> pos2(x2,y2);

    pos1.add(pos2);
    pos1.show();

    cin >> n;

    pos2.move(n);
    pos2.show();

    pos1.swap();
    pos1.show();

    double x3, x4, y3, y4;
    cin>>x3>>y3;

    Point<double> pos3(x3, y3);
    cin>>x4>>y4;

    Point<double> pos4(x4,y4);

    pos3.add(pos4);
    pos3.show();

    cin >> n;

    pos4.move(n);
    pos4.show();

    pos3.swap();
    pos3.show();

return 0;
}