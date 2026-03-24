#include <iostream>
#include <string.h>
using namespace std;

class NameCard {
private:
    char* name;
    char* id;
    char* phone;

public:
    NameCard(char* name, char* id, char* phone) { 
        int nl = strlen(name) + 1;
        int il = strlen(id) + 1;
        int pl = strlen(phone) + 1;

        this->name = new char[nl];
        this->id = new char[il];
        this->phone = new char[pl];

        strcpy(this->name, name);
        strcpy(this->id, id);
        strcpy(this->phone, phone);
    }

    NameCard(NameCard& n) { 
        this->name = new char[sizeof(n.getname())];
        this->id = new char[sizeof(n.getid())];
        this->phone = new char[sizeof(n.getphone())];

        strcpy(this->name, n.getname());
        strcpy(this->id, n.getid());
        strcpy(this->phone, n.getphone());
    }

    ~NameCard() {
        delete[] name;
        delete[] id;
        delete[] phone;
    }

    char* getname() {
        return this->name;
    }

    char* getid() {
        return this->id;
    }

    char* getphone() {
        return this->phone;
    }

    void Show() {
        cout << "name: " << this->name << std::endl;
        cout << "ID: " << this->id << std::endl;
        cout << "phone: " << this->phone << std::endl;
        cout << endl;
    }

    void setInfo(char* name, char* id, char* phone) {
        strcpy(this->name, name);
        strcpy(this->id, id);
        strcpy(this->phone, phone);
    }
};

int main()
{
    char name[80], ID[80], phone[80];
    cin >> name >> ID >> phone;

    NameCard man1(name, ID, phone);
    NameCard man2 = man1;

    cin >> name >> ID >> phone;

    man2.setInfo(name, ID, phone);
    man1.Show();
    man2.Show();
    return 0;
}