#include <iostream>
#include <string>

template<typename T>
class StaticValues {
private:
    static T val;
public:
    void append(T val) {
        this->val += val;
    }

    void show() {
        std::cout << this->val << std::endl;
    }
};

template<typename T>
T StaticValues<T>::val = *(new T());

int main() {
    StaticValues<int> a;
    StaticValues<int> b;
    a.append(5);
    b.append(15);

    a.show();

    StaticValues<long> c;
    StaticValues<long> d;
    c.append(3);
    d.append(97);

    c.show();

    StaticValues<double> q;
    StaticValues<double> p;
    q.append(3);
    p.append(0.14);

    q.show();

    StaticValues<std::string> e;
    StaticValues<std::string> f;
    e.append("Hello ");
    f.append("World!!");

    e.show();

    return 0;
}