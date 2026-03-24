#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZEARR 5
#define SIZESTUDENT 5

#define seatsize 10
#define SIZEARRZ 10

int main(void) {
    //16p
    int rndsc[SIZEARR];

    srand((unsigned)time(NULL));
    for(int i = 0; i < SIZEARR; i++)
        rndsc[i] = rand() % 100;

    for(int x = 0; x < SIZEARR; x++)
        printf("rndsc[%d] = %d\n", x, rndsc[x]);

    
    //18p
    int studentvals[SIZESTUDENT];
    for (int i = 0; i < SIZESTUDENT; i++) {
        printf("학생의 점수를 입력하시오: ");
        scanf(" %d", &studentvals[i]);
    }

    int totalsum = 0;
    for(int i = 0; i < SIZESTUDENT; i++)
        totalsum += studentvals[i];

    int avg = totalsum / SIZESTUDENT;
    printf("평균: %d\n", avg);


    //26p
    int scores[SIZEARR] = {31, 63, 62, 87, 14};

    for(int i = 0; i < SIZEARR; i++)
        printf("scores[%d] = %d\n", i, scores[i]);

    int scoresx[SIZEARR] = {31, 63};

    for(int i = 0; i < SIZEARR; i++)
        printf("scoresx[%d] = %d\n", i, scoresx[i]);

    int uscore[SIZEARR];

    for(int i = 0; i < SIZEARR; i++)
        printf("uscore[%d] = %d\n", i, scores[i]);


    //30p
    int lensample[] = { 1, 2, 3, 4, 5, 6 };
    int sizeoflenp = 0;

    sizeoflenp = sizeof(lensample) / sizeof(lensample[0]);
    for(int i = 0; i < sizeoflenp; i++)
        printf("lensample[%d] = %d\n", i, lensample[i]);
    printf("size of lensample = %d\n", sizeoflenp);
    
   
    //벡스터형래더좀살려줘요
    //35p
    int dicefreq[6] = {0};

    srand((unsigned)time(NULL));
    for(int i = 0; i < 10000; i++) 
        ++dicefreq[rand() % 6];

    printf("====================\n숫자     빈도\n====================\n");
    for(int i = 0; i < 6; i++)
        printf("%3d     %3d\n", i, dicefreq[i]);



    //37p
    int seats[seatsize] = {0};
    int select;
    char c;

    while(1){
        printf("좌석을 예약하시겠습니까? (Y/N): ");
        scanf(" %c", &c);

        if(c == 'n'){
            printf("현재 예약 상태:\n");
            printf("========================================\n");
            for(int i = 0; i < seatsize; i++)
                printf("%3d ", i + 1);
            printf("\n");
            printf("========================================\n");
            for(int i = 0; i < seatsize; i++)
                printf("%3d ", seats[i]);
            printf("\n");
            break;

        } else if(c == 'y') {
            printf("========================================\n");
            for(int i = 0; i < seatsize; i++)
                printf("%3d ", i + 1);
            printf("\n");
            printf("========================================\n");
            for(int i = 0; i < seatsize; i++)
                printf("%3d ", seats[i]);
            printf("\n");

            printf("몇번째 좌석을 예약하시겠습니까? : ");
            scanf(" %d", &select);

            if(0 > (select - 1) || (select - 1) > seatsize) {
                printf("올바른 좌석이 아닙니다.\n");
                continue;
            }

            if (seats[select - 1] == 1){
                printf("이미 예약된 좌석입니다.\n");
                continue;
            } else {
                seats[select - 1] = 1;
                printf("좌석이 예약되었습니다.\n");
            }
        } else {
            printf("invalid input.\n");
            continue;
        }
    }
    


    //43p
    int randvalary[SIZEARRZ];
    int min = randvalary[0];
    int max = randvalary[0];

    for(int i = 0; i < (sizeof(randvalary) / sizeof(randvalary[0])); i++){
        if(min > randvalary[i])
            min = randvalary[i];
        if(max < randvalary[i])
            max = randvalary[i];
    }

    printf("ARRAY: \n");
    for(int i = 0; i < (sizeof(randvalary) / sizeof(randvalary[0])); i++)
        printf("%2d ", randvalary[i]);
    printf("\n");

    printf("MIN: %d\nMAX: %d\n", min, max);

    return 0;
}