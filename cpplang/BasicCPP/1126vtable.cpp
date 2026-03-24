#include <iostream>

class AAA {
private:
    int num1;

public:
    virtual void Func1() {
        std::cout << "AAA FUNC1" << std::endl;
    }

    virtual void Func2() {
        std::cout << "AAA FUNC2" << std::endl;
    }
};

class BBB : public AAA {
private:
    int num1;

public:
    virtual void Func1() {
        std::cout << "BBB FUNC1" << std::endl;
    }

    void Func3() {
        std::cout << "BBB FUNC3" << std::endl;
    }
};

int main() {
    AAA* aobj = new AAA();
    aobj->Func1();

    BBB* bobj = new BBB();
    bobj->Func1();

    AAA* abobj = new BBB();
    abobj->Func1();
    abobj->Func2();

    return 0;
}