#include <iostream>
#include <vector>

long long swapCount = 0;

long long partition(std::vector<long long> &arr, long long start, long long end) {
    long long key = arr[end];
    long long i = start - 1;
    for (long long j = start; j <= end - 1; j++) {
        if (arr[j] <= key) {
            i++;
            swapCount++;
            std::swap(arr[i], arr[j]);  
        }
    }
    std::swap(arr[i + 1], arr[end]);
    swapCount++;
    return i + 1;
}

void quickSort(std::vector<long long> &arr, long long start, long long end) {
    if (start < end) {
        long long pivot = partition(arr, start, end);
        quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

int main() {
    long long n;
    std::cin >> n;
    if (n <= 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<long long> arr(n);
    for(long long i = 0; i < n; i++) {
        std::cin >> arr[i]; 
    }

    quickSort(arr, 0, n - 1);
    
    std::cout << swapCount << std::endl;
    return 0;

}