#include <iostream>

class Element {
    private:
        int base;
        int coeffc;
    
    public:
        Element() :
            base(0), coeffc(0) 
        { }
    
        Element(int b, int c) :
            base(b), coeffc(c)
        { }
    
        int getBase() { return this->base; }
        int getCoeffc() { return this->coeffc; }
    
        void printElement() {
            std::cout << std::fixed;
            std::cout.precision(1);
            std::cout << (float)this->base << " x^" << this->coeffc; 
        }
    };
    

class Node {
private:
    Node* link;
    Element data;

public:
    Node(Element rand) : data(rand), link(NULL)
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

    Element getData() {
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
        head(Node(Element())) { }

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

class Formular {
private:
    LinkedList formul;

public:
    Formular() {}

    int getDegree() { return this->formul.getSize(); }
    Element getEleemnt(int index) { 
        Node* d1 = this->formul.getIndex(index);
        if(d1 == NULL) {
            return Element(0, 0);
        } else {
            return d1->getData();
        } 
    }

    void insertElement(int b, int c) { 
        this->formul.insertItem(new Node(Element(b, c)), this->formul.getSize()); 
    }

    void printFormular() {
        std::cout << "(" << this->formul.getSize() << ") = ";
        for(int i = 0; i < this->formul.getSize(); i++) {
            Element e = this->formul.getIndex(i)->getData();
            e.printElement();

            if(i != this->formul.getSize() - 1) 
                std::cout << " + ";
        }
        std::cout << std::endl;
    }

    void sumFormular(Formular* f1) {
        for(int i = 0; i < f1->getDegree(); i++) {
            Element E1 = f1->getEleemnt(i);
            
            bool merged = false;
            for(int j = 0; j < this->getDegree(); j++) {
                Element E2 = this->getEleemnt(j);

                if(E1.getCoeffc() == E2.getCoeffc()) {
                    this->formul.replaceItem(new Node(Element(E1.getBase() + E2.getBase(), E2.getCoeffc())), j);
                    merged = true;
                    break;
                }
            }

            if(!merged) {
                //std::cout << E1.getCoeffc() << " " << this->getEleemnt(0).getCoeffc() << std::endl;
                if(E1.getCoeffc() > this->getEleemnt(0).getCoeffc()) {
                    this->formul.insertItem(new Node(E1), 0);
                    continue;
                }
            

                int pos = 0;
                for(int j = 0; j < this->getDegree(); j++) {
                    if(this->getEleemnt(j).getCoeffc() > E1.getCoeffc()) pos = j + 1;
                }


                this->formul.insertItem(new Node(E1), pos);
            }   
        }
    }
};


int main() {
    int eq1_l, eq2_l;
    Formular f1, f2;
    Formular sum;

    std::cin >> eq1_l;
    for(int i = 0; i < eq1_l; i++) {
        int b, c;
        std::cin >> b >> c;

        f1.insertElement(b, c);
    }

    std::cin >> eq2_l;
    for(int i = 0; i < eq2_l; i++) {
        int b, c;
        std::cin >> b >> c;

        f2.insertElement(b, c);
    }

    f1.printFormular();
    f2.printFormular();

    f1.sumFormular(&f2);

    f1.printFormular();
    
    return 0;
}