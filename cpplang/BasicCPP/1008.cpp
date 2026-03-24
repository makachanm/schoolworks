#include <iostream>
#include <string.h>

class SimpleClass{
private:
    int num;

public:
    SimpleClass(int n = 0){
        num = n;
        std::cout << "num = " << num << ", ";
        std::cout << "addr = " << this << std::endl;
    }

    int get_num(){
        return num;
    }

    SimpleClass* getthis() {
        return this;
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

    const char* getname() {
        return name;
    }

    ~Prsn() {
        std::cout << "deleting" << std::endl;
        delete[] name;
    }
};


int main() {
    SimpleClass sc1;
    SimpleClass* sc1_ptr = sc1.getthis();
    std::cout << sc1_ptr << ", ";
    std::cout << sc1_ptr->get_num() << std::endl;

    Prsn person("Alice");
    std::cout << person.getname() << std::endl;
    
    return 0;
}