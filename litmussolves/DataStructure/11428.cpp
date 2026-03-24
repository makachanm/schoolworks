#include <iostream>

template <typename T>
class BinaryTNode {
private:
    T data;
    BinaryTNode<T>* left;
    BinaryTNode<T>* right;

public:
    BinaryTNode() :
        data(NULL), left(NULL), right(NULL) 
    { }

    BinaryTNode(T data) : 
        data(data), left(NULL), right(NULL)
    { }

    BinaryTNode(T data, BinaryTNode<T>* lptr, BinaryTNode<T>* rptr) :
        data(data), left(lptr), right(rptr)
    { }

    void setData(T data) { this->data = data; }
    void setLeft(BinaryTNode<T>* ptr) { this->left = ptr; }
    void setRight(BinaryTNode<T>* ptr) { this->right = ptr; }
    T getData() { return this->data; }
    BinaryTNode<T>* getLeft() { return this->left; }
    BinaryTNode<T>* getRight() { return this->right; }

    bool isTermination() { return this->left == NULL && this->right == NULL; }
};

template <typename T>
class BinaryTree {
private:
    BinaryTNode<T>* root;

protected:
    int getSize(BinaryTNode<T>* node) { 
        if (node == NULL) return 0;
        else return getSize(node->getLeft()) + getSize(node->getRight());
    }

public:
    BinaryTree() : root(NULL) { }

    void setRoot(BinaryTNode<T>* ptr) { this->root = ptr; }
    BinaryTNode<T>* getRoot() { return this->root; }
    
    int getSize() { return this->isEmpty() ? 0 : this->getSize(this->root); }
    int getHeight(BinaryTNode<T>* ptr) { 
        if(ptr == NULL) return 0;
        else {
            int left = this->getHeight(ptr->getLeft());
            int right = this->getHeight(ptr->getRight());

            return (left >= right) ? left + 1 : right + 1;
        }
    }
    bool isEmpty() { return this->root == NULL; }

    bool isBalanced() {
        int rLeft = this->getHeight(this->root->getLeft());
        int rRight = this->getHeight(this->root->getRight());

        return ((rLeft - rRight) < 2);
    }

    //BinaryTNode<T>* searchByKey(T key) { }
    void inorderSearch() { inorderSearch(this->root); }
    void inorderSearch(BinaryTNode<T>* node) { 
        if(node == NULL) return;

        inorderSearch(node->getLeft());
        std::cout << " | "  << node->getData() << " | ";
        inorderSearch(node->getRight());
    }
};

template <typename T>
class BSearchTree : public BinaryTree<T> {
protected:
    BinaryTNode<T>* search(BinaryTNode<T>* ptr, T key) {         
        if(ptr->getData() == key) return ptr;
        else {
            if(ptr->getData() > key) return this->search(ptr->getLeft(), key);
            else return this->search(ptr->getRight(), key);
        }
    }

    void insert(BinaryTNode<T>* n, BinaryTNode<T>* ptr) {         
        if(ptr->getData() == n->getData()) return;

        if(ptr->getData() < n->getData()) {
            if(n->getLeft() == NULL) n->setLeft(ptr);
            else insert(n->getLeft(), ptr);
        } else {
            if(n->getRight() == NULL) n->setRight(ptr);
            else insert(n->getRight(), ptr);
        }
    }

    void remove(BinaryTNode<T>* parent, BinaryTNode<T>* target) { 
        if(target->isTermination()) {
            if(/*parent == NULL*/BinaryTree<T>::getRoot() == target) BinaryTree<T>::setRoot(NULL);
            else { 
            if(parent->getLeft() == target) parent->setLeft(NULL);
            else parent->setRight(NULL);
            }
        }


        else if(target->getLeft() == NULL || target->getRight() == NULL) {
            BinaryTNode<T>* children = (target->getLeft() != NULL) ? target->getLeft() : target->getRight();

            if(BinaryTree<T>::getRoot() == target) BinaryTree<T>::setRoot(children);       
            else {
            if(parent->getLeft() == target) parent->setLeft(children);
            else parent->setRight(children);
            }
        }


        else {
            BinaryTNode<T>* replacement = target->getRight();
            BinaryTNode<T>* replace_prt = target;
            
            while(replacement->getLeft() != NULL) {
                replace_prt = replacement;
                replacement = replacement->getLeft();
            }

            if(replace_prt->getLeft() == replacement) replace_prt->setLeft(replacement->getRight());
            else replace_prt->setRight(replacement->getRight());

            target->setData(replacement->getData());
            target = replacement;
        }

        delete target;
    }

public:
    BSearchTree() {}

    BinaryTNode<T>* search(T key) { 
        if(BinaryTree<T>::getRoot() == NULL) return NULL;
        
        BinaryTNode<T>* ptr = BinaryTree<T>::getRoot();
        if(ptr->getData() == key) return ptr;
        else {
            if(ptr->getData() > key) this->search(ptr->getLeft(), key);
            else this->search(ptr->getRight(), key);
        }

        return ptr;
    }

    void insert(BinaryTNode<T>* ptr) { 
        if(BinaryTree<T>::isEmpty()) {
            BinaryTree<T>::setRoot(ptr);
            return;
        }

        BinaryTNode<T>* root = BinaryTree<T>::getRoot();
       
        if(ptr->getData() == root->getData()) return;
        if(ptr->getData() < root->getData()) {
            if(root->getLeft() == NULL) root->setLeft(ptr);
            else insert(root->getLeft(), ptr);
        } else {
            if(root->getRight() == NULL) root->setRight(ptr);
            else insert(root->getRight(), ptr);
        }
        
    }

    void remove(T key) { 
            if(BinaryTree<T>::isEmpty()) {
                std::cout << "ERROR: NO TARGET TO REMOVE: EMPTY TREE" << std::endl;
                return;
            }

            BinaryTNode<T>* target = BinaryTree<T>::getRoot();
            BinaryTNode<T>* t_ptr = NULL;

            while(target != NULL && target->getData() != key) {
                t_ptr = target;
                target = (key < target->getData()) ? target->getLeft() : target->getRight();
            }

            if(target == NULL) {
                std::cout << "ERROR: NO TARGET TO REMOVE, KEY " << key << std::endl;
            } else remove(t_ptr, target);
        }
};

int main() {
    BSearchTree<int> tree;

    int totalnodesize = 0;
    char option;
    int x;
    std::cin >> totalnodesize;

    for(int i = 0; i < totalnodesize; i++) {
        std::cin >> option;
        std::cin >> x;

        switch (option)
        {
        case 'I':
            tree.insert(new BinaryTNode<int>(x));
            break;

        case 'D':
            tree.remove(x);
            break;
        
        default:
            break;
        }

    }

    if(tree.isBalanced()) std::cout << "Balanced" << std::endl;
    else std::cout << "Unbalanced" << std::endl;

    return 0;
}