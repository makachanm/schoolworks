#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> m;
    for(int i = 0; i < n; i++) {
        int t1, t2;
        std::cin >> t1 >> t2;
        m.push_back(std::pair<int, int>(t1, t2));
    }

    //행렬 곱셈 순서 문제
    std::vector<std::vector<int>> k(n, std::vector<int>(n));
    for(int i = 0; i < n; i++) {
        k[i][i] = 0;
    }

    for(int i = 0; i < n -1; i++) {
        for(int j = 0; j < n - i; j++) { 
            int p = i + j;
            k[j, p] = std::min();
        }
    }

    return 0;
}