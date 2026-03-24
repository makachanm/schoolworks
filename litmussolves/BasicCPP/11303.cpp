#include <iostream>
using namespace std;

class AbstractGate
{
protected:
    bool x, y;
public:
    AbstractGate(bool x, bool y) : x(x), y(y) { }
    virtual bool operation() = 0;
};

class ANDGate : public AbstractGate {
public:
    ANDGate(bool x, bool y) :
     AbstractGate(x, y)
    { }

    bool operation() {
        return (x && y);
    }
};

class ORGate : public AbstractGate {
public:
    ORGate(bool x, bool y) :
     AbstractGate(x, y)
    { }

    bool operation() {
        return (x || y);
    }
};

class XORGate : public AbstractGate {
public:
    XORGate(bool x, bool y) :
     AbstractGate(x, y)
    { }

    bool operation() {
        return (x ^ y);
    }
};

int main() {
    bool x, y;
    cin >> x >> y;           // 1 또는 0만 입력된다. 1은 true, 0은 false이다.

    ANDGate AND(x, y);
    ORGate OR(x, y);
    XORGate XOR(x, y);

    cout.setf(ios::boolalpha);    // bool 값을 "true", "false"로 출력하기 위하여 사용
    cout << AND.operation() << ' ' << OR.operation() << ' ' << XOR.operation() << endl;

    return 0;
}