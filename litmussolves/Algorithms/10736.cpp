#include <iostream>
#include <vector>

int main() { 
    

    int q, r;
    std::cin >> q >> r;
    std::vector<std::vector<int>> m(q, std::vector<int>(r, 0));
    for(int i = 0; i < q; i++) {
        for(int j = 0; j < r; j++) {
            std::cin >> m[i][j];
        }
    }

    //find the most cheapest path
    //우선, (0,0)은 첫 가중치로 초기화한다.
    //그 뒤, 모든 path에 대해서 값을 계산한다.
    std::vector<std::vector<int>> n(q, std::vector<int>(r, 0));

    n[0][0] = m[0][0];

    for(int i = 1; i < q; i++) {
        n[i][0] = n[i - 1][0] + m[i][0];
    }

    for(int i = 1; i < r; i++) {
        n[0][i] = n[0][i - 1] + m[0][i];
    }

    for(int i = 1; i < q; i++) {
        for(int j = 1; j < r; j++) {
            n[i][j] = std::min(n[i - 1][j], n[i][j -1]) + m[i][j]; 
        }
    }

    std::cout << n[q - 1][r - 1];

    return 0;
}