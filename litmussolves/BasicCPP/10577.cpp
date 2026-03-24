#include <iostream>
#include <string>
using namespace std;

class Account {
private:
   string acc_num;
   int balance;

public:
   Account(string num, int bal) :
      acc_num(num), balance(bal)
   { }

   string GetAcc_Num() {
      return this->acc_num;
   }

   int GetBal() {
      return this->balance;
   }
};

class KBAccount : public Account {
private:
   int trans_limit;

public:
   KBAccount(string an, int ba, int tl) :
      Account(an, ba), trans_limit(tl)
   { }

   void ShowData() {
      cout << "acc_num : " << Account::GetAcc_Num() << endl;
      cout << "balance : " << Account::GetBal() << endl;
      cout << "trans_limit : " << this->trans_limit << endl;
   } 
};

int main()
{
string num;
int bal, limit;
cin >> num >> bal >> limit;
KBAccount acc(num, bal, limit);
acc.ShowData();
return 0;
}