#include <iostream>
#include <cstring>

class Person {
protected:
    char* name;

public:
    Person(char* rname) {
        int len = strlen(rname);
        this->name = new char[len + 1];
        strcpy(this->name, rname);

        std::cout << "Person 생성자: 메모리 할당됨" << std::endl;
    }

    Person(const Person& p) {
        int len = strlen(p.name);
        this->name = new char[len + 1];
        strcpy(this->name, p.name);

        std::cout << "Person 복사 생성자: 메모리 할당됨, 복사됨" << std::endl;
    }

    ~Person() {
        delete []name;

        std::cout << "Person 소멸자: 메모리 해제됨" << std::endl; 
    }

    void ShowName() {
        std::cout << "name: " << this->name << std::endl;
    }
};

class UnivStudent : public Person {
private:
    char* major;

public:
    UnivStudent(char* name, char* major) : 
        Person(name) 
    {
        int len = strlen(major);
        this->major = new char[len + 1];
        strcpy(this->major, major);

        std::cout << "UnivStudent 생성자: 메모리 할당됨" << std::endl;
    }

    UnivStudent(const UnivStudent& stu) :
        Person(stu) 
    {
        int len = strlen(stu.major);
        this->major = new char[len + 1];
        strcpy(this->major, stu.major);

        std::cout << "UnivStudent 복사 생성자: 메모리 할당됨, 복사됨" << std::endl;
    }

    ~UnivStudent() {
        delete []major;

        std::cout << "UnivStudent 소멸자: 메모리 해제됨" << std::endl; 
    }

    void ShowInfo() {
        Person::ShowName();
        std::cout << "major: " << this->major << std::endl;
    }

};

int main() { 
  char myname[32], mymajor[32];
  UnivStudent *pstd; 
 
  std::cin >> myname >> mymajor; 
  pstd = new UnivStudent(myname, mymajor);
  pstd->ShowInfo(); 

  std::cin >> myname >> mymajor; 
  UnivStudent stu = UnivStudent(myname, mymajor); 
  stu.ShowInfo(); 

  UnivStudent copy = stu;
  copy.ShowInfo();
  
  std::cout << std::endl;
    
  std::cout << "동적할당객체 소멸 시작 ... " << std::endl; 
  delete pstd; 

  std::cout << "동적할댕객체 UnivStd 소멸 끝 ... " << std::endl; 
  
  return 0; 
}
