#include <iostream>
#include <map>
#include <string>

std::map<std::string, int> students;

int main() {
    int menu;
    bool isRunning = true;

    while(isRunning) {
        std::cin >> menu;

        std::string name = "";
        int score = 0;

        typename std::map<std::string, int>::iterator result;

        switch (menu)
        {
        case 1:
            std::cin >> name >> score;
            result = students.find(name);

            if(result == students.end()) {
                students.insert(std::make_pair(
                    name, score
                ));
            } else {
                (*result).second = score;
            }
            break;

        case 2:
            std::cin >> name;
            result = students.find(name);
            if(result != students.end())
                std::cout << (*result).first << " " << (*result).second << std::endl;
            else 
                std::cout << "None" << std::endl;
            break;

        case 3:
            if(students.size() < 1) {
                std::cout << "None" << std::endl;
                break;
            }
            std::cout << "[";
            for(auto i = students.begin(); i != students.end(); i++) {
                std::cout << (*i).first << ": " << (*i).second;
                if(i != (--students.end())) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << std::endl;;
            break;

        case 4:
            isRunning = false;
        
        default:
            break;
        }
    }    

    
    return 0;
}