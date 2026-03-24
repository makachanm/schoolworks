#include <iostream>

class MyArray {
private:
    int len;
    int* val;

public:
    MyArray(int x) :
        len(x), val(new int[x])
    { }

    ~MyArray() {
        delete[] val;
    }

    int length() const {
        return this->len;
    }

    int& operator[](int i) {
        if(i < 0 || i >= this->len) {
            std::cout << "out of index" << std::endl;
            exit(-1);
        }
        
        return this->val[i];
    }

    int& operator[](int i) const {
        if(i < 0 || i >= this->len) {
            std::cout << "out of index" << std::endl;
            exit(-1);
        }
        
        return this->val[i];
    }

    MyArray& operator=(const MyArray& u) {
        delete[] val;

        this->len = u.length();
        this->val = new int[u.length()];

        for(int i = 0; i < u.length(); i++) {
            this->val[i] = u.val[i];
        }

        return *this;
    }
};

void show(const MyArray& ref){
    for(int i = 0; i < ref.length(); i++)
        std::cout << ref[i] << std::endl;
}

int main() {
    int array[3] = {0, 1, 2};
    array[-1] = 5;
    std::cout << array[-1] << std::endl;

    std::cout << "marray" << std::endl;
    MyArray marray(3);
    marray[2] = 3;
    std::cout << marray[2] << std::endl;

    std::cout << "show marray" << std::endl;
    show(marray);

    std::cout << "copied" << std::endl;
    MyArray xa(0);
    xa = marray;
    show(xa);

    std::cout << "oidx" << std::endl;
    marray[-1] = 3;
    std::cout << marray[-1] << std::endl;

    return 0;
}