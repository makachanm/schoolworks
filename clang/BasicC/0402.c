#include <stdio.h>

int main(void) {
    const int SEC_PER_MIN = 60;
    //Chapter 4 55p.
    double xr = (1.0e20 + 5.0) - 1.0e20;
    printf("%f\n", xr);
    /*
    0.000000
    */

    //Chapter 4 61p.
    char code1 = "D";
    char code2 = 65;

    printf("code1 = %c\ncode2 = %c\n", code1, code2);
    /*(
    code1 = D
    code2 = A
    )*/

    //Chapter 4 65p.
    char beep1 = 7;
    char beep2 = "\a";

    printf("%c", beep1);
    printf("%c", beep2);

    //Chapter 4 69p.
    int id, passwd;

    printf("ID와 PASSWORD를 4개의 숫자로 입력하시오.\n");
    printf("ID: \b\b\b\b");
    scanf("%d", &id);
    printf("PASSWORD: \b\b\b\b");
    scanf("%d", &passwd);

    printf("\a입력된 ID는 \"%d\" 이고 PASSWORD는 \"%d\"이다.\n", id, passwd);
    /*
    ID와 PASSWORD를 4개의 숫자로 입력하시오.
    1234
    PASSWO5678
    입력된 ID는 "1234" 이고 PASSWORD는 "5678"이다.
    */

    //Chapter 4 70p.
    char ch1 = 'A';
    printf("%d %d %d \n", ch1, ch1 + 1, ch1 + 2);
    printf("%c %c %c \n", ch1, ch1 + 1, ch1 + 2);
    /*
    65 66 67 
    A B C 
    */

    //Chapter 5 11p.
    int x, y, result;

    printf("두개의 정수 입력 > ");
    scanf("%d %d", &x, &y);

    result = x + y;
    printf("%d + %d = %d\n", x, y, result);
    result = x - y;
    printf("%d - %d = %d\n", x, y, result);
    result = x * y;
    printf("%d * %d = %d\n", x, y, result);
    result = x / y;
    printf("%d / %d = %d\n", x, y, result);
    /*
    두개의 정수 입력 > 5 2
    5 + 2 = 7
    5 - 2 = 3
    5 * 2 = 10
    5 / 2 = 2
    */

    //Chapter 5 12p.
    double px, py, presult;

    printf("두개의 실수 입력 > ");
    scanf("%lf %lf", &px, &py);

    presult = px + py;
    printf("%lf + %lf = %lf\n", px, py, presult);
    presult = px - py;
    printf("%lf - %lf = %lf\n", px, py, presult);
    presult = px * py;
    printf("%lf * %lf = %lf\n", px, py, presult);
    result = px / py;
    printf("%lf / %lf = %lf\n", px, py, presult);
    /*
    두개의 실수 입력 > 7 4
    7.000000 + 4.000000 = 11.000000
    7.000000 - 4.000000 = 3.000000
    7.000000 * 4.000000 = 28.000000
    7.000000 / 4.000000 = 28.000000
    */

    //Chapter 5 23p.

    int money, inputs, remain;
    printf("물건 값을 입력하시오: ");
    scanf("%d", &money);

    printf("투입할 값을 입력하시오: ");
    scanf("%d", &inputs);

    remain = inputs - money;

    int thousand, fivehund, hund;
    thousand = remain / 1000;
    remain = remain % 1000;

    fivehund = remain / 500;
    remain = remain % 500;

    hund = remain / 100;
    remain = remain % 100;

    int fifteen, ten;
    fifteen = remain / 50;
    remain = remain % 50;

    ten = remain / 10;
    
    printf("천원권 %d장\n 500원권 %d개\n 100원권 %d개\n가 거슬러진다.\n", thousand, fivehund, hund);
    printf("혹시 몰라: 50원 %d개, 10원 %d개. \n", fifteen, ten);
    /*
    물건 값을 입력하시오: 9870
    투입할 값을 입력하시오: 25000
    천원권 15장
    500원권 0개
    100원권 1개
    가 거슬러진다.
    혹시 몰라: 50원 0개, 10원 3개. 
    */

    //Chapter 5 35p.
    int vx = 10, vy = 10, vz = 33;

    vx += 1;
    vy *= 2;
    vz %= 10 +20;

    printf("x = %d, y = %d, z = %d\n", vx, vy, vz);
    /*(
    x = 11, y = 20, z = 3
    )*/
    // 37페이지 하기

    return 0;
}