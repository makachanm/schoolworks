#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> minHeap;

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n, target_v;
    std::cin >> n >> target_v;

    for(long long i = 0; i < n; i++) {
        long long q;
        std::cin >> q;
        minHeap.push(q);
    }

    int count = 0;

    while(minHeap.size() >= 2 && minHeap.top() <= target_v){
        long long first = minHeap.top();
        minHeap.pop();

        long long second = minHeap.top();
        minHeap.pop();

        long long mixed = first + (second * 2);
        minHeap.push(mixed);

        count++;
    }

    if(!minHeap.empty() && minHeap.top() >= target_v) {
        std::cout << count << std::endl;
    } else {
        std::cout << "-1" << std::endl;
    }

    return 0;

}
