#include <iostream>
#include <string>

template<typename T>
void xswap(T &a1, T &a2) {
   T temp = a1;
   a1 = a2;
   a2 = temp;
}

int main() {
   int x1, x2;
   double y1, y2;
   std::string z1, z2;

   std::cin >> x1 >> x2;
   std::cin >> y1 >> y2;
   std::cin >> z1 >> z2;

   xswap<int>(x1, x2);
   xswap<double>(y1, y2);
   xswap<std::string>(z1, z2);

   std::cout << x1 << " " << x2 << std::endl;
   std::cout << y1 << " " << y2 << std::endl;
   std::cout << z1 << " " << z2 << std::endl;

   return 0;
}
