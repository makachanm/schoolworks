#include <stdio.h>

int main() {
   int grade;
   scanf("%d", &grade);

   if (grade > 60)
      printf("Pass");
   else
      printf("Fail");

   return 0;
}