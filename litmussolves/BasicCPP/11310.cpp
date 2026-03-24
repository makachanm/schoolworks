#include <iostream>
using namespace std;

class Fib {
private:
   int* arr;
   int n;

public:
   Fib(int n) :
      arr(new int[n]), n(n)
   { }

   ~Fib() {
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

    Fib f{ n };

    f[0] = 1;
    f[1] = 1;

    for (int i = 2; i < n; i++)
        f[i] = f[i - 1] + f[i - 2];

    for (int i = 0; i < n; i++)
        cout << f[i] << ' ';

    cout << endl;
    return 0;
}