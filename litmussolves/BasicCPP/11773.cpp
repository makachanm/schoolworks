#include <iostream>
#include <map>
#include <vector>

int main() {
    int n, m;
    std::cin >> n;

    std::map<int, int> nmap;

    for(int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        nmap.insert(std::make_pair(x, i));
    }

    std::cin >> m;
    std::vector<int> mx;

    for(int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        mx.push_back(x);
    }
    
    for(auto q = mx.begin(); q != mx.end(); q++) {
        auto rs = nmap.find(*(q));
        if(rs != nmap.end()) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "0" << std::endl;
        }
    }

    return 0;
}