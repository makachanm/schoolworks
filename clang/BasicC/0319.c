#include <stdio.h>
#define PI 3.141592

int main(void) {
    //44p
    int x, y;
    printf("첫번째 숫자를 입력하시오: ");
    scanf("%d", &x);
    printf("두번째 숫자를 입력하시오: ");
    scanf("%d", &y);

    int sum = x + y;

    printf("두 수의 합: %d\n", sum);

    float radius;
    printf("반지름을 입력하시오: ");
    scanf("%f", &radius);

    float area;
    float lengths;

    area = PI * radius * radius;
    lengths = PI * 2 * radius;

    printf("넓이: %f\n", area);
    printf("길이: %f\n", lengths);

    double usd, rate, krw;

    printf("환율을 입력하시오: ");
    scanf("%lf", &rate);

    printf("원화 금액을 입력하시오: ");
    scanf("%lf", &krw);

    usd = krw / rate;

    printf("%lf원은 %lf 달러입니다.\n", krw, usd);

    double first, second, third;
    printf("실수 3개를 입력해 주십시오. \n");
    scanf("%lf %lf %lf", &first, &second, &third);

    double totalsum = (first + second + third);
    double avgresult = totalsum / 3;

    printf("총합: %lf\n", totalsum);
    printf("평균값: %lf\n", avgresult);

    return 0;
}