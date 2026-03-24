#include <iostream>
using namespace std;

class Converter
{
protected:
    double ratio;
    virtual double convert(double src) = 0;
    virtual string getSourceString() = 0;
    virtual string getDestString() = 0;

public:
    Converter(double ratio) : ratio(ratio) { }
    void run()  {
        double src;
        cout << getSourceString() << " to " << getDestString() << endl;
        cin >> src;
        cout << convert(src) << ' ' << getDestString() << endl;
    }
};

class WonToDollar : public Converter {
public:
    WonToDollar(double ratio) : 
        Converter(ratio)
    { }

protected:
    double convert(double src) {
        return src / ratio;
    }

    string getSourceString() {
        return "won";
    }

    string getDestString() {
        return "dollar";
    }
};

class KmToMile : public Converter {
public:
    KmToMile(double ratio) : 
        Converter(ratio)
    { }

protected:
    double convert(double src) {
        return src / ratio;
    }

    string getSourceString() {
        return "km";
    }

    string getDestString() {
        return "mile";
    }
};


int main() {
    double KRW2USD, km2mile;

    cin >> KRW2USD;
    WonToDollar w2d(KRW2USD);
    w2d.run();

    cin >> km2mile;
    KmToMile k2m(km2mile);
    k2m.run();
    return 0;
}