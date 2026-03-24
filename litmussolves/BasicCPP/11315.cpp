#include <iostream>
#include <cstring>
#include <string>

template <typename T>
T mmax(T a1, T a2) {
   return (a1 > a2) ? a1 : a2;
}

template<>
const char* mmax<const char*>(const char* a1, const char* a2) {
   return (strcmp(a1, a2) > 0) ? a1 : a2;
} 

int main() {
   int x1, x2;
   double y1, y2;
   std::string z1, z2;

   std::cin >> x1 >> x2;
   std::cin >> y1 >> y2;
   std::cin >> z1 >> z2;

   std::cout << mmax<int>(x1, x2) << std::endl;
   std::cout << mmax<double>(y1, y2) << std::endl;
   std::cout << mmax<const char*>(z1.c_str(), z2.c_str()) << std::endl;

   return 0;
}