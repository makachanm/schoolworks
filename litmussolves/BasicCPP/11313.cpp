#include <iostream>
#include <string>

template<typename T>
T add(T a1, T a2) {
   return a1 + a2;
}

int main() {
   int x1, x2;
   double y1, y2;
   std::string z1, z2;

   std::cin >> x1 >> x2;
   std::cin >> y1 >> y2;
   std::cin >> z1 >> z2;

   std::cout << add<int>(x1, x2) << std::endl;
   std::cout << add<double>(y1, y2) << std::endl;
   std::cout << add<std::string>(z1, z2) << std::endl;

   return 0;
}
