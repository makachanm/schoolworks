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

    Array& operator=(const Array& ref) {
         delete[] ptr;
         
         this->ptr = new int[ref.size];
         this->size = ref.size;

         for(int i = 0; i < ref.size; i++) 
            this->ptr[i] = ref.ptr[i]; 

         return *this;  
   }
    
};

int main()
{
   Array arr1( 1,5 );
   arr1.PrintArr();

   Array arr8( 2,3 );
   arr8.PrintArr();

   arr8 = arr1;
   arr8.PrintArr();

   return 0;
}