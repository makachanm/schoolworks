#include <stdio.h>

int main(void) {
    // 01. 연봉을 한푼도 쓰지 않고 몇년동안 모아야 10억이 될까?
    int income;
    double year;

    printf("연봉을 입력하시오(단위: 만원): ");
    scanf("%d", &income);

    year = 1000000000 / (income * 10000);

    printf("10억을 모으는데 걸리는 시간(단위: 년): %.2lf\n", year);

    //02. 마일을 미터로 환산하는 프로그램을 만들어보자.
    float mile;
    double meter;

    printf("마일을 입력하시오: ");
    scanf("%f", &mile);

    meter = mile * 1690;
    printf("%f 마일은 %lf 미터입니다.\n", mile, meter);

    //03. 삼각형의 높이와 밑변을 받아서 넓이를 계산하여 출력하는 프로그램을 만들어보자.
    float width, height, area;

    printf("삼각형의 밑변: ");
    scanf("%f", &width);

    printf("삼각형의 높이: ");
    scanf("%f", &height);

    area = width * height * 0.5;

    printf("삼각형의 넓이: %f\n", area);

    //04. 섭씨 온도를 화씨 온도로 바꿔 출력하는 프로그램을 만들어보자.
    float fer;
    float temp;

    printf("화씨값을 입력하시오: ");
    scanf("%f", &fer);

    temp = (5.0 / 9.0) * (fer - 32.0);
    printf("섭씨값은 %f 입니다.\n", temp);

    //05. 다항식 3x^2 + 7x + 11의 값을 프로그램을 작성하여라.
    float x;
    float result;

    printf("실수를 입력하시오: ");
    scanf("%f", &x);

    result = (3 * x * x) + (7 * x) + 11;
    printf("다항식의 값은 %f\n", result);

    //06. 자신의 몸무게를 입력받아 달에서의 몸무게를 계산하는 프로그램을 작성하여라.
    float weight;
    double moon;

    printf("몸무게를 입력하시오(단위: kg): ");
    scanf("%f", &weight);

    moon = weight * 0.17;
    printf("달의서에 몸무게는 %f kg입니다.\n", moon);

    return 0;
}