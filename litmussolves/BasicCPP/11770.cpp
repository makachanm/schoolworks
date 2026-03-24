#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

struct xcompare {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b){
        return a.second > b.second;
    }
};

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<std::string, int>> x;

    for(int i = 0; i < n; i++) {
        std::string name;
        int score;

        std::cin >> name >> score;
        x.push_back(make_pair(
            name, score
        ));
    }

    std::sort(x.begin(), x.end(), xcompare());

    for(int i = 0; i < n; i++) {
        std::cout << (i + 1) << ", " << (x[i]).first << ": " << (x[i]).second << std::endl;
    }

    return 0;
}