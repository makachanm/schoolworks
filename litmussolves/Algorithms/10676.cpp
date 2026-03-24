#include <iostream>
#include <vector>

long long compareCount = 0;

void doMerge(std::vector<long long> &arr, long long start, long long mid, long long end) {
    long long i = start, j = mid + 1;
    long long k = 0;

    std::vector<long long> temp(end - start + 1);
    while(i <= mid && j <= end) {
        compareCount++;
        if(arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    } 

    while (j <= end) {
        temp[k++] = arr[j++];
    }

    i = start; 
    k = 0;
    while(i <= end) {
        arr[i++] = temp[k++];
    }
}

void mergeSort(std::vector<long long> &arr, long long start, long long end) {
    if(start < end) {
        long long mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        doMerge(arr, start, mid, end);
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

    mergeSort(arr, 0, n - 1);
    std::cout << compareCount << std::endl;

    return 0;
}