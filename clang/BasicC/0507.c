#include <stdio.h>

void pstar() { //define function
    for(int x = 0; x < 30; x++)
        printf("*");
    printf("\n");
}

int imax(int x, int y) {
    if (x > y) 
        return x;
    else 
        return y;
}

void happybday(){
    printf("생일축하합니다!\n");
    printf("생일축하합니다!\n");
    printf("사랑하는 친구의\n");
    printf("생일축하합니다!\n");
}

int getint() {
    int val;
    printf("input intger: ");
    scanf("%d", &val);
    return val;
}

int add(int x, int y) { 
    return x + y;
}

int fac(int turn) {
    int m = 1;
    for(int a = turn; a >= 1; a--){
        m = m * a;
    }
    return m;
}
 
int main(void) {
    pstar(); //15p
    printf("HELLOWORLD!\n");
    pstar();
    //43 ->  3 -> 4 -> 5 -> 6 -> 9 -> 43 -> 44 -> 45 -> 3 -> 4 -> 5 -> 6 -> 9 -> 45 -> ...

    //p23
    int p, q;
    printf("input two intger: ");
    scanf("%d %d", &p, &q);

    int bigger = imax(p, q);
    printf("%d is bigger.\n", bigger);
    //when 30, 20
    //49 -> 50 -> 51 -> 53 -> 9 -> 10 -> 11 -> 53 -> 54 -> ...
    //when 20, 30
    //49 -> 24 -> 25 -> 27 -> 9 -> 10 -> 12 -> 13 -> 27 -> 28 -> ...

    //25p
    happybday();
    //61 -> 16 -> 17 -> 18 -> 19 -> 20 -> 21 -> 61 -> ...

    //31p
    int k = getint();
    int l = getint();
    int xsum = add(k, l);
    printf("두 수의 합은 %d이다.\n", xsum);
    //65 -> 23 -> 24 -> 25 -> 26 -> 27 -> 65 -> 58 -> 66 -> 24 -> 25 -> 26 -> 27 -> 66 -> 67 -> 30 -> 31 -> 32 -> 67 -> 68 -> ...

    //32p
    printf("알고싶은 팩토리얼 값은?\n");
    int ft = getint();

    int result = fac(ft);
    printf("%d의 fac은 %d입니다.\n", ft, result);
    //72 -> 73 -> 23 -> 24 -> 25 -> 26 -> 27 -> 73 -> 75 -> 34 -> 35 -> 36 -> 37 -> 38 -> 39 -> 75 -> 76 -> ...

    return 0;
}



/*
C Program Memory Structure

//////// STACK
x, y, bigger (main()) - function's memory area.
x, y         (imax()) - function's memory area.

/////// HEAP 
--------------
--------------
-------------- 
(user allocable)

/////// DATA
a, b, ..... strings....
*/