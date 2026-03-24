#include <iostream>
#include <string>
#include <exception>

int stoi(std::string& s) {
   int ref = 0;
   if(s[0] == '0' && s.length() > 1)
      throw std::runtime_error("Error: first number is 0");

   for(int i = 0; i < s.length(); i++) {
      if(s[i] < '0' || s[i] > '9') {
         std::string err("Error: input character ");
         err += s[i];

         throw std::runtime_error(err);
      }

      ref = ref * 10 + (s[i] - '0');
   }

   return ref;
}

int main() {
   std::string x, y;
   std::cin >> x >> y;

   int x1, y1;
   try {
      x1 = stoi(x);
      y1 = stoi(y);
   } catch(std::exception& e) {
      std::cout << e.what() << std::endl;
      return 0;
   }

   std::cout << "+: " << x1 + y1 << std::endl;
   std::cout << "-: " << x1 - y1 << std::endl;
   std::cout << "*: " << x1 * y1 << std::endl;

   try {
      if(y1 == 0)
         throw -1;
         std::cout << "/: " << x1 / y1 << std::endl;
   } catch(int e) { 
      std::cout << "Error: y is 0" << std::endl;
   }

   return 0;
}