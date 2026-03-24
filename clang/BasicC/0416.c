#include <stdio.h>

int main(void) {
    //Chapter 6 51-52p
    int number;
    int x;

    printf("input: ");
    scanf("%d", &number);

    switch (number)
    {
    case 0:
        printf("없음\n");
        break;
    
    case 1:
        printf("하나\n");
        break;

    case 2:
        printf("둘\n");
        break;

    default:
        printf("많음\n");
        break;
    }

    if(number == 0)
        printf("없음\n");
    else if (number == 1)
        printf("하나\n");
    else if(number == 2)
        printf("둘\n");
    else 
        printf("많음\n");

    /*
    switch (number)
    {
    case x:
        printf("x와 일치\n");
        break;
    
    case (x+2):
        printf("수식과 일치\n");
        break;

    case 0.001:
        printf("실수\n");
        break;

    case 'a':
        printf("문자\n");
        break;

    default:
        printf("많음\n");
        break;
    }
    */

    //Chapter 7 11p
    int i = 0;

    while(i < 5){
        printf("HELLO WORLD!\n");
        i++;
    }

    /*
    HELLO WORLD!
    HELLO WORLD!
    HELLO WORLD!
    HELLO WORLD!
    HELLO WORLD!
    */

    //Chapter 7 14p
    int step;
    int mul = 1;

    printf("출력하고 싶은 단: ");
    scanf("%d", &step);

    while(mul < 10) {
        printf("%d * %d = %d\n", step, mul, step*mul);
        mul++;
    }
    
    /*
    출력하고 싶은 단: 5
    5 * 1 = 5
    5 * 2 = 10
    5 * 3 = 15
    5 * 4 = 20
    5 * 5 = 25
    5 * 6 = 30
    5 * 7 = 35
    5 * 8 = 40
    5 * 9 = 45
    */

   int powt = 1;
   printf("    n    n의 제곱\n");
   printf("=================\n");

   while(powt <= 10){
      printf("%5d    %5d\n", powt, powt*powt);
      powt++;
   }

   /*
       n    n의 제곱
    =================
        1        1
        2        4
        3        9
        4       16
        5       25
        6       36
        7       49
        8       64
        9       81
        10      100
   */

    //Chapter 7 16p
    int sum = 0;
    int n = 1;
    int target;

    printf("합할 정수를 입력: ");
    scanf("%d", &target);

    while(n <= target) {
        sum = sum + n;
        n++;
    }

    printf("1부터 %d까지의 합은 %d입니다.\n", target, sum);

    //Chapter 7 21p
    int l, sumr;

    l = 0;
    sumr = 0;
    while(l < 5){
        int r;
        printf("input value: ");
        scanf("%d", &r);

        sumr = sumr + r;
        l++;
    }

    printf("합계는 %d입니다.\n", sumr);

    /*
    input value: 1
    input value: 1
    input value: 1
    input value: 1
    input value: 1 
    합계는 5입니다.
    */


    return 0; 
}