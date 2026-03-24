#include <iostream>

float area(int x1);
float area(int x, int x2);
float area(int x, int x2, int x3);

float perimeter(int x1);
float perimeter(int x1, int x2);
float perimeter(int x1, int x2, int x3);

int main() {
    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);

    int selection;

    int n1, n2, n3;
    float area_r, perimeter_r;

    bool running = true;

    while(running) {
        std::cin >> selection;
        switch (selection)
        {
        case 0:
            running = false;
            break;

        case 1:
            std::cin >> n1 >> n2;
            if ((n1 < 0) || (n2 < 0)){
                std::cout << "incorrect number" << std::endl;
                break;
            }

            area_r = area(n1, n2);
            perimeter_r = perimeter(n1, n2);

            std::cout << (int)area_r << " " << (int)perimeter_r << std::endl;

            break;

        case 2:
            std::cin >> n1;
            if (n1 < 0) {
                std::cout << "incorrect number" << std::endl;
                break;
            }

            area_r = area(n1);
            perimeter_r = perimeter(n1);

            std::cout << area_r << " " << perimeter_r << std::endl;
            break;

        case 3: 
            std::cin >> n1 >> n2 >> n3;
            if ((n1 < 0) || (n2 < 0) || (n3 < 0)){
                std::cout << "incorrect number" << std::endl;
                break;
            }

            area_r = area(n1, n2, n3);
            perimeter_r = perimeter(n1, n2, n3);

            std::cout << (int)area_r << " " << (int)perimeter_r << std::endl;
            break;
        
        default:
            std::cout << "wrong menu" << std::endl;
            break;
        }
    }

    return 0;
}

float area(int x1) {
    return 3.14 * (x1 * x1);
}

float area(int x1, int x2) {
    return x1 * x2;
}

float area(int x1, int x2, int x3) {
    return (((x1 * x2) + (x1 * x3) + (x2 * x3)) * 2);
}

float perimeter(int x1) {
    return 2 * 3.14 * x1;
}

float perimeter(int x1, int x2) {
    return 2 * (x1 + x2);
}

float perimeter(int x1, int x2, int x3) {
    return ((x1 + x2 + x3) * 4);
}