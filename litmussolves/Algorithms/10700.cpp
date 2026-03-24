#include <iostream>
#include <vector>

void countingSort(std::vector<long long> &arra, std::vector<long long> &arrb) {
    long long min, max;
    min = arra[0];
    max = arra[0];

    for(long long i = 0; i < arra.size(); i++) {
        if(arra[i] < min) min = arra[i];
        if(arra[i] > max) max = arra[i];
    }

    long long k = max - min + 1;
    std::vector<long long> c(k);

    for (long long i = 0; i < arra.size(); i++) {
        c[arra[i] - min]++;
    }

    for(long long i = 1; i < k; i++) {
        c[i] += c[i - 1];
    }

    for(long long i = 0; i < c.size(); i++) {
        std::cout << c[i] << " ";
    }

    for (long long i = arra.size() - 1; i > 0; i--) {
        arrb[c[arra[i] - min] - 1] = arra[i];
        c[arra[i] - min]--;
    }
}

int main() {
    long long n;
    std::cin >> n;
    if (n < 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<long long> arra(n);
    std::vector<long long> arrb(n);
    for(long long i = 0; i < n; i++) {
        std::cin >> arra[i];
    }

    countingSort(arra, arrb);

    return 0; 
}