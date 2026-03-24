#include <stdio.h>

int add_odd(int arr[100], int n) {
   int result = 0;

   for(int i = 0; i < n; i++) {
      if(arr[i] % 2 != 0) {
         result += arr[i];
      }
   }

   return result;
}

int main()
{
int n, i;
int arr[100];
scanf("%d", &n);
for(i = 0; i < n; i++) scanf("%d", &arr[i]);
printf("%d", add_odd(arr, n));
return 0;
}