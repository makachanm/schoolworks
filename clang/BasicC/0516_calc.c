#include <stdio.h>
#include <math.h>

const double pi = 3.141592f;

int menu() {
    printf("== CALCULATOR ==\n");
    printf("1. fac(n)\n");
    printf("2. sin(n: degree)\n");
    printf("3. log10(n)\n");
    printf("4. sqrt(x)\n");
    printf("5. permutaion(nPr)\n");
    printf("6. combination(nCr)\n");
    printf("9. quit\n");

    int input;
    printf("> ");
    scanf(" %d", &input);
    return input;
}

double inputnnum() {
    double input;
    printf("input n: ");
    scanf(" %lf", &input);

    return input;
}

double rad(double degree) {
    return pi * degree / 180.0f;
}

int fac(int n) {
    int p = 1;
    for(int x = n; x >= 1; x--)
        p = p * x;

    return p;
}

double sinx(double n) {
    double degree = rad(n);
    return sin(n);
}

double log10x(double n) {
    if (n <= 0.0f){
        printf("ERROR: cannot be 0 or smaller.\n");
        return 0.0f;
    }
    return log10(n);
}

double sqrtx(double n) {
    if (n < 0.0f) {
        printf("ERRORL cannot be smaller than 0.\n");
        return 0.0f;
    }
    return sqrt(n);
}

int permutation(int n, int r) {
    return fac(n) / (fac(n - r));
}

int combination(int n, int c) {
    return permutation(n, c) / fac(c);
}

int main(void) {
    while(1) {
        int select = menu();
        double result;
        double input;

        switch(select) {
            case 1:
                input = inputnnum();
                result = (double)fac((int)input);
                break;

            case 2:
                input = inputnnum();
                result = sinx(input);
                break;

            case 3:
                input = inputnnum();
                result = log10x(input);
                break;
            
            case 4:
                input = inputnnum();
                result = sqrtx(input);
                break;

            case 5:
                int n, r;
                printf("input n: ");
                scanf(" %d", &n);
                printf("input p: ");
                scanf(" %d", &r);

                result = permutation(n, r);
                break;

            case 6:
                int n2, c;
                printf("input n: ");
                scanf(" %d", &n2);
                printf("input c: ");
                scanf(" %d", &c);

                result = permutation(n2, c);
                break;

            case 9:
                printf("exiting...\n");
                return 0;
        }

        printf("result: %lf\n", result);
    }
}