#include <stdio.h>
#include <stdlib.h>

int main() {
   int n;
   scanf("%d", &n);
   
   int* a = (int *)malloc(sizeof(int) * n);
   for(int i = 0; i < n; i++)
      scanf("%d", &a[i]);

   
   int x = 0;
   for(int j = 0; j < n; j++) {
      if(a[j] % 2 != 0)
         x += a[j];
   }

   printf("%d\n", x);
   free(a);
   
   return 0;
}