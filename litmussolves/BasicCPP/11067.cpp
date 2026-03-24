#include <iostream>
using namespace std;

class Time {
private:
   int second, minute, hour;

public:
   Time(int h = 0, int m = 0, int s = 0) :
      hour(h), minute(m), second(s)
   { }

   void Show() {
      cout << this->hour << " H " << this->minute << " M " << this->second << " S" << endl;
   }
   
   int operator[](int idx) {
      switch (idx)
      {
      case 1:
         return this->hour;
         break;

      case 2:
         return this->minute;
         break;

      case 3:
         return this->second;
         break;
      
      default:
         return 0;
         break;
      }
   }
};

int main()
{
    int x,y,z;

    cin >> x >> y>>z;
    Time time1(x, y, z);

    cin>>x>>y;
    Time time2(x, y );

    time1.Show();
     time2.Show();

    cout<<time1[1]<<endl;
    cout<<time1[2]<<endl; 
    cout<<time1[3]<<endl;
    cout<<time2[3]<<endl;
 return 0;
}