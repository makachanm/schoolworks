#include <stdio.h>
#include <limits.h>

#define EXCHANGE_RATE 1200
#define MONTHS 12

int main(void){
    // 4장 18p Source
    short year = 0;
    int sale = 0;
    long total_sale = 0;

    year = 25;
    sale = 200000000;

    total_sale = sale * year;

    printf("total sale => %d\n", total_sale);
    //실행결과
    //total sale => 705032704

    //4장 21p Source
    unsigned int sales = 2800000000;
    printf("u- %u\n", sales);
    printf("d - %d\n", sales);
    /*
    u- 2800000000
    d - -1494967296
    */
    int usalze = 2800000000;
    printf("overflow: %d\n", usalze);
    //overflow: -1494967296

    //4장 22p Source
    short s_money = __SHRT_MAX__;
    unsigned short u_money = USHRT_MAX;

    s_money++;
    u_money++;

    printf("smoney = %d\numoney = %d\n", s_money, u_money);
    /*
    smoney = -32768
    umoney = 0
    */

    //4장 28p Soruce
    int x = 11;
    int y = 014;
    int z = 0x11;

    printf("x = %d\ny = %d\nz = %d\n", x, y, z);

   //4장 33p

    const float TAX_RATE = 0.2;

    int m_selary, total_selary;

    printf("월급 입력: ");
    scanf("%d", &m_selary);

    total_selary = m_selary * MONTHS;
    printf("연봉: %d\n", total_selary);
    printf("세금: %.2f\n", total_selary * TAX_RATE);

    //4장 34p 4번 풀이
    //overflow가 발생하여 다시 범위의 끝 값인 0이나 4294967295같은 잘못된 값이 나온다.
    unsigned int x1 = -1;
    printf("%u\n", x1);
    //4294967295

    //4장 35p 5번 풀이
    //이 또한 overflow가 발생하여 short의 한계를 넘어선 값을 저장할 경우 끝 값인 -32768 등이 나오거나, 잘못된 값이 나올 수 있다.
    short y1 = 32768;
    printf("%d\n", y1);
    //-32768

    return 0;
}