#include <stdio.h>

int main(void) {
    //이제는 고양이가 락도 하네
    int a = (~42) + 0x01;
    int b = (~a) + 0x01;
    printf("a = %d, b = %d\n", a, b);

    //Chapter 5 90, 91p
    int i;
    double f;

    f = 5 / 4;
    printf("%f\n", f);

    f = (double)5 / 4;
    printf("%f\n", f);

    f = (double)5 / (double)4;
    printf("%f\n", f);

    i = 1.3 + 1.8;
    printf("%d\n", i);

    i = (int)3.2 + (int) 2.8;
    printf("%d\n", i);
    /*
    1.000000
    1.250000
    1.250000
    3
    5
    */

    //Chapter 5 101p
    int x = 0, y = 0;
    int result;

    result = 2 > 3 || 6 > 7;
    printf("%d\n", result);

    result = 2 || 3 && 3 > 32;
    printf("%d\n", result);

    result = x = y = 1;
    printf("%d\n", result);

    result = ++x + y--;
    printf("%d\n", result);

    result = - ++x + y--;
    printf("%d\n", result);
    /*
    0
    1
    1
    3
    -3
    */

    //Chapter 6 9p
    int input;
    printf("input intger: ");
    scanf("%d", &input);

    if(input > 0)
        printf("양수입니다.\n");

    printf("input: %d\n", input);
    /*
    input intger: 25
    양수입니다.
    input: 25

    input intger: -9
    input: -9
    */

    //Chapter 6 18p
    int score;
    printf("score?: ");
    scanf("%d", &score);

    if (score >= 60) {
        printf("합격입니다.\n");
        printf("장학금도 받습니다. \n");
        //좋겠다 나는 못받ㄱ았는데
    } else {
        printf("불합격입니다.\n");
    }
    /*
    score?: 62
    합격입니다.
    장학금도 받습니다. 

    score?: 37
    불합격입니다.
    */

    //Chapter 6 25p
    int v, q, xresult;
    printf("두 정수를 입력하시오: ");
    scanf("%d %d", &v, &q);

    if(q == 0){
        printf("error: division by 0\n");
    } else {
        xresult = v / q;
        printf("result: %d\n", xresult);
    }

    /*
    두 정수를 입력하시오: 5 4
    result: 1

    두 정수를 입력하시오: 5 0
    error: division by 0
    */

    //Chapter 6 28p
    int n;
    printf("input intger(n): ");
    scanf("%d", &n);

    if (n > 100) {
        printf("large\n");
    } else {
        printf("small\n");
    }
    /*
    input intger(n): 102
    large

    input intger(n): 42
    small
    */
    

    return 0;
}
