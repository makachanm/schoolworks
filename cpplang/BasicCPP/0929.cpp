#include <iostream>

class Time {
private:
   int hour;
   int minute;
   int second;

public:
   Time(int h = 0, int m = 0, int s = 0) :
      hour(h), minute(m), second(s) { }

   void print() {
      std::cout << this->hour << "h " << this->minute << "m " << this->second << "s" << std::endl;
      std::cout << ((this->hour * 60 * 60) + (this->minute * 60) + this->second) << "s" << std::endl;
   }   
};

int main() {
  int hour, min, sec;
        std::cin >> hour >> min >> sec;
        Time t1;
        Time t2(hour);
        Time t3(hour, min);
        Time t4(hour, min, sec);
        t1.print();
        t2.print();
        t3.print();
        t4.print();
   return 0;
}