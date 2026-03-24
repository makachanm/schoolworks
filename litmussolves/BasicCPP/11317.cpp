#include <iostream>
using namespace std;

template<typename T>
class SmartArray {
private:
   int len;
   T* data;

public:
   SmartArray(T initial) : 
      len(5), data(new T[5])
   {
      for(int i = 0; i < this->len; i++)
         this->data[i] = (initial + i);
   }

   void Print() {
      for(int i = 0; i < this->len; i++)
         cout << this->data[i] << " ";
      cout << endl;
   }
};

int main()

{

    int d;

    double f;

    char c;

    cin >> d >> f >> c;

    SmartArray<int> Ary1(d);

    SmartArray<double> Ary2(f);

    SmartArray<char> Ary3(c);

    Ary1.Print();

    Ary2.Print();

    Ary3.Print();

    return 0;

}