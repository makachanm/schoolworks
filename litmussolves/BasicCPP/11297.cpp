#include <iostream>

class Base
{
public:
    virtual void print() {
        std::cout << "Base Class" << std::endl;
    }
};

class Derived : public Base
{
public:
    void print() {
        std::cout << "Derived Class" << std::endl;
    }
};

void Message(Base *pB)
{
    pB->print();
}

int main()
{
    Base B;
    Derived D;

    Message(&B);
    Message(&D);

    return 0;
}