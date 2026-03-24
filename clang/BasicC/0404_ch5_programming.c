#include <stdio.h>

#define METER_PER_PYNG 3.3058

int main(void) {
   // 01.
   float userinput;
   printf("실수를 입력하시오: ");
   scanf("%f", &userinput);

   printf("실수형식으로는 %f입니다.\n", userinput);
   printf("지수형식으로는 %e입니다.\n", userinput);

   // 02.
   int p;
   printf("16진수 정수를 입력하시오: ");
   scanf("%x", &p);

   printf("8진수로는 %o입니다.\n", p);
   printf("10진수로는 %d입니다.\n", p);
   printf("16진수로는 %#x입니다.\n", p);

   // 03.
   int x = 10, y = 20;
   printf("x=%d y=%d\n", x, y);

   int tmp;
   tmp = x;
   x = y;
   y = tmp; 

   printf("x=%d y=%d\n", x, y);

   // 04.
   double w, h, d, vol;
   printf("상자의 가로 세로 높이를 한번에 입력: ");
   scanf("%lf %lf %lf", &w, &h, &d);

   vol = w * d * h;
   printf("상자의 부피는 %lf입니다.\n", vol);

   // 05.
   double pyng, pyngm;
   printf("평을 입력하세요: ");
   scanf("%lf", &pyng);

   pyngm = pyng * METER_PER_PYNG;

   printf("%lf 평방미터입니다.\n", pyngm);

   // 06.
   double result = (3.32e-3) + (9.76e-8);
   printf("%lf\n", result);

   // 07.
   double mass, spped, energy;
   printf("질량(kg): ");
   scanf("%lf", &mass);

   printf("속도(m/s): ");
   scanf("%lf", &spped);

   energy = (mass * (spped * spped)) / 2.0;
   printf("운동에너지(J): %lf\n");

   // 08.
   int ascii;
   printf("아스키 코드값을 입력하시오: ");
   scanf("%d", &ascii);

   printf("문자:%c입니다.\n", ascii);   

   return 0;
}