#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

int main() {
    std::vector<int> s(5);

    for(int i = 0; i < 5; i++)
        s[i] = i;

    std::cout << "Logical Space: " << s.size() << std::endl;
    std::cout << "Physical Space: " << s.capacity() << std::endl;

    s.push_back(6);
    std::cout << "Pushed: 1" << std::endl;

    std::cout << "Logical Space: " << s.size() << std::endl;
    std::cout << "Physical Space: " << s.capacity() << std::endl;

    for(int i = 0; i < 5; i++)
        s.push_back(i * 10);
    std::cout << "Pushed: 10" << std::endl;

    std::cout << "Logical Space: " << s.size() << std::endl;
    std::cout << "Physical Space: " << s.capacity() << std::endl;

    for(int i = 0; i < 3; i++)
        s.pop_back();
    std::cout << "Poped: 3" << std::endl;

    std::cout << "Logical Space: " << s.size() << std::endl;
    std::cout << "Physical Space: " << s.capacity() << std::endl;

    std::cout << "Datas: " << std::endl;
    auto it = s.begin();
    for(; it != s.end(); it++) 
        std::cout << *(it) << " ";
    std::cout << std::endl;

    std::sort(s.begin(), s.end());
    std::cout << "Sorted!" << std::endl;

    std::cout << "Datas: " << std::endl;
    for(it = s.begin(); it != s.end(); it++) 
        std::cout << *(it) << " ";
    std::cout << std::endl;

    std::map<std::string, std::string> pBook {
        { "Kim-Nam", "1999-99-99" },
        { "Park-Suk", "1982-87-73" },
    };

    pBook["MinYooh"] = "1993-11-34";
    pBook.insert(std::make_pair(
        "Jo-Gil", "1956-45-34"
    ));

    for(auto pi = pBook.begin(); pi != pBook.end(); pi++)
        std::cout << pi->first << " : " << pi->second << std::endl;
    
    std::cout << pBook.size() << "(s) registered" << std::endl;

    auto result = pBook.find("MinYooh");
    std::cout << "Result Name: " << result->first << std::endl;
    std::cout << "Result Birth: " << result->second << std::endl;
    
    return 0;
}