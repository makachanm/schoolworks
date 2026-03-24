#include <iostream>
#include <vector>

int hash(int key, int retry, int tablesize) { 
    return (key + retry) % tablesize;
}

bool isprime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

std::vector<int> hashtable;

int main() {
    int n;
    std::cin >> n;

    int k = n * 2;

    while(!isprime(k)) {
        k++;
    }

    int totalcrash = 0;
    hashtable.resize(k, 0);

    for(int i = 0; i < n; i++) {
        int key;
        std::cin >> key;

        int pos = hash(key, 0, k);
        int retry = 0;
        while(hashtable[pos] != 0) {
            retry++;
            totalcrash++;
            pos = hash(key, retry, k);  
        }
        hashtable[pos] = key;
    }

    std::cout << totalcrash << std::endl;
}