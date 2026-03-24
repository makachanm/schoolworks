#include <iostream>

class Array {
private:
    int* ptr;
    int size;

public:
    Array(int first, int len) :
        size(len), ptr(new int[len])
    { 
        for(int i = first; i < (first + len); i++) {
            this->ptr[i - first] = i;
        }
    }

    Array(const Array& ref) :
        size(ref.size)
    {
        this->ptr = new int[ref.size];
        for(int i = 0; i < ref.size; i++)
            this->ptr[i] = ref.ptr[i];
    }

    ~Array() {
        delete[] ptr;
    }

    void PrintArr() {
        for(int i = 0; i < this->size; i++)
            std::cout << this->ptr[i] << " ";
        std::cout << std::endl;
    }

    Array operator+(const Array& ref) {
        if(this->size != ref.size) {
            std::cout << "Wrong dimension" << std::endl;
            return *this;
        }

        for(int i = 0; i < ref.size; i++)
            this->ptr[i] += ref.ptr[i];

        return *this;
    }

    friend Array operator+(const Array& ref, int power);
    friend Array operator+(int power, const Array& ref);
};

Array operator+(const Array& ref, int power) {
    Array a(ref);

    for(int i = 0; i < a.size; i++) {
        a.ptr[i] = a.ptr[i] + power;
    }

    return a;
}

Array operator+(int power, const Array& ref) {
    Array a(ref);

    for(int i = 0; i < a.size; i++) {
        a.ptr[i] = a.ptr[i] + power;
    }

    return a;
}


int main()
{
   Array arr1( 1,5 );
   arr1.PrintArr();

   Array arr2( 2,3 );
   arr2.PrintArr();

   Array arr3( 2,5 );
   arr3.PrintArr();

   Array arr4 = arr1 + arr2;
   Array arr5 = arr1 + arr3;
   arr5.PrintArr();

   Array arr6 = arr5 + 3;
   arr6.PrintArr();

   Array arr7 = 3 + arr5;
   arr7.PrintArr();

   return 0;
}