#include <iostream>
#include <stack>
#include <string>
#include <vector>

int priority(char c) {
    switch (c)
    {
    case '+': case '-':
        return 1;

    case '*': case '/':
        return 2;
    
    default:
        return 0;
    }
}

int main() {
    std::string input;
    std::vector<std::string> pre_equations;
    std::vector<std::string> post_equations;
    std::stack<std::string> operatior_stack;
    std::stack<double> operand_s;

    std::getline(std::cin, input);
    std::cin >> std::ws;

    std::size_t cur_pos = 0;
    std::size_t pos;
    while((pos = input.find(" ", cur_pos)) != std::string::npos) {
        pre_equations.push_back(input.substr(cur_pos, (pos - cur_pos)));
        cur_pos = pos + 1;
    }
    pre_equations.push_back(input.substr(cur_pos, (pos - cur_pos)));


    for(auto i = pre_equations.begin(); i != pre_equations.end(); i++) {
        std::string s = *i;

        if(s == "+" || s == "-" || s == "/" || s == "*") {
            while(!operatior_stack.empty()) {
                std::string s1 = operatior_stack.top();
                if(priority(s[0]) <=  priority(s1[0])) {
                    post_equations.push_back(s1);
                    operatior_stack.pop();
                } else {
                    break;
                }
            }
            operatior_stack.push(s);
        } else if (s == "("){
            operatior_stack.push(s);
        } else if (s == ")") {
            while(!operatior_stack.empty()) {
                std::string s1 = operatior_stack.top();
                if(s1 != "(") {
                    post_equations.push_back(s1);
                    operatior_stack.pop();
                } else {
                    operatior_stack.pop();
                    break;
                }
            }
        } else {
            post_equations.push_back(s);
        }
    }

    while(!operatior_stack.empty()){
        post_equations.push_back(operatior_stack.top());
        operatior_stack.pop();
    }

    for(auto i = post_equations.begin(); i != post_equations.end(); i++) {
        std::string s = (*i);
        
        
        if(s == "+" || s == "-" || s == "/" || s == "*") {
            double x2 = operand_s.top();
            operand_s.pop();
            double x1 = operand_s.top();
            operand_s.pop();

            double result;
            switch (s[0]) {
            case '+':
                result = (x1 + x2);
                break;
            case '-':
                result = (x1 - x2);
                break;
            case '*':
                result = (x1 * x2);
                break;
            case '/':
                if(x2 == 0) {
                    std::cout << "Error : zero division error" << std::endl;
                    exit(0);
                } else {
                    result = (x1 / x2);
                }
                break;
            default:
                break;
            }

            operand_s.push(result);
        } else {
            operand_s.push(std::stod(s));
        }
        
    }

    std::cout << std::fixed;
    std::cout.precision(2);
    std::cout << operand_s.top() << std::endl;
    return 0;
}