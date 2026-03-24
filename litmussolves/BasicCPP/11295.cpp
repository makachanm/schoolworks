#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    string phone;

public:
    Person(string n, string p) : 
        name(n), phone(p) 
    { }

    void ShowInfo() {
        cout << "Name: " << this->name << endl;
        cout << "Phone: " << this->phone << endl;
    }
};

class Customer : public Person {
private:
    int cusnum;
    int mile;

public:
    Customer(string n, string p, int cn, int mi) :
        Person(n, p), cusnum(cn), mile(mi)
    { }

    void ShowInfo() {
        Person::ShowInfo();
        cout << "Member: " << this->cusnum << endl;
        cout << "Mileage: " << this->mile << endl;
    } 
};

int main()
{
    string name, phone;
    int member, mileage;

    cin>>name>>phone;

    Person per(name,phone);

    per.ShowInfo();                                                       // 개인 정보 출력

    cin>>name>>phone>>member>>mileage;

    Customer cus(name,phone,member,mileage);      

    cus.ShowInfo();                                                       // 고객 정보 출력

    return 0;
}