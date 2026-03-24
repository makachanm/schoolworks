#include <iostream>

int& func(int n) {
    int num = 20;
    num += n;
    return num;
}

int main() {
    return 0;
}