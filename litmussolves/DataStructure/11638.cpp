#include <iostream>
#include <string>

class Line {
private:
    std::string data;

public:
    Line() : data("") 
    { }

    Line(std::string s) :
        data(s)
    { }

    void print() { std::cout << this->data; }

    bool hasstring(std::string str) { 
        return this->data.find(str) != std::string::npos;
    }

    void replace(std::string replacement, std::string target) {
        size_t position = 0;

        while((position = this->data.find(target, position)) != std::string::npos) {
            this->data.replace(position, target.length(), replacement);
            position += replacement.length();
        }        
    }
};

class Node {
    private:
        Node* link;
        Line data;
    
    public:
        Node(Line rand) : data(rand), link(NULL)
        { }
    
        void setLink(Node* addr) {
            this->link = addr;
        }
    
        void setNext(Node* next) {
            if(next != NULL) {
                next->link = this->link;
                this->link = next;
            }
        }
    
        Node* getLink() {
            return this->link;
        }
    
        Line& getData() {
            return this->data;
        }
    
        Node* removeNext() {
            Node* nextnode = this->link;
            if(nextnode != NULL) {
                this->link = nextnode->getLink();
            }
    
            return nextnode;
        }
    
    };
    
    class LinkedList {
    private:
        Node head;
    
    public:
        LinkedList() : 
            head(Node(Line())) { }
    
        ~LinkedList() { 
            while(!this->isEmpty()) delete this->removeItem(0);
        }
    
        bool isEmpty() { return this->head.getLink() == NULL; }
        int getSize() { 
            int length = 0;
            for(Node* ptr = this->head.getLink(); ptr != NULL; ptr = ptr->getLink())
                length++;
    
            return length;
         }
    
        Node* getIndex(int index) {
           Node* head = &this->head;
           for(int i = -1; i < index; i++, head = head->getLink()) {
                if(head == NULL) break;
           }
    
           return head;
        }
    
        void insertItem(Node* ptr, int index) {
            Node* prev = this->getIndex(index - 1);
            if(ptr != NULL) {
                prev->setNext(ptr);
            }
        }
    
        Node* removeItem(int index) {
            Node* prev = this->getIndex(index - 1);
            return prev->removeNext();
        }
    
        void replaceItem(Node* ptr, int index) {
            Node* prev = this->getIndex(index - 1);
            if(prev != NULL) {
                delete prev->removeNext();
                prev->setNext(ptr);
            }
        }
    };

class Editor {
private:
    LinkedList lines;

public:
    Editor() { }

    void insertl() { 
        int row;
        std::cin >> row;
        std::cin >> std::ws;

        std::string input;
        std::getline(std::cin, input);

        this->lines.insertItem(new Node(input), row);
    }

    void deletel() { 
        int row;
        std::cin >> row;

        delete this->lines.removeItem(row);
    }

    void replacel() { 
        int row;
        std::cin >> row;
        std::cin >> std::ws;

        std::string input;
        std::getline(std::cin, input);

        this->lines.replaceItem(new Node(input), row);
    }

    void allprint() { 
        for(int i = 0; i < this->lines.getSize(); i++) {
            std::cout << i << ": ";
            this->lines.getIndex(i)->getData().print();
            std::cout << std::endl;
        }
        std::cout << "EOF" << std::endl;
    }

    void findreplacel() {
        std::cin >> std::ws;

        std::string find, replacement;
        std::getline(std::cin, find);
        std::getline(std::cin, replacement);

        for(int i = 0; i < this->lines.getSize(); i++) {
            if(this->lines.getIndex(i)->getData().hasstring(find)) {
                this->lines.getIndex(i)->getData().replace(replacement, find);
            }
        }
    }
};

int main() {
    bool running = true;
    char input;

    Editor E;

    while(running) {
        std::cin >> input;
        switch(input) {
        case 'i':
            E.insertl();
            break;

        case 'd':
            E.deletel();
            break;

        case 'r':
            E.replacel();
            break;
        
        case 'p':
            E.allprint();
            break;

        case 'f':
            E.findreplacel();
            break;

        case 'q':
            running=false;
            break;
        }
    }
    return 0;
}