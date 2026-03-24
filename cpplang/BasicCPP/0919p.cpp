#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int height = ((2 * n) - 1);
    int weight = n - 1;

    /* 스페이스 출력 -> 별 출력 -> 사이 공간 출력 -> 별 출력 */

    for (int x = 0; x < height; x++) {
        if (x < n) {
            for(int i = 0; i < (weight - x); i++) {
                std::cout << " ";
            }

            for(int i = (weight - x); i < (weight - x + 1); i++) {
                std::cout << "*";
            }

            for(int i = weight - 1; (weight - x) < i; i--) {
                std::cout << " ";
            }

            for(int i = weight; i > (weight - x); i--) {
                std::cout << "*";
                break;
            }
           
        } else {
            for(int i = weight; i < x; i++) {
                std::cout << " ";
            }

            for(int i = weight; i > (weight - 1); i--) {
                std::cout << "*";
            }

            for(int i = 0; i < (height - x - 2); i++) {
                std::cout << " ";
            }

            for(int i = 0; i < (height - x -1); i++) {
                std::cout << "*";
                break;
            }

        }

        std::cout << std::endl;
    }
}