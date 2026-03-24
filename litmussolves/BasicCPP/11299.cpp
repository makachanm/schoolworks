#include <iostream>

class BaseNum
{
protected:
    int *bnum;
public:
    BaseNum(int x) {
        this->bnum = new int(x);
    } 

    virtual ~BaseNum() {
        delete bnum;
    }

    virtual void print() {
        std::cout << *this->bnum << std::endl;
    }
};

class DerivedNum : public BaseNum
{
protected:
    int *dnum;
public:
    //생성자, 소멸자, print 함수 구현
    DerivedNum(int x, int y) :
        BaseNum(x)
    {
        this->dnum = new int(y);
    } 

    virtual ~DerivedNum() {
        delete dnum;
    }

    void print() {
        BaseNum::print();
        std::cout << *this->dnum << std::endl;
    }
};

int main() 
{
    BaseNum *b = new BaseNum{ 10 };
    BaseNum *d = new DerivedNum{ 5 , -7 };

    b->print();
    d->print();

    delete b;
    delete d;

    return 0;
}