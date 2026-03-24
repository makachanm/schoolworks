#include <iostream>

class Base {
private: 
    int a;

public:
    Base() : a(10) 
    { }

    virtual void show() {
        std::cout << "Base: " << a << std::endl;
    }
};

class Derived : public Base {
private:
    int a;

public:
    Derived() :
        Base(), a(20)
    { }

    virtual void show() {
        std::cout << "Derived: " << a << std::endl;
    }
};

class DoubleDerived : public Derived {
private:
    int a;

public:
    DoubleDerived() :
        Derived(), a(30)
    { }

    void show() {
        std::cout << "DoubleDerived: " << a << std::endl;
    }
};

int main() {
    DoubleDerived* dd = new DoubleDerived();
    Derived* d = dd;
    Base* b = dd;

    dd->show();
    d->show();
    b->show();

    Derived* x = new Derived();
    Base* y = x;
    
    x->show();
    y->show();

    return 0;
}