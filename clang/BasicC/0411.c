#include <stdio.h>

int main(void) {
    //Chapter 6 34p
    int grade;
    printf("성적을 입력하시오: ");
    scanf("%d", &grade);

    if(grade >= 90)
        printf("A\n");
    else if(grade >= 80)
        printf("B\n");
    else if(grade >= 70)
        printf("C\n");
    else if(grade >= 60)
        printf("D\n");
    else
        printf("F: Fail\n");
    

    //Chapter 6 36p
    char inc;
    printf("문자를 입력하시오: ");

    inc = getchar();

    if(inc >= 'A' && inc <= 'Z'){
        printf("%c는 대문자입니다.\n", inc);
    } else if(inc >= 'a' && inc <= 'z'){
        printf("%c는 소문자입니다.\n", inc);
    } else if(inc >= '0' && inc <= '9'){
        printf("%c는 숫자입니다.\n", inc);
    } else {
        printf("%c는 기타입니다.\n", inc);
    }

    //Chapter 6 37p 중간점검
    /* 
    1번

    n = -1일때
      C
    n = 0일때
      A
    n = 5일때
      B
    */

    /*2번*/
    int cupsize;
    printf("input cup size(ml): ");
    scanf("%d", &cupsize);
 
    if (cupsize >= 200){
      printf("large\n");
    } else if (cupsize >= 100 && cupsize < 200){
      printf("medium\n");
    } else if (cupsize > 100){
      printf("small\n");
    }

    //Chapter 6 43p
    int x, y, result;
    char op;

    printf("식 입력 (2 + 5): ");
    scanf("%d %c %d", &x, &op, &y);

    if (op == '+'){
        result = x + y;
    } else if (op == '-'){
        result = x - y;
    } else if (op == '*'){
        result = x * y;
    } else if (op == '/'){
        result = x / y;
    } else if (op == '%'){
        result = x % y;
    } else {
        printf("unsupported operator; error.\n");
        result = 0;
    }

    printf("%d %c %d = %d\n", x, op, y, result);
    printf("result = %d\n", result);


    return 0;
}