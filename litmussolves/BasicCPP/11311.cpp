#include <iostream>
using namespace std;

class Square {
private:
   int* arr;
   int n;

public:
   Square(int n) :
      arr(new int[n]), n(n)
   { }

   ~Square() {
      delete[] arr;
   }

   int& operator[](int idx) {
      if(idx < 0)
         exit(-1);

      return this->arr[idx];
   }
};

int main()
{
    int n;
    cin >> n;

    Square s{n};

    for(int i = 0; i < n; i++)
        s[i] = (i+1) * (i+1);

    for(int i = 0; i < n; i++)
        cout << s[i] << ' ';

    cout << endl;
    return 0;
}