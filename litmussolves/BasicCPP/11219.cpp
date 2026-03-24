#include <iostream>
using namespace std;

class Person {
protected:
        string name;
public:
        Person(string n) :
            name(n)
        { }

        virtual ~Person() {
            cout << name << " ";
        }
};
 
class Student : public Person{
private:
        char grade;
public:
        Student(string n, char g) :
            Person(n), grade(g)
        { }

        ~Student() {
            cout << grade << " ";
        }
};

int main() {
       string name;
       char grade;
       cin >> name >> grade;

        Person *ptr = new Student(name, grade);
        delete ptr;
        return 0;
}
