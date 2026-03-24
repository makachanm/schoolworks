#include <iostream>
#include <vector>
#include <string>

int main() {
   std::string input;
   std::getline(std::cin, input);

   char r_target, r_item;
   std::cin >> r_target;
   std::cin >> r_item;

   std::vector<char> chars;
   for(auto i = input.begin(); i != input.end(); i++) {
      chars.push_back(*i);
   }

   for(auto j = chars.begin(); j != chars.end(); j++) {
      if((*j) == r_target) {
         *j = r_item;
      } else {
         continue;
      }
   }

   std::string result(chars.begin(), chars.end());
   std::cout << result << std::endl;

   return 0;
}