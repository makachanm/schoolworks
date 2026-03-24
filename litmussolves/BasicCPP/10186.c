#include <stdio.h>
#include <stdlib.h>

int main() {
   int n, i, j, *q, r;

   scanf("%d", &n);
   q = (int *)malloc(sizeof(int) * n);

   for(int k = 0; k < n; k++)
      scanf("%d", &q[k]);

   scanf("%d %d", &i, &j);

   r = 0;
   for(int k = i; k <= j; k++)
      r += q[k];

   printf("%d\n", r);
   free(q);

   return 0;
}