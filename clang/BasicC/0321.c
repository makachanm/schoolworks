#include <stdio.h>

int main(void) {
    int x;
    printf("size of var x: %d\n", sizeof(x));

    printf("size of char: %d\n", sizeof(char));
    printf("size of int: %d\n", sizeof(int));
    printf("size of long: %d\n", sizeof(long));
    printf("size of short: %d\n", sizeof(short));
    printf("size of float: %d\n", sizeof(float));
    printf("size of double: %d\n", sizeof(double));

    /*
    result:

    size of var x: 4
    size of char: 1
    size of int: 4
    size of long: 8
    size of short: 2
    size of float: 4
    size of double: 8
    */
    return 0;
}