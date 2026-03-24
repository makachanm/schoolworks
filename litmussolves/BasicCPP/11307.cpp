#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : 
        x(x), y(y)
    {}

    void ShowPosition() {
        cout << "[" << this->x << ", " << this->y << "]" << endl;
    }

    friend bool operator==(const Point& u1, const Point& u2);
    friend bool operator!=(const Point& u1, const Point& u2);
};

bool operator==(const Point& u1, const Point& u2) {
    return (u1.x == u2.x) && (u1.y == u2.y);
}

bool operator!=(const Point& u1, const Point& u2) {
    return (u1.x != u2.x) || (u1.y != u2.y);
}


int main()
{
    int x1, x2, y1, y2;

    cin >> x1 >> y1;
    cin >> x2 >> y2;

    Point p1(x1, y1);
    Point p2(x2, y2);

    p1.ShowPosition();
    p2.ShowPosition();

   if(p1==p2){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"no"<<endl;
   }
   if(p1!=p2){
        cout<<"yes"<<endl;
    }
    else{
        cout<<"no"<<endl;
   }
     return 0;
}