#include <stdio.h>

int main(void) {
    //Chapter 5 56p.

    // Q1.
    // int nohome, ownerage, familynumber;
    // (nohome >= 3) && (ownerage >= 40) && (familynumber >= 3)

    // Q2.
    // 거짓

    // Q3.
    // !3 == 0

    // Q4.
    // (4 > 5) && (i++ > 7)

    //Chapter 5 59p.
    int year;
    int result;
    printf("연도를 입력하시오: ");
    scanf("%d", &year);

    result = (year % 4 == 0) && !(year % 100 == 0) || (year % 400 == 0);
    if(result) {
        printf("윤년입니다.\n");
    }
    printf("result=%d\n", result);
    /*
    연도를 입력하시오: 2024
    윤년입니다.
    result=1
    */

    //Chapter 5 61p.
    int p, q, age;
    printf("정수 2개 입력: ");
    scanf("%d %d", &p, &q);

    printf("bigger: %d\n", (p > q)? p : q);
    printf("smaller: %d\n", (p < q)? p : q);
    /*
    정수 2개 입력: 5 2
    bigger: 5
    smaller: 2
    */

    printf("나이 입력: ");
    scanf("%d", &age);

    (age > 20)? printf("성인입니다.\n") : printf("청소년입니다.\n");
    /*
    나이 입력: 25
    성인입니다.
    */

    //Chapter 5 63p.
    int x, y, z;

    x = 2 + 3, 5 - 3;
    printf("x = %d\n", x);
    printf("Thank "), printf("You!\n");
    x = 2, y = 3, z = 4;
    printf("x = %d, y = %d, z = %d\n", x, y, z);
    /*
    x = 5
    Thank You!
    x = 2, y = 3, z = 4
    */

    return 0;
}