#include <iostream>

//just for test

int add(int a = 1, int b = 2);
//int example(int a = 1, int b = 1, int c);

namespace AAA {
    namespace BBB {
        namespace CCC {
            int num1 = 1;
        }
    }
}

namespace Hello {
    namespace HHello {
        void hello();
    }

    namespace XHello {
        void hello();
    }
}

namespace ABC = AAA::BBB::CCC;

int main() {
    std::cout << add() << std::endl;
    std::cout << add(3) << std::endl;
    std::cout << add(3, 5) << std::endl;

    std::cout << add(2.0) << std::endl;
    std::cout << add(2.2, 3.3) << std::endl;

    std::cout << ABC::num1 << std::endl;

    Hello::HHello::hello();
    Hello::XHello::hello();

    return 0;
}

int add(int num1, int num2) {
    return num1 + num2;
}

float add(float num1, float num2) {
    return num1 + num2;
}

void Hello::HHello::hello() {
    std::cout << "Hello from H!" << std::endl;
}

void Hello::XHello::hello() {
    std::cout << "Hello from X!" << std::endl;
}
