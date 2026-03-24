#include <stdio.h>
#include <stdlib.h>

int main(void) {
    //22, 4
    int x;
    int y;

    printf("gcd(x, y): ");
    scanf("%d %d", &x, &y);
    
    int r;

    while(y != 0){
        r = x % y;
        x = y;
        y = r;
    }

    printf("%d\n", x);

    //Chapter 7 49p
    int select = 0;
    do
    {
        printf("1. Create New\n");
        printf("2. Open File\n");
        printf("3. Close File\n");
        printf("> ");
        scanf("%d", &select);
    } while (select > 3 || select < 1);
    /*
    1. Create New
    2. Open File
    3. Close File
    > 1
    선택: 1
    */
    
    printf("선택: %d\n", select);

    //Chapter 7 50p
    int n = 0;
    do {
        printf("%d\n", n);
        n = n + 1;
    } while(n < 3);

    /*
    0
    1
    2
    */

   //Chapter 7 51p
   /*
   int answer = rand() % 100;
   int try = 0;
   int guess;

   do
   {
      printf("Guess?: ");
      scanf("%d", &guess);
      try++;

      if(guess < answer) {
        printf("LOW\n");
      } else if (guess > answer){
        printf("HIGH\n");
      }
   } while (answer == guess);

   printf("맞추었습니다: 시도횟수 %d\n", try);
   */

    //Chapter 7 59p
    for(int i = 0; i < 5; i++){
        printf("%d = HELLO WORLD!\n", i);
    }   
    /*
    0 = HELLO WORLD!
    1 = HELLO WORLD!
    2 = HELLO WORLD!
    3 = HELLO WORLD!
    4 = HELLO WORLD!
    */

    //Chapter 7 62p
    int sum = 0;
    for(int i = 1; i < 11; i++){
        sum += i;
    }
    
    printf("1부터 10까지의 정수의 합: %d\n", sum);

    int whilesum = 0;
    int d = 1;

    while(d <= 10){
        whilesum += d;
        d++;
    }

    printf("1부터 10까지의 정수의 합: %d\n", whilesum);

    //Chapter 7 66p
    printf("*********\n");
    for(int i = 0; i < 5; i++){
        printf("*        *\n");
    }
    printf("*********\n");
    /*
    *********
    *        *
    *        *
    *        *
    *        *
    *        *
    *********
    */
    

    return 0;
}