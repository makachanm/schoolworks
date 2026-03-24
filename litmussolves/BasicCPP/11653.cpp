#include <iostream>

class Account {
private:
   int userid;
   int money;

   void checkBalance(int current) {
      if(current <= 0) {
         std::cout << "Error" << std::endl;
         exit(0);
      }
   }

public:
   Account(int uid, int amount) : 
      userid(uid), money(amount) 
   { }

   void ShowBalance() {
      std::cout << "ID: " << this->userid << " Money: " << this->money << std::endl;
   }

   void Deposit(int amount) {
      int current = this->money;
      current = current + amount;

      this->checkBalance(current);
      this->money = current;
   }

   void Withdraw(int amount) {
      int current = this->money;
      current = current - amount;

      this->checkBalance(current);
      this->money = current;
   }

};

int main() {
   int id, amount, menu;
   bool running = true;
   int a;

   std::cin >> id >> amount;
   
   Account ac(id, amount);

   while(running) {
      std::cin >> menu;
      switch (menu)
      {
      case 0:
         running = false;
         break;

      case 1:
         ac.ShowBalance();
         break;
      
      case 2:
         std::cin >> a;
         ac.Deposit(a);
         break;

      case 3:
         std::cin >> a;
         ac.Withdraw(a);
         break;
      
      default:
         break;
      }
   }
   return 0;
}