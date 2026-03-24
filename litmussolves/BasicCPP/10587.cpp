#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
   string acc_num;
   int balance;
   int trans_limit;

   bool QuietWithdraw(int amount) {
      if(amount > this->trans_limit) {
         cout << "trans_limit exceed" << endl;
         return false;
      }

      if(this->balance - amount < 0) {
         cout << "not enough money" << endl;
         return false;
      } else {
         this->balance -= amount;
         return true;
      }
   }

public:
   Account(string num, int bal, int limit) :
      acc_num(num), balance(bal), trans_limit(limit)
   { }

   string GetAcc_Num() {
      return this->acc_num;
   }

   int GetBal() {
      return this->balance;
   }

   void Deposit(int amount) {
      this->balance += amount;
      cout << "deposit complete" << endl;
   }

   void Withdraw(int amount) {
      if(amount > this->trans_limit) {
         cout << "trans_limit exceed" << endl;
         return;
      }

      if(this->balance - amount < 0) {
         cout << "not enough money" << endl;
      } else {
         this->balance -= amount;
         cout << "withdraw complete" << endl;
      }
   }
}; 

class JBAccount  : public Account {
private:
   static int const KB = 500;
   static int const GB = 1000;
   static int const NH = 1500;

   int trans_balance;

public:
    JBAccount (string an, int ba, int tl) :
      Account(an, ba, tl), trans_balance(0)
   { }

   void TransferMoney(int amount, int banktype) {
      int commision = 0;

      switch (banktype)
      {
      case 1:
         commision = KB;
         break;
      
      case 2:
         commision = GB;
         break;

      case 3:
         commision = NH;
         break;
      
      default:
         break;
      }

      int x = (amount + commision);
      if((x + this->trans_balance) > this->trans_limit) {
         cout << "trans_limit exceed" << endl;
         return;
      }

      if(Account::QuietWithdraw(x)) {
         cout << "transfer complete" << endl;
         this->trans_balance = amount;
      }

      
   }

   void ShowData() {
      cout << "acc_num : " << Account::GetAcc_Num() << endl;
      cout << "balance : " << Account::GetBal() << endl;
      cout << "trans_limit : " << this->trans_limit << endl;
      cout << "trans_balance : " << this->trans_balance << endl;
   } 
};


int main() {
   string id;
   int limit;

   std::cin >> id >> limit;

   JBAccount ac(id, 0, limit);

   int menu;
   int x;
   int b;
   bool running = true;

   while(running) {
      std::cin >> menu;

      switch (menu)
      {
      case 1:
         cin >> x;
         ac.Deposit(x);
         break;
      
      case 2:
         cin >> x;
         ac.Withdraw(x);
         break;

      case 3:
         cin >> b >> x;
         ac.TransferMoney(x, b);
         break;

      case 4:
         ac.ShowData();
         break;

      case 5:
         running = false;
         break;
      
      default:
         break;
      }
   }
}