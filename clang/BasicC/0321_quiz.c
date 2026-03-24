#include <stdio.h>
#include <math.h>

int main() {
    float weight, height;
    float meterheight;
    double bmi;

    printf("몸무게(단위 kg) 입력: ");
    scanf("%f", &weight);

    printf("키(단위 cm) 입력: ");
    scanf("%f", &height);

    meterheight = height / 100;

    bmi = weight / (meterheight * meterheight);

    printf("\n몸무게: %.2fkg\n 키: %.2fcm\nBMI: %.2f\n", weight, height, bmi);
}