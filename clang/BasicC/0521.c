#include <stdio.h>

int inc(int counter);
int A, B;
int MYGLOBAL;

int qx;
int ksum = 42;

void sub() {
    for (qx = 0; qx < 10; qx++)
        printf("*");
}

int globaladd() {
    return A + B;
}

void account() {
    static int scount = 0;
    int acct = 0;

    printf("scount = %d\nacct = %d\n", scount, acct);

    scount++;
    acct++;
}

int main(void) { 
    //10p
    int i;
    int tempx = 3;

    for(i = 0; i < 5; i++) {
        int temp = 3;
        printf("temp = %d\n", temp);
        temp++;
    }

    for(i = 0; i < 5; i++) {
        printf("tempx = %d\n", tempx);
        tempx++;
    }

    int tempq;
    printf("tempq = %d\n");
    // tempq = 2132999000
    // 쓰레기 값이 나올 확률이 존재함.
    tempq = 5;
    printf("tempq = %d\n", tempq);


    //13p
    //before fix
    i = 10;
    printf("before call i = %d\n", i);
    inc(i); //Call-By Value
    printf("after call i = %d\n", i);

    //after fix
    i = 10;
    printf("before call i = %d\n", i);
    i = inc(i); //Call-By Value
    printf("after call i = %d\n", i);
    

    //15p
    // A , B, MYGLOBAL는 전역변수.
    A = 5;
    B = 7;
    int answer = globaladd();
    printf("A + B = %d\n", answer);
    printf("MYGLOBAL = %d\n", MYGLOBAL);

    //17p (시험문제 예정)
    //qx는 전역변수.
    for(qx = 0; qx < 10; qx++)
        sub();
    printf("\n\n");
    //fixed
    for(int qnx = 0; qnx < 10; qnx++) {
        sub();
        printf("\n");
    }


    //19p
    //ksum은 전역변수
    int ksum = 0;
    printf("ksum = %d\n", ksum);



    //20p 중간점검
    /*
    1. 함수의 안에 있는가, 밖에 있는가.
    2. 지역 변수, 전역 변수.
    3. 전역 변수.
    4. 지역 변수.
    5. 정의할수 있다.
    6. 똑같은 이름의 지역변수는 정의될 수 없다.
    7. 지역 변수는 블록이 종료되면 사라진다.
    8. 쓰레기 값이 들어간다.
    9. 함수의 매개 변수도 그 함수의 지역 변수이다.
    10. 전역 변수는 함수 바깥 소스 내에 정의된다.
    11. 전역 변수는 프로그램이 종료될 때 까지 생존하며 초기값은 int 기준 0이다.
    12. 지역 변수가 우선적으로 취급되어 내부에서는 지역변수의 값을 가진다. 
    */


    //24p
    for(int i = 0; i < 3; i++)
        account();

    return 0;
}

int inc(int counter) {
    counter++;
    return counter;
}
