#include <iostream>

class First {
public:
    void overloadFunc() {
        std::cout << "First Class" << std::endl;
    }

    virtual void virtualFunc() {
        std::cout << "First Class" << std::endl;
    }
};

class Second : public First {
public:
    void overloadFunc() {
        std::cout << "Second Class" << std::endl;
    }

    virtual void virtualFunc() {
        std::cout << "Second Class" << std::endl;
    }
};

class Third : public Second {
public:
    void overloadFunc() {
        std::cout << "Third Class" << std::endl;
    }

    virtual void virtualFunc() {
        std::cout << "Third Class" << std::endl;
    }
};

int main()
{
    Third * tptr = new Third();
    Second * sptr = tptr;
    First * fptr= sptr;

    fptr->overloadFunc();
    sptr->overloadFunc();
    tptr->overloadFunc();

    fptr->virtualFunc();
    sptr->virtualFunc();
    tptr->virtualFunc();

    delete tptr;
    return 0;
}