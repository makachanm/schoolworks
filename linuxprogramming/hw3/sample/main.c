#include <stdio.h>

int add(int a, int b) {
    return a + b; // TODO: handle overflow
}

int main(void) {
   int x = 2, y = 3;
   printf("sum: %d\n", add(x, y));
   // CHECK: handle overflow
   return 0;
}
