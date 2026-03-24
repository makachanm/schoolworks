#include <stdio.h>

int main(void) {
    char name1 = "";
    char name2 = "";
    char name3 = "";
    char name4 = "";
    char name5 = "";

    int price1 = 0;
    int price2 = 0;
    int price3 = 0;
    int price4 = 0;
    int price5 = 0;

    int total = 0;

    printf("1번째 물건의 이름을 입력하라. ");
    scanf("%c", &name1);
    printf("1번째 물건의 가격을 입력하라. ");
    scanf("%d", &price1);
    getchar();

    printf("2번째 물건의 이름을 입력하라. ");
    scanf("%c", &name2);
    printf("2번째 물건의 가격을 입력하라. ");
    scanf("%d", &price2);
    getchar();

    printf("3번째 물건의 이름을 입력하라. ");
    scanf("%c", &name3);
    printf("3번째 물건의 가격을 입력하라. ");
    scanf("%d", &price3);
    getchar();

    printf("4번째 물건의 이름을 입력하라. ");
    scanf("%c", &name4);
    printf("4번째 물건의 가격을 입력하라. ");
    scanf("%d", &price4);
    getchar();

    printf("5번째 물건의 이름을 입력하라. ");
    scanf("%c", &name5);
    printf("5번째 물건의 가격을 입력하라. ");
    scanf("%d", &price5);
    getchar();

    total = price1 + price2 + price3 + price4 + price5;

    printf("==== TOTAL LIST ==== \n");
    printf("항목 : %c, 가격 : %d원\n", name1, price1);
    printf("항목 : %c, 가격 : %d원\n", name2, price2);
    printf("항목 : %c, 가격 : %d원\n", name3, price3);
    printf("항목 : %c, 가격 : %d원\n", name4, price4);
    printf("항목 : %c, 가격 : %d원\n", name5, price5);
    printf("TOTAL : %d\n", total);

    int money = 0;
    int remain = 0;
    int c10000 = 0;
    int c5000 = 0;
    int c1000 = 0;
    int c500 = 0;
    int c100 = 0;
    int c50 = 0;
    int c10 = 0;

    printf("계산할 금액 입력: ");
    scanf("%d", &money);

    if (money < 10) 
        printf("금액을 확인하세요.\n");
    else {
        c10000 = money / 10000;
        remain = money % 10000;

        c5000 = remain / 5000;
        remain = remain % 5000;

        c1000 = remain / 1000;
        remain = remain % 1000;

        c500 = remain / 500;
        remain = remain % 500;

        c100 = remain / 100;
        remain = remain % 100;

        c50 = remain / 50;
        remain = remain % 50;

        c10 = remain / 10;

        printf("==== 거스름돈 ====\n");
        printf("10000원 %d 장\n", c10000);
        printf("5000원 %d 장\n", c5000);
        printf("1000원 %d 장\n", c1000);
        printf("500원 %d 장\n", c500);
        printf("100원 %d 장\n", c100);
        printf("50원 %d 장\n", c50);
        printf("10원 %d 장\n", c10);
    }
    

    return 0;
}