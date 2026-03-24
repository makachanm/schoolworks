#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 3
#define COLS 5

//arugment로 전달되는 array는 data가 복사되지 않고 address가 전해진다.
//array 자체의 변수는 array의 data가 적재된 memory의 address를 쥐고 있는 포인터.
int get_avg(int students[], int length);

void modarray(int a[], int size);
void printarray(int a[], int size);

int main(void) {
    int students[5] = {1, 2, 3, 4, 5};
    int avg = get_avg(students, 5);
    printf("평균은 %d입니다.\n", avg);

    int listq[] = {1, 2, 3, 4, 5, 6, 7};
    printarray(listq, (int)(sizeof(listq) / sizeof(listq[0])));
    printf("\n");
    modarray(listq, (int)(sizeof(listq) / sizeof(listq[0])));
    printarray(listq, (int)(sizeof(listq) / sizeof(listq[0])));
    printf("\n");


    //중간점검
    /*
    1. 원본이 전달된다.
    2. 함수 인자 타입 앞에 const를 붙인다.
    */

    int z[ROWS][COLS]; 
    srand((unsigned)time(NULL));

    
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            z[i][j] = rand() % 100;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++)
            printf("%3d", z[i][j]);
        printf("\n");
    }

    return 0;
}

int get_avg(int students[], int length) {
    int sumofval = 0;

    for(int i = 0; i < length; i++)
        sumofval += students[i];

    return sumofval / length;
}

void modarray(int a[], int size) {
    for(int i = 0; i < size; i++)
        a[i] = a[i]++;
}

void printarray(int a[], int size) {
    for(int i = 0; i < size; i++)
        printf("%3d", a[i]);
}