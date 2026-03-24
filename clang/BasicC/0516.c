#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

const double PI = 3.141592;

int main(void) {
    //70~73p
    double result, val = 1.6f;
    result = floor(val);

    printf("%lf\n", result);

    result = ceil(val);

    printf("%lf\n", result);

    printf("12.0 fabs : %lf\n", fabs(12.0f));
    printf("-12.0 fabs : %lf\n", fabs(-12.0f));

    printf("10^3 : %lf\n", pow(10.0f, 3.0f));
    printf("sqrt 16 : %lf\n", sqrt(16.0f));


    double x, siny, cosy;

    x = PI / 2;
    siny = sin(x);
    cosy = cos(x);

    printf("sin(%f) = %f\n", x, siny);
    printf("cos(%f) = %f\n", x, cosy);

    //76p
    printf("press any key.");
    getchar();

    system("ls -al");
    printf("press any key.");
    getchar();

    system("clear");
    getchar();

    //77p.
    time_t start, end;
    printf("press enter after 10sec.\n");

    start = time(NULL);
    while(1) {
        if(getchar())
            break;
    }
    end = time(NULL);
    printf("breaked.\n");
    printf("elapsed: %ldsec.\n", end - start);


    return 0;
}