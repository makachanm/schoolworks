#include <stdio.h>
#include <stdlib.h>

int main() {
   int n;
   scanf("%d", &n);

   int* gr = (int *)malloc(sizeof(int) * n * 3);
   
   for(int i = 0; i < (n * 3); i += 3) {
      for(int j = 0; j < 3; j++) {
         scanf("%d", &gr[i + j]);
      }
   }

   for(int i = 0; i < (n * 3); i += 3) {
      for(int k = 0; k < 3; k++)
         printf("%d ", gr[i + k]);

      int total = 0;
      for(int k = 0; k < 3; k++)
         total += gr[i + k];

      int avg = total / 3;

      printf("%d %d\n", total, avg);
   }

   printf("\n");
   free(gr);

   return 0;
}