#include <iostream>

class Base {
private:
    double* d1;

public:
    Base(int n) {
        this->d1 = new double[n];
        std::cout << "size of d1: " << sizeof(*this->d1) << std::endl;
    }

    virtual ~Base() {
        std::cout << "~Base() : " << sizeof(*this) << std::endl;

        delete[] d1;
    }
};

class Derived : public Base {
private:
    int* d2;

public:
    Derived(int n1, int n2) :
        Base(n1)
    {
        this->d2 = new int[n2];
        std::cout << "size of d2: " << sizeof(*this->d2) << std::endl;
    }

    ~Derived() {
        std::cout << "~Derived() : " << sizeof(*this) << std::endl;

        delete[] d2;
    }
};

int main(){
    Base* ptr = new Derived(10, 20);
    delete ptr;

    return 0;
}