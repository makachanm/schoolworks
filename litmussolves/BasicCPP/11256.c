#include <stdio.h>
#include <stdlib.h>

int main() {
   int n;
   scanf("%d", &n);

   int* t = (int *)malloc(sizeof(int) * n * 3);

   for(int i = 0; i < (n * 3); i+=3) {
      for(int  j = 0; j < 3; j++){
         scanf("%d", &t[i+j]);
      }
   }

   int avgs[3];
   int high[3];
   int low[3];

   for(int i = 0; i < 3; i++) {
      int total = 0;
      int tmax;
      int tmin;
      
      for(int j = i; j < (n * 3); j += 3) {
         total += t[j];

         if(j == i) {
            tmax = t[j];
            tmin = t[j];
            continue;
         }

         if(t[j] > tmax)
            tmax = t[j];
         if(t[j] < tmin)
            tmin = t[j];
      }

      avgs[i] = (total / n);
      high[i] = tmax;
      low[i] = tmin;
   }

   for(int i = 0; i < (n * 3); i+=3) {
      for(int j = 0; j < 3; j++){
         printf("%d ", t[i+j]);
      }
      printf("\n");
   }

   for(int i = 0; i < 3; i++)
      printf("%d ", low[i]);
   printf("\n");

   for(int i = 0; i < 3; i++)
      printf("%d ", high[i]);
   printf("\n");

   for(int i = 0; i < 3; i++)
      printf("%d ", avgs[i]);
   printf("\n");

   free(t);
   return 0;
}