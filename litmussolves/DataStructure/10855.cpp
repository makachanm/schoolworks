#include <iostream>

int main() {
   int size;
   std::cin >> size;

   int* numbers = new int[size];
   
   for(int i = 0; i < size; i++)
      std::cin >> numbers[i];

   int idx;
   std::cin >> idx;
   std::cout << numbers[idx] << std::endl;

   delete numbers;

   return 0;
}