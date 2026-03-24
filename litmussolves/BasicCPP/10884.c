#include <stdio.h>

int main() {
   int n1, n2;
   scanf("%d %d", &n1, &n2);

   int x[100];

   int q = 0;
   for(;;) {
      int m;
      scanf("%d", &m);

      if(m == 0) break;
      else { 
         x[q] = m;
         q++;
      }
   }

   for(int i = 0; i < q; i++) {
      if((x[i] >= n1) && (x[i] <= n2)) {
         printf("%d ", x[i]);
      }
   }

   printf("\n");

   return 0;
}