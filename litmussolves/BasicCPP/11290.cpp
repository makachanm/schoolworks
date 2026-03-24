#include <iostream>
#include <string>

class Account {
private:
   static int totalacc;
   std::string name;
   int balance;      

public:
   Account(std::string aname, int abalance):
      name(aname), balance(abalance)
   {
      this->totalacc++;
   }

   static void print_total() {
      std::cout << "num client: " << totalacc << std::endl;
   }

   ~Account() {
      this->totalacc--;
   }
};

int Account::totalacc = 0;

int main()
{
 Account::print_total();
 Account kim( "kim", 10000 );
 Account::print_total();

 {
  Account lee( "lee", 20000 );
  Account::print_total();
 }
 Account::print_total();

 Account *park = new Account("Park", 50000);
 Account::print_total();
 delete park;
 Account::print_total();
 return 0;
}