#include <stdio.h>

int main() {
   int n, m;
   scanf("%d %d", &n, &m);

   if(m == 0) {
      m = 100;
   }

   for(int i = 1; i < 11; i++) {
      if((n * i) >= m) break;
      else printf("%d ", (n * i));
   }

   printf("\n");

   return 0;
}