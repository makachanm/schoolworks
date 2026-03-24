#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const double PI = 3.141592f;

int even(int n);
int absolute(int n);
int sign(int n);

int is_multiple(int n, int m);

double get_bigger(double x, double y);

int check_alpha(char c);

double cal_area(double radius);

int is_leap(int year);

int pround(double f);

int get_tax(int income);

double sin_degree(double degree);

int randint();

int main(void) {
   // 01번.
   int n1in;
   printf("정수를 입력하시오: ");
   scanf(" %d", &n1in);
   printf("even()의 결과: %d\n", even(n1in));
   printf("absolute()의 결과: %d\n", absolute(n1in));
   printf("sign()의 결과: %d\n", sign(n1in));

   // 02번.
   int firstint, secondint;
   printf("첫번째 정수를 입력하시오: ");
   scanf(" %d", &firstint);
   printf("두번째 정수를 입력하시오: ");
   scanf(" %d", &secondint);
   if (is_multiple(firstint, secondint) == 0) {
      printf("%d는 %d의 배수가 아닙니다.\n", firstint, secondint);
   } else {
      printf("%d는 %d의 배수입니다.\n", firstint, secondint);
   }

   // 03번.
   double xf, yf;
   printf("실수를 입력하시오: ");
   scanf(" %lf %lf", &xf, &yf);
   printf("큰 수는 %lf입니다.\n", get_bigger(xf, yf));

   // 04번.
   char ch;
   printf("문자를 입력하시오: ");
   scanf( " %c", &ch);
   if(check_alpha(ch)) {
      printf("%c는 알파벳 문자입니다.\n", ch);
   } else {
      printf("%c는 알파벳 문자가 아닙니다.\n", ch);
   }

   // 05번.
   double radius;
   printf("원의 반지름을 입력하시오: ");
   scanf(" %lf", &radius);
   printf("원의 면적은 %lf입니다.\n", cal_area(radius));

   // 06번.
   int year;
   printf("연도를 입력하시오: ");
   scanf(" %d", &year);
   if(is_leap(year)) {
      printf("%d년은 윤년입니다.\n", year);
   } else {
      printf("%d년은 윤년이 아닙니다.\n", year);
   }

   // 07번.
   // round();는 math.h의 round();와 겹침.
   double k;
   printf("실수를 입력하시오: ");
   scanf(" %lf", &k);
   printf("반올림한 값은 %d입니다.\n", pround(k));

   // 08번.
   int income;
   printf("소득을 입력하시오(만원): ");
   scanf(" %d", &income);
   printf("소득세는 %d만원입니다.\n", get_tax(income));
   

   // 09번.
   for(double i = 0; i < 190.0f; i += 10.0f)
      printf("sin(%lf)의 값은 %lf\n", i, sin_degree(i));

   // 10번.
   for(int i = 0; i < 10; i++)
      printf("%d ", randint());
   printf("\n");

   return 0;
}

// 01번.
int even(int n) {
   if (n % 2 == 0)
      return 1;
   else
      return 0;
}

int absolute(int n) {
   if (n == 0)
      return n;
   else if (n > 0)
      return n;
   else if (n < 0)
      return -(n);
}

int sign(int n) {
   if (n < 0)
      return -1;
   else if (n > 0)
      return 1;
   else if (n == 0)
      return 0;
}

// 02번.
int is_multiple(int n, int m) {
   if (n % m == 0) {
      return 1;
   } else {
      return 0;
   }
}

// 03번.
double get_bigger(double x, double y) {
   return (x > y) ? x : y;
}

// 04번.
int check_alpha(char c) {
   return (96 < c && c < 123) ? 1 : 0;
}

// 05번.
double cal_area(double radius) {
   return (PI * pow(radius, 2.0f));
}

// 06번.
int is_leap(int year) {
   return (year % 100 != 0 && (year % 4 == 0 || year % 400 == 0)) ? 1 : 0;
}

// 07번.
int pround(double f) {
   return (int)(f + 0.5f);
}

// 08번.
int get_tax(int income) {
   double eightper = 0;
   double tenper = 0;

   if (income - 1000 > 0) {
      tenper = (income - 1000) * (0.1);
      eightper = (income - (income - 1000)) * (0.08);
   } else {
      eightper = (income) * (0.08);
   }

   return (int)floor(eightper + tenper);
}

// 09번.
double sin_degree(double degree) {
   double rad = (PI * degree) / 180.0f;
   return sin(rad);
}

// 10번.
int randint() {
   return (10) + (rand() % (90 - 11));
}