#include <stdio.h>

void printmenu(){
    printf("====================\n");
    printf("c : 섭씨 -> 화씨\n");
    printf("f : 화씨 => 섭씨\n");
    printf("q : 종료\n");
    printf("====================\n");
}

double celtofer(double cel) {
    return 9.0 / 5.0 * cel + 32;
}

double fertocel(double fer) {
    return (fer - 32) * 5.0 / 9.0;
}

char inputc() {
    char c;

    printf("메뉴에서 선택하시오: ");
    scanf(" %c", &c);
    return c;
}


int main(void) {
    double temp;
    char input;

    while(1) {
        printmenu();
        input = inputc();

        if(input == 'q') break;
        else if (input == 'c'){
            printf("섭씨: ");
            scanf(" %lf", &temp);
            printf("화씨: %lf\n", celtofer(temp));
        } else if (input == 'f'){
            printf("화씨: ");
            scanf(" %lf", &temp);
            printf("섭씨: %lf\n", fertocel(temp));
        }
        getchar();
    }
    return 0;
}