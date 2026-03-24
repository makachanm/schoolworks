#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

struct student {
    int number;
    char name[10];
    double grade;
};

struct point {
    int x;
    int y;
};


void getSensorData(float *p);
double getPointDistance(struct point p1, struct point p2);

int main(void) {
    float x[3];
    getSensorData(x);

    printf("왼쪽 센서와 장애물과의 거리: %lf \n", x[0]);
    printf("중간 센서와 장애물과의 거리: %lf \n", x[1]);
    printf("오른쪽 센서와 장애물과의 거리: %lf \n", x[2]);

    struct student s;
    
    /*
    strcpy(s.name, "홍길동");
    s.number = 202412000;
    s.grade = 3.65f;
    */

    printf("NAME? ");
    scanf(" %s", s.name);
    printf("NUMBER? ");
    scanf(" %d", &s.number);
    printf("GRADE? ");
    scanf(" %lf", &s.grade);

    printf("\n==============\n");

    printf("학번: %d\n", s.number);
    printf("이름: %s\n", s.name);
    printf("학점: %.2f\n", s.grade);


    struct point q = { 1, 2 };
    struct point p = { .x = 1, .y = 2 };

    printf("p=(%d, %d) \n", p.x, p.y);
    printf("q=(%d, %d) \n", q.x, q.y);

    struct point p1, p2;
    double dist;

    printf("FIRST POINT: (x, y)\n");
    scanf("%d %d", &p1.x, &p1.y);

    printf("SECOND POINT: (x, y)\n");
    scanf("%d %d", &p2.x, &p2.y);

    dist = getPointDistance(p1, p2);
    printf("거리: %lf\n", dist);

    /*
    중간점검
    1. 멤버 변수
    2. struct
    3. 선언한 다른 구조체와 구분하기 위해서이다.
    4. 그렇지 않다.
    5. (구조체_이름).(구조체_멤버)
    */

    return 0;
}

void getSensorData(float *p) {
    srand(time(NULL));
    p[0] = rand() % 100;
    p[1] = rand() % 100;
    p[2] = rand() % 100;

    return;
}

double getPointDistance(struct point p1, struct point p2) {
    double dist;

    double xdif = p1.x - p2.x;
    double ydif = p1.y - p2.y;

    dist = sqrt((double)(xdif * xdif + ydif * ydif));

    return dist;
}