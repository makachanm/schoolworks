#include <iostream>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point(double x, double y) :
        x(x), y(y)
    { }

    void ShowPosition() {
        cout << "[" << this->x << ", " << this->y << "]" << endl;
    }

    Point operator-() {
        x = (this->x * -1) != -0 ? -(this->x) : 0;
        y = (this->y * -1) != -0 ? -(this->y) : 0;

        return *this;
    }
};

int main()
{
    int x,y;
    cin>>x>>y;

    Point pos1(x,y);
    pos1.ShowPosition();

    Point pos2 = -pos1;

    pos2.ShowPosition();

    return 0;
}