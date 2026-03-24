#include <stdio.h>

int main() {
    printf("Result = %d\n", 2 + 3);
    printf("Result = %d\n", 2 - 3);
    printf("Result = %d\n", 2 * 3);
    printf("Result = %d\n", 2 / 3);

    for(unsigned int i = 1; i <= __UINT16_MAX__; i++){
        printf("9 X %d = %d\n", i, 9 * i);
    }
    return 0;
}