#include <iostream>
#include <cstring>

using namespace std;

class mstring {
private:
    int len;
    char* str = NULL;

public:
    mstring() : len(0), str(NULL) { }

    mstring(const char* c) {
        int len = strlen(c);

        this->str = new char[len];
        this->len = len;
        strcpy(this->str, c);
    }

    mstring(const mstring& ref) {
        int len = ref.len;

        this->len = len;
        this->str = new char[len];
        strcpy(this->str, ref.str);
    }

    ~mstring() {
        if(this->str != NULL)
            delete[] str;
    }

    mstring& operator=(const mstring& ref) {
        if(this->str != NULL)
            delete[] str;

        int len = ref.len;
        this->len = len;
        this->str = new char[len];

        strcpy(this->str, ref.str);

        return *this;
    }

    mstring& operator+=(const mstring& ref) {
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

    mstring operator+(const mstring& ref) {
        int len = (this->len + ref.len);

        char* sum = new char[len];
        strcpy(sum, this->str);
        strcat(sum, ref.str);

        mstring r(sum);
        delete[] sum;

        return r;
    }

    bool operator!=(const mstring& ref) {
        return (strcmp(this->str, ref.str) != 0) ? true : false;
    }

    bool operator==(const mstring& ref) {
        return (strcmp(this->str, ref.str) == 0) ? true : false;
    }

    bool operator>(const mstring& ref) {
        return strcmp(this->str, ref.str) > 0 ? true : false;
    }

    bool operator<(const mstring& ref) {
        return strcmp(ref.str, this->str) > 0 ? true : false;
    }

    friend ostream& operator<<(ostream& os, mstring& s);
    friend istream& operator>>(istream& is, mstring& s);
};

ostream& operator<<(ostream& os, mstring& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& is, mstring& s) {
    char x[100];
    is >> x;

    s = mstring(x);
    return is;
}

int main(void)
{
	mstring str1="I like ";
	mstring str2="string class";
	mstring str3=str1+str2;

	cout<<str1<<endl;
	cout<<str2<<endl;
	cout<<str3<<endl;

	str1+=str2;
	if(str1==str3) 	
		cout<<"동일 문자열!"<<endl;
	else
		cout<<"동일하지 않은 문자열!"<<endl;

	mstring str4;
	cout<<"문자열 입력: ";
	cin>>str4;
	cout<<"입력한 문자열: "<<str4<<endl;

    cout << (str1 > str2) << endl;
    cout << (str1 < str2) << endl;
	return 0;
}
