#include <iostream>
#include <string>
#include <exception>
#include <typeinfo>
#include <vector>

int divc(int n1, int n2) {
    if(n2 == 0) {
        return -1;
    } else {
        return n1 / n2;
    }
}

int divexcp(int n1, int n2) {
    if(n2 == 0) {
        throw -1;
    } else {
        return n1 / n2;
    }
}

int stoi(std::string& num) {
    int ret = 0;
    for(int i = 0; i < num.length(); i++) {
        if(num[i] < '0' || num[i] > '9')
            throw num[i];
        ret = ret * 10 + (num[i] - '0');
    }

    return ret;
}

int wrapper03(std::string& s) {
    std::cout << "this is wrapper03" << std::endl;
    return stoi(s);
}

int wrapper02(std::string& s) {
    std::cout << "this is wrapper02" << std::endl;
    return wrapper03(s);
}


void wrapper01(std::string& s) {
    std::cout << "this is wrapper01" << std::endl;
    try {
        int x = wrapper02(s);
        std::cout << "result: " << x << std::endl; 
    } catch(char c) {
        std::cout << "(wrapper01) input is invalid - not a number: " << c << std::endl;
    }
}

void thrower() {
    std::cout << "this is thrower!" << std::endl;
    throw -1;
}

int main() {
    int num1, num2;
    std::cin >> num1 >> num2;

    int dvcr = divc(num1, num2);
    if(dvcr == -1) {
        std::cout <<  "error: divisor is zero!, " << dvcr << std::endl;
    } else {
        std::cout << "divc: " << dvcr << std::endl;
    }

    try {
        int dvexpr = divexcp(num1, num2);
        std::cout << "divexcp: " << dvexpr << std::endl;
    } catch(int ex) {
        std::cout <<  "error: divisor is zero!, " << ex << std::endl;
    }

    std::string i1, i2;
    std::cin >> i1 >> i2;

    try {
        int n1 = stoi(i1);
        int n2 = stoi(i2);
        std::cout << n1 << " + " << n2 << " = " << n1+n2 << std::endl;
    } catch(char c) {
        std::cout << "input is invalid - not a number: " << c << std::endl;
    }

    wrapper01(i2);
    
    try {
        thrower();
    } catch (char n) {
        std::cout << "aww! this is char!" << std::endl;
    } catch (int n) {

    }

    try {
        std::string s1;
        s1.resize(-256);
    } catch(std::exception& e) {
        std::cout << "error occur: " << typeid(e).name() << std::endl;
        std::cerr << "why: " << e.what() << std::endl;
    }

    int total = 0;
    try {
        while(1) {
            total += sizeof(int[1000000][1000000]);
            std::cout << "ALLOC: " << total  << " " << (total / (1024 * 1024)) << "MB" << std::endl;
            new int[1000000][1000000];
        }
    } catch(std::exception& e) {
        std::cout << "error occur: " << typeid(e).name() << std::endl;
        std::cerr << "why: " << e.what() << std::endl;
    }

    try {
        std::vector<int> a(5);
        a.at(-1);
    } catch(std::exception& e) {
        std::cout << "error occur: " << typeid(e).name() << std::endl;
        std::cerr << "why: " << e.what() << std::endl;
    }

    std::cout << "all excution clear" << std::endl;
    return 0;
}