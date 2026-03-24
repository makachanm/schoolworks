#include <iostream>
#include <string.h>

using namespace std;

class SimpleClass{
private:
    int num1;
    int num2;
public:
    SimpleClass(int n1, int n2) : num1(n1), num2(n2) { }
    SimpleClass(const SimpleClass& copy) :
        num1(copy.num1), num2(copy.num2)
    {
        cout << "Copy constructor is called!" << endl;
    }
};

class Prsn {
private:
    char* name;

public:
    Prsn(const char* name) {
        int length = strlen(name);
        this->name = new char[length+1];
        strcpy(this->name, name);
    }

    Prsn(const Prsn& copy) {
        //for deep copy
        int length = strlen(copy.name);
        this->name = new char[length+1];
        strcpy(this->name, copy.name);
    }

    const char* getname() {
        return name;
    }

    ~Prsn() {
        std::cout << "deleting" << std::endl;
        delete[] name;
    }
};

int main() {
    SimpleClass sc1(15, 20);

    cout << "Before creation..." << endl;
    SimpleClass sc2 = sc1;
    cout << "After creation..." << endl;

    Prsn man1("Jane");
    Prsn man2 = man1;
    Prsn man3(man2);

    cout << man2.getname() << endl;
    cout << man3.getname() << endl;

    return 0;
}