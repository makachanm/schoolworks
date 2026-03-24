#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);
int get_slope_incp(int x1, int y1, int x2, int y2, float *slope, float *yinscept);

int main(void) {
    //12p
    int zi = 10;
    double zf = 12.3f;

    int *zp = NULL;
    double *zpf = NULL;
    zp = &zi;
    zpf = &zf;

    printf("%p %p\n", &zi, zp);
    printf("%p %p\n", &zf, zpf);
    printf("\n");
    printf("%d %d\n", zi, *zp);
    printf("%lf %lf\n", zf, *zpf);


    printf("\nzi = %d\n", zi);
    *zp = 20;
    printf("zi = %d\n", zi);


    /*
    22p 중간-점검

    1. 바이트
    2. char  : 1byte
       short : 2byte
       int   : 4byte
       long  : 4byte
       float : 4byte
       double: 8byte
    3. 주소를 담는 변수이기 때문에 맞다.
    4. &
    5. p = &x;
    6. *p = 25;
    */

    /*
    *p++ - p가 가르키는 주소의 값을 불러오고 p 포인터 증가
    (*p)++ - p가 가르키는 주소의 값을 증가
    */

    /*
    37p 중간-점검
    1. 증가, 감소, 덧셈, 뺄셈
    2. 84번지
    3. 전자는 p가 가르키는 값을 불러온 뒤 주소를 증가시키지만 후자는 p가 가르키는 값이 증가한다.

    int i = 5;
    int  *p = &i; (0x100 가정)

    3-1. v = *p++에서
         v는 5의 값을 가지고 p는 0x104의 값을 가진다.

    3.2 v = (*p)++에서
         v는 6의 값을 가지고 p는 0x100의 값을 가진다.

    4. p가 가진 타입만큼 3 뒤에 있는 주소의 값을 가져온다.
    */

    int a = 250, b = 100;
    printf("Before Swap:\n");
    printf("a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("After Swap:\n");
    printf("a = %d, b = %d\n", a, b);

    //46p
    printf("\n");


    float slope, incp;
    if(get_slope_incp(2, 4, 3, 5, &slope, &incp) == 0)
        printf("ERR!\n");
    else
        printf("기울기: %f, Y절편: %f\n", slope, incp);


    /*
    48p 중간-점검
    1. call-by-value
    2. call-by-reference
    3. 매개 변수로 주소 값을 받아 포인터를 통해 접근한다.
    */

    /*
    60p 중간-점검
    1. call-by-value
    2. call-by-reference
    3. 복사되지 않고 주소값이 전해진다.
    */

    return 0;
}   

void swap(int *x, int *y) {
    int tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

int get_slope_incp(int x1, int y1, int x2, int y2, float *slope, float *yinscept) {
    if ((x1 == x2) || (y1 == y2))
        return 0;

    float sp = (float)(y2 - y1) / (float)(x2 - x1);
    *slope = sp;
    *yinscept = y1 - (sp * x1) ;
    return 1;
}