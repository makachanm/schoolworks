#include <stdio.h>

int main()
{
    int a, m2, m3;
    printf("정수 입력\r\n");
    scanf("%d", &a);

    m2 = !(a%2);
    m3 = !(a%3) ? 0 : 2;

    int k2, k3;
    k2 = !(a%2);
    k3 = !(a%3);


    switch (m2 + m3)
    {
    case 3:
        printf("2와 3의 공배수");
        break;

    case 2:
        printf("3의 공배수");
        break;

    case 1: 
        printf("2의 공배수");
        break;
    
    default:
        printf("배수 관계가 없음");
        break;
    }
    
    switch((k2 << 1) | k3)
    {
    case 0x3:
        printf("2와 3의 공배수");
        break;

    case 0x2:
        printf("3의 공배수");
        break;

    case 0x1: 
        printf("2의 공배수");
        break;
    
    default:
        printf("배수 관계가 없음");
        break;

    }
}