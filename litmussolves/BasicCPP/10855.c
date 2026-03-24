#include <stdio.h>
#include <stdlib.h>

int main() {
   int n;
   scanf("%d", &n);

   int* x = (int *)malloc(sizeof(int) * n);
   for(int i = 0; i < n; i++)
      scanf("%d", &x[i]);

   int v;
   scanf("%d", &v);

   printf("%d\n", x[v]);
   
   free(x);
   return 0;
}