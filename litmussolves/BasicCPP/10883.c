#include <stdio.h>

int main() {
   int n;
   scanf("%d", &n);

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

   int temp;
   for(int k = q; k > 0; k--) {
      for(int j = 0; j < k; j++) {
         if(x[j] > x[j + 1]) {
            temp = x[j];
            x[j] = x[j + 1];
            x[j] = temp;
         }
      }
   }

   for(int i = 0; i < q + 1; i++) {
      if((x[i] % 2 != 0) && (x[i] <= n)) {
         printf("%d ", x[i]);
      }
   }
   
   return 0;
}