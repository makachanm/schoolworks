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

   void Transfer(Account& ac, int amount) {
      ac.Withdraw(amount);
      this->Deposit(amount);
   }

};

void exiterror() {
   std::cout << "Error" << std::endl;
   exit(0);
}

int main() {
   int id1, amount1, id2, amount2;
   int menu;
   bool running = true;

   int a, ida, idb;

   std::cin >> id1 >> amount1;
   std::cin >> id2 >> amount2;
   
   Account ac1(id1, amount1);
   Account ac2(id2, amount2);

   while(running) {
      std::cin >> menu;
      switch (menu)
      {
      case 0:
         running = false;
         break;
      
      case 1:
         std::cin >> ida;

         if(ida == id1) {
            ac1.ShowBalance();
         } else if (ida == id2) {
            ac2.ShowBalance();
         } else {
            exiterror();
         }
         break;

      case 2:
         std::cin >> ida;
         std::cin >> a;

         if(ida == id1) {
            ac1.Deposit(a);
         } else if (ida == id2) {
            ac2.Deposit(a);
         } else {
            exiterror();
         }
         break;

      case 3:
         std::cin >> ida;
         std::cin >> a;

         if(ida == id1) {
            ac1.Withdraw(a);
         } else if (ida == id2) {
            ac2.Withdraw(a);
         } else {
            exiterror();
         }
         break;

      case 4:
         std::cin >> ida >> idb;
         std::cin >> a;
         
         if(ida == idb) {
            exiterror();
         }

         if(ida == id1) {
            if(idb == id2) {
               ac2.Transfer(ac1, a);
            } else {
               exiterror();
            }
         } else if (ida == id2) {
            if(ida == id1) {
               ac1.Transfer(ac2, a);
            } else {
               exiterror();
            }
         } else {
            exiterror();
         }
         break;
      
      default:
         break;
      }
   }
   
   return 0;
}