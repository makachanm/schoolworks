#include <stdio.h>

#define SIZE 5
//28p Lab: Impl Bank Account

int x = 50; // Global x

int main(void) {
    //37p
    int x = 100; // Local x
    {
        extern int x; // Global x
        printf("x = %d\n", x);
    }
    printf("x = %d\n", x); // Local x



    //C10 13p
    int i;
    int score[5];

    score[0] = 10;
    score[1] = 20;
    score[2] = 30;
    score[3] = 40;
    score[4] = 50;

    for(i = 0; i < 5; i++)
        printf("score[%d] = %d\n", i, score[i]);

    //fixed
    int scorex[SIZE];
    for(i = 0; i < SIZE; i++)
        scorex[i] = ((i + 1) * 10);

    for(i = 0; i < SIZE; i++)
        printf("scorex[%d] = %d\n", i, scorex[i]);

    return 0;
}