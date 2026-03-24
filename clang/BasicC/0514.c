#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

/*
Program written in linux/arm64 - libc
Windows MSVC/MinGW와 라이브러리 및 작동이 다를 수 있음.
*/

const int MAX = 45;

double ctof(double temp);
int coin();
int carprint(int, int);
int carrand();

int main(void) {
    //46p
    /*
    /home/maka/workspace/school-clang/0514.c:4:48: warning: implicit declaration of function ‘ctof’ [-Wimplicit-function-declaration]
    4 |     printf("섭씨 %lf는 화씨 %lf이다.\n", 36.0, ctof(36.0));
      |       
    /home/maka/workspace/school-clang/0514.c:8:8: error: conflicting types for ‘ctof’; have ‘double(double)’
    8 | double ctof(double temp) {
      |        ^~~~
  
    오류의 이유: 함수 원형 선언 없이 뒤에 선언된 함수를 호출하려 했기 때문이다. 
    */

    printf("섭씨 %lf는 화씨 %lf이다.\n", 36.0, ctof(36.0));

    //52p 중간점검
    /*
    1. 함수의 이름, 반환형, 매개변수 이름, 매개변수 타입, 함수의 정의 
    2. 한 개
    3. void
    4. 함수 원형은 함수를 정의하기 전에 함수의 형태를 미리 지정해놓는 것을 뜻한다.
    5. 타입이 같거나 순서를 헷갈릴 위험이 있기 때문에 이름을 붙인다.
    6. 함수는 double 실수를 반환하며 double형 매개변수를 두개 받는다.
    */


   //58p
   for(int i = 0; i < 6; i++)
        printf("%d ", rand());
    printf("\n");

    for(int i = 0; i < 6; i++)
        printf("%d ", 1+(rand()%45));
    printf("\n");

    /*
    1804289383 846930886 1681692777 1714636915 1957747793 424238335 
    2 13 25 2 33 23 

    1804289383 846930886 1681692777 1714636915 1957747793 424238335 
    2 13 25 2 33 23 

    1804289383 846930886 1681692777 1714636915 1957747793 424238335 
    2 13 25 2 33 23 
    */

    srand((unsigned)time(NULL));
    for(int i = 0; i < 6; i++)
        printf("%d ", 1+(rand()%MAX));
    printf("\n");
    /*
    42 12 35 38 44 26 
    7 21 20 38 25 6 
    21 39 42 25 29 45 
    */

    //61,62p

    int front = 0;
    int back = 0;

    srand((unsigned)time(NULL));
    const int toss = 100;

    for(int t = 0; t < toss; t++){
        if(coin() == 1){
            front++;
        } else {
            back++;
        }
    }

    printf("front: %d\nback: %d\n", front, back);
    /*
    front: 44
    back: 56
    
    front: 54
    back: 46

    front: 63
    back: 37
    */

    //63p
    /*
    1. 난수 시드 초기화
    2. 6번 반복:
        2-1: 난수를 발생해 자동차 1의 주행거리 누적
        2-2: 난수를 발생해 자동차 2의 주행거리 누적
        2-3: 자동차의 주행 거리 표기    
    */

    /*
    자동차 출력 함수 알고리즘:
    1. 자동차 번호 출력
    2. 자동차 거리를 10으로 나눈 만큼 * 출력
    */
    int carone = 0;
    int cartwo = 0;
    srand((unsigned)time(NULL));

    for(int i = 0; i < 6; i++){
        carone += carrand();
        cartwo += carrand();

        carprint(1, carone);
        carprint(2, cartwo);
        printf("==========================\n");
        getchar();
    }

    /*
CAR NUMBER 1: **
CAR NUMBER 2: ****
==========================

CAR NUMBER 1: **
CAR NUMBER 2: *******
==========================

CAR NUMBER 1: *****
CAR NUMBER 2: ****************
==========================

CAR NUMBER 1: ******
CAR NUMBER 2: ***********************
==========================

CAR NUMBER 1: ***********
CAR NUMBER 2: *************************
==========================

CAR NUMBER 1: *****************
CAR NUMBER 2: ********************************
==========================
    */
   carone = 0;
   cartwo = 0;
   int carthree = 0;

    for(int i = 0; i < 6; i++){
        system("clear");

        carone += carrand();
        cartwo += carrand();
        carthree += carrand();

        carprint(1, carone);
        carprint(2, cartwo);
        carprint(3, carthree);

        sleep(1);
    }

    /*
    CAR NUMBER 1: *************************
    CAR NUMBER 2: ******************************
    CAR NUMBER 3: *********************************
    */

    return 0;
}

double ctof(double temp) {
    return 9.0/5.0*temp + 32;
}

int coin() {
    return (rand() % 2);
}

int carrand() {
    return (rand() % 100);
}

int carprint(int carnum, int distance) {
    printf("CAR NUMBER %d: ", carnum);
    
    for(int i=0; i < (int)(distance / 10); i++)
        printf("*");
    printf("\n");
}