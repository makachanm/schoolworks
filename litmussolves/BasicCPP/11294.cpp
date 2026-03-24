#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string name;
    string isbn;
    int price;

public:
    Book(string n, string i, int p) :
        name(n), isbn(i), price(p)
    { }

    void ShowBookInfo() {
        cout << "name: " << this->name << endl;
        cout << "ISBN: " << this->isbn << endl;
        cout << "price: " << this->price << endl;
    }
};

class Ebook : public Book {
private:
    string pkey;

public:
    Ebook(string n, string i, int p, string pk) :
        Book(n, i, p), pkey(pk) 
    { }

    void ShowBookInfo() {
        Book::ShowBookInfo();
        cout << "DRMkey: " << this->pkey << endl;
    }
};

int main()
{
    string name, isbn, key;
    int price;

    cin >> name >> isbn >> price;

    Book book(name, isbn, price);
    book.ShowBookInfo();

    cin >> name >> isbn >> price >> key;

    Ebook ebook(name, isbn, price, key);
    ebook.ShowBookInfo();

    return 0;
}