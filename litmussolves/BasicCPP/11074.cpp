#include <iostream>
using namespace std;

int main()
{
    int x,y;
    cin>>x>>y;

    /*
    try~catch문
    y 값이 0이면 "Error: y is 0" 출력 후 종료
    y 값이 0이 아니라면 두 수의 덧셈, 뺄셈, 곱셈, 나눗셈 계산 후 출력
    */

      cout << "+: " << x + y << endl;
      cout << "-: " << x - y << endl;
      cout << "*: " << x * y << endl;

      try {
         if(y == 0)
            throw -1;
         
         cout << "/: " << x / y << endl;
      } catch(int e) { 
         cout << "Error: y is 0" << endl;
      }
    return 0;
}