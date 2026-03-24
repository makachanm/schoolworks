#include <iostream>

class Exchange {
private:
   float yen;
   float dollar;
   float wian;

public:
   Exchange(float y, float d, float w) : 
      yen(y), dollar(d), wian(w)
   { }

   float wontodollar(int won) {
      return won / this->dollar;
   }

   float wontowian(int won) {
      return won / this->wian;
   }

   float wontoyen(int won) {
      return won / (this->yen / 100);
   }

   float dollartowon(int dollar) {
      return dollar * this->dollar;
   }

   float wiantowon(int wian) {
      return wian * this->wian;
   }

   float yentowon(int yen) {
      return yen * (this->yen / 100);
   }
};

int main() {
   std::cout.setf(std::ios::fixed, std::ios::floatfield);
   std::cout.precision(2);

   float d, y, w;
   std::cin >> d >> w >> y;

   Exchange e(y, d, w);

   int menu;
   int x;
   bool running = true;

   while(running) {
      std::cin >> menu;
      if(menu == 0) {
         break;
      }

      std::cin >> x;

      switch (menu)
      {
      case 1:
         std::cout << e.wontodollar(x) << std::endl;
         break;
      
      case 2:
         std::cout << e.wontowian(x) << std::endl;
         break;

      case 3:
         std::cout << e.wontoyen(x) << std::endl;
         break;

      case 4:
         std::cout << e.dollartowon(x) << std::endl;
         break;

      case 5:
         std::cout << e.wiantowon(x) << std::endl;
         break;

      case 6:
         std::cout << e.yentowon(x) << std::endl;
         break;
      
      default:
         break;
      }
   }
}