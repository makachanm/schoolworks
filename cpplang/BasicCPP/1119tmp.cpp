#include <iostream>
#include <cstring>

template <typename T>
class MyArray {
private:
    int len;
    T* val;

public:
    MyArray(int x) :
        len(x), val(new T[x])
    { }

    ~MyArray() {
        delete[] val;
    }

    int length() const {
        return this->len;
    }

    T& operator[](int i) {
        if(i < 0 || i >= this->len) {
            std::cout << "out of index" << std::endl;
            exit(-1);
        }
        
        return this->val[i];
    }

    T& operator[](int i) const {
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

template <typename T>
void show(const MyArray<T>& ref){
    for(int i = 0; i < ref.length(); i++)
        std::cout << ref[i] << std::endl;
}

template <typename T>
T mmax(T e1, T e2) {
    return (e1 > e2) ? e1 : e2;
}

template <>
char* mmax<char*>(char* a, char* b){    
    return strlen(a) > strlen(b) ? a : b;
}

template <>
const char* mmax<const char*>(const char* e1, const char* e2) {
    return (strcmp(e1, e2) > 0) ? e1 : e2;
}


/*
template <>
char* max<char>(char* e1, char* e2) {
    return (strlen(e1) > strlen(e2)) ? e1 : e2;
}

template <>
const char* max<const char*>(const char* e1, const char* e2) {
    return (strcmp(e1, e2) > 0) ? e1 : e2;
}
*/

int main() {
    MyArray<char> x(3);
    x[0] = 'a';
    x[1] = 'b';
    x[2] = 'c';

    show(x);

    MyArray<int> y(3);
    y[0] = 1;
    y[1] = 2;
    y[2] = 3;

    show(y);

    std::cout << mmax<int>(11, 15) << std::endl;
    std::cout << mmax<char>('T', 'Q') << std::endl;
    std::cout << mmax<const char*>("apple", "banana") << std::endl;
    /*
    cout << max<char*>('T', 'Q') << endl;
    cout << max<const char*>("apple", "banana") << endl;
    */

    return 0;
}