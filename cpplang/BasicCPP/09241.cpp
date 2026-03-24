#include <iostream>

class Time {
private:
   int hour;
   int minute;
   int second;

public:
   Time() {
      hour = 0;
      minute = 0;
      second = 0;
   }

   void Set(int hr) {
      hour = hr;
   }

   void Set(int hr, int min) {
      hour = hr;
      minute = min;
   }

   void Set(int hr, int min, int sec) {
      second = sec;
      minute = min;
      hour = hr;
   }

   void GetFulltime() {
      std::cout << hour << "h " << minute << "m " << second << "s" << std::endl;
   }

   void GetSecond() {
      int r = ((hour * 60 * 60) + (minute * 60) + second);
      std::cout << r << "s" << std::endl;
   }
};

int main() {
    Time* t = new Time();

    int menu;
    int h, m, s;
   
   std::cin >> menu;
   switch (menu)
   {
      case 1:
         std::cin >> h;
         t->Set(h);
         break;

      case 2:
         std::cin >> h >> m;
         t->Set(h, m);
         break;

      case 3:
         std::cin >> h >> m >> s;
         t->Set(h, m, s);
         break;
   }

   t->GetFulltime();
   t->GetSecond();
    

   return 0;
}