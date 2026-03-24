#include <stdio.h>

int is_p(int n) {
    for(int x = 2; x < n; x++){
        if(n % x == 0) return 1;
    }

    return 0;
}

int getint() {
    int tg;
    printf("input intger: ");
    scanf("%d", &tg);

    return tg;
}

int main(void) {
    while(1){
        int n = getint();

        if (n < 0) break;

        if(is_p(n) == 0){
            printf("is prime!\n");
        } else {
            printf("is not prime....\n");
        }
        getchar();
    }
    printf("exiting!\n");
    return 0;
}