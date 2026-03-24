#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
    int len;
    char* str = NULL;

public:
    String() : len(0), str(NULL) { }

    String(const char* c) {
        int len = strlen(c);

        this->str = new char[len];
        this->len = len;
        strcpy(this->str, c);
    }

    String(const String& ref) {
        int len = ref.len;

        this->len = len;
   this->str = new char[len];
        strcpy(this->str, ref.str);
    }

    ~String() {
        if(this->str != NULL)
            delete[] str;
    }

    String& operator=(const String& ref) {
        if(this->str != NULL)
            delete[] str;

        int len = ref.len;
        this->len = len;
        this->str = new char[len];

        strcpy(this->str, ref.str);

        return *this;
    }

    String& operator+=(const String& ref) {
        int len = (this->len + ref.len);
        this->len = len;

        char* sum = new char[len];
        strcpy(sum, this->str);
        strcat(sum, ref.str);

        if(this->str != NULL)
            delete[] str;
        this->str = new char[len];

        strcpy(this->str, sum);

        return *this;
    }

    String operator+(const String& ref) {
        int len = (this->len + ref.len);

        char* sum = new char[len];
        strcpy(sum, this->str);
        strcat(sum, ref.str);

        String r(sum);
        delete[] sum;

        return r;
    }

    bool operator==(const String& ref) {
        return (strcmp(this->str, ref.str) == 0) ? true : false;
    }

    friend ostream& operator<<(ostream& os, String& s);
    friend istream& operator>>(istream& is, String& s);
};

ostream& operator<<(ostream& os, String& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& is, String& s) {
    char x[100];
    is >> x;

    s = String(x);
    return is;
}

int main()
{
    String str1;
    String str2;
    String str3;

    cin>>str1;
    cin>>str2;

    cout << str1 << endl;
    cout << str2 << endl;

    str3 = str1+str2;
    cout << str3 << endl;

    str2+=str1;
    cout << str2 << endl;

    if(str2 == str3)    cout<<"same string"<<endl;
    else                     cout<<"different string"<<endl;

    return 0;
}