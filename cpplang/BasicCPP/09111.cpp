#include <iostream>

bool fizzbuzz(int n);

int main() {
    int x;
    std::cin >> x;

    if(fizzbuzz(x)) {
        std::cout << "True" << std::endl;
    } else {
        std::cout << "False" << std::endl;
    }
}

bool fizzbuzz(int n) {
    return ((n % 3 == 0) || (n % 5 == 0));
}
