#include <iostream>

void swap(char &a, char &b, char &c);

int main() {
   char c1, c2, c3;

   std::cin >> c1 >> c2 >> c3;

   swap(c1, c2, c3);
   std::cout << c1 << " " << c2 << " " << c3 << std::endl;

   swap(c1, c2, c3);
   std::cout << c1 << " " << c2 << " " << c3 << std::endl;

   swap(c1, c2, c3);
   std::cout << c1 << " " << c2 << " " << c3 << std::endl;
   

   return 0;
}

void swap(char &a, char &b, char &c) {
   char keepb = b;
   char keepc = c;

   b = a;
   c = keepb;
   a = keepc;
}