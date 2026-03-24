#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::priority_queue<long long, std::vector<long long>, std::less<long long>> minHeap;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, q;
    std::cin >> n;
        
    for(long long i = 0; i < (n * n); i++) {
        std::cin >> q;
        minHeap.push(q);
    
        if(minHeap.size() < n) {
            minHeap.push(q);
        } else {
            if(minHeap.top() < q) {
                minHeap.pop();
                minHeap.push(q);
            } else {
                continue;
            }
        }
    }

    for(long long i = 0; i < n - 1; i++)
        minHeap.pop();

    std::cout << minHeap.top() << std::endl;

    
    return 0;

}