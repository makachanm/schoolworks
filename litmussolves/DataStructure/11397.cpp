#include <iostream>

template <typename T>
class Stack {
private:
    T stack[20];
    int head;

public:
    Stack() :
      head(-1)
    { }

    bool empty() {
        return (this->head < 0);
    }

    T top() {
        return this->stack[this->head];
    }

    void push(T i) {
        this->stack[++this->head] = i;
    }

    T pop() {
        return this->stack[this->head--];
    }
};

template <typename T>
class Queue {
private:
    T queue[20];
    int head, tail, maxlen;

public:
    Queue() :
        head(0), tail(0),
        maxlen(20)
    { 
        for(int  i = 0; i < this->maxlen; i++)
            this->queue[i] = 0;
    }

    bool empty() {
        return (this->head == this->tail);
    }

    T front() {
        return this->queue[this->head + 1];
    }

    void push(T i) {
        this->tail++;
        this->queue[this->tail] = i;
    }

    T pop() {
        this->head++;
        return this->queue[this->head];
    }
    
};

int main() {
    int len;
    int x, k, q;
    char s_type;
    
    Queue<int> input;
    Stack<int> pr;
    Queue<int> output;

    std::cin >> len;
    std::cin >> s_type;

    for(int i = 0; i < len; i++) {
        std::cin >> x;
        input.push(x);
    }

    switch (s_type) {
    case 'a':
        //가장 큰 수가 스택의 가장 밑에 깔려야 함 (가장 먼저 들어가야 함)
        k = 1;
        while(!input.empty() || !pr.empty()) {
            std::cout << input.front();// << std::endl;
            if(k == input.front()) {
                output.push(input.pop());
                k++;
            } else if (k == pr.top()) {
                output.push(pr.pop());
                k++;
            } else {
                pr.push(input.pop());
                //k++;
            }
            std::cout<<std::endl;
        }
        
        q = output.front();

        while(!output.empty()) {
            std::cout << q << " ";
            if(output.front() < q) {
                std::cout << "No" << std::endl;
                return 0;
            }

            q = output.pop();
        }

        std::cout << "Yes" << std::endl;
        break;

    case 'd':
        k = len;
        while(!input.empty() || !pr.empty()) {
            std::cout << input.front();// << std::endl;
            /*
            if(k == input.front()) {
                output.push(input.pop());
                k--;
            } else if (k == pr.top()) {
                output.push(pr.pop());
                k--;
            } else {
                pr.push(input.pop());
                //k++;
            }
            */
            input.pop();
        }
    
        q = output.front();

        while(!output.empty()) {
            std::cout << q << " ";
            if(output.front() < q) {
                std::cout << "No" << std::endl;
                return 0;
            }

            q = output.pop();
        }
        std::cout << "Yes" << std::endl;
        break;                
    
    default:
        break;
    }

    
}