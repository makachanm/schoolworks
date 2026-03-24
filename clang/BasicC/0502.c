#include <stdio.h>
#include <math.h>

int main(void) {
   //91p
    int x;

    while(1) {
        printf("input intger: ");
        scanf("%d", &x);
        if (x < 0)
            break;
        if (x % 3 == 0)
            break;
    }

    //93p
    int base = 1000000;
    int money = base;
    int duration = 0;
    int doubleduration = 0;

    while(1) {
        duration++;
        money += money * 0.3;
        if (money > (base * 10))
            break;
    }

    money = base;

    while(1) {
        doubleduration++;
        money += money * 0.3;
        if (money > (base * 20))
            break;
    }

    printf("until 10x: %d year left.\n", duration);
    printf("until 20x: %d year left.\n", doubleduration);
    /*
    until 10x: 9 year left.
    until 20x: 12 year left.
    */

    //96p
    double sv;
    while(1) {
        printf("input realnum to sqrt: ");
        scanf("%lf", &sv);

        if (sv < 0.00f){
            break;
        }

        printf("sqrt: %f\n", sqrt(x));
    }

    //99p
    for (int i = 0; i < 10; i++){
        if(i % 3 == 0)
            continue;
        printf("%d ", i);
    }

    printf("\n");

    //101p
    char c;

    while(1) {
        printf("input lowercase: ");
        scanf(" %c", &c);

        if (c == 'Q')
            break;
        if (c < 'a' || c > 'z')
            continue;

        c = c - 32;
        printf("uppercase: %c\n", c);
    }

    //103p 중간점검
    /*
    1번.
    continue

    2번.
    break
    */
    
    //3번
    int i;
    for(i = 1; i < 10; i++){
        if(i % 3 == 0) break;
        printf("%d\n", i);
    }
    printf("\n");
    /*
    1
    2
    */

    //4번
    for(i = 1; i < 10; i++){
        if(i % 3 == 0) continue;
        printf("%d\n", i);
    }
    /*
    1
    2
    4
    5
    7
    8
    */

    return 0;
}