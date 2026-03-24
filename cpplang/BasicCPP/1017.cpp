#include <iostream>

class BaseClass {
private:
    int base_num;

public:
    BaseClass(int n) : base_num(n) { 
        std::cout << "BaseClass(n) : " << this->base_num << std::endl;
    }

    ~BaseClass() {
        std::cout << "~BaseClass()" << std::endl;
    }
}

class DerivedClass : public BaseClass {
    
}

int main() { 
    return 0;
}