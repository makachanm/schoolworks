#include <iostream>
using namespace std;

class Time {
private:
   int hour, minute, second;

public:
   Time(int h, int m, int s) :
      hour(h), minute(m), second(s)
   { }

   void Show() {
      cout << hour << "H " << minute << "M " << second << "S" << endl;
   }

   Time operator++() {
      if(this->second + 1 > 59) {
         this->second = 0;
         if(this->minute + 1 > 59) {
            this->hour++;
            this->minute = 0;
         } else {
            this->minute++;
         }
      } else {
         this->second++;
      }
   }
};

int main()
{
    int x,y,z;
    cin >> x >> y>>z;

    Time time1(x, y, z);

    time1.Show();
    ++time1;
    time1.Show();

    return 0;
}