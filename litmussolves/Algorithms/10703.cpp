#include <iostream>
#include <vector>

long long insertions = 0;

class BinaryNode {
public:
    long long data;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(long long val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryNode* root;

    BinaryTree() : root(nullptr) {}
    
    void insert(long long data) {
        treeInsert(root, data);
    }

    void deleteitem(long long data, int deltype) {
        BinaryNode*& targetRef = searchNodeRef(root, data);
        
        if (targetRef != nullptr) {
            deleteNode(targetRef);
        }

        switch(deltype) {
            case 0: preorderPrint(this->root); break;
            case 1: inorderPrint(this->root); break;
            case 2: postorderPrint(this->root); break;
        }
    }

private:
    void treeInsert(BinaryNode*& node, long long data) {
        insertions++;
        
        if(node == nullptr) {
            node = new BinaryNode(data);
            return;
        }

        if(data < node->data) {
            treeInsert(node->left, data);
        } else if(data > node->data) {
            treeInsert(node->right, data); 
        }
    }

    BinaryNode*& searchNodeRef(BinaryNode*& node, long long data) {
        if (node == nullptr || node->data == data) {
            return node;
        }

        if (data < node->data) {
            return searchNodeRef(node->left, data);
        } else {
            return searchNodeRef(node->right, data);
        }
    }

    void preorderPrint(BinaryNode* node) {
        if(node == nullptr) return;

        std::cout << node->data << " ";
        preorderPrint(node->left);
        preorderPrint(node->right);
    }

    void inorderPrint(BinaryNode* node) {
        if(node == nullptr) return;

        inorderPrint(node->left);
        std::cout << node->data << " ";
        inorderPrint(node->right);
    }

    void postorderPrint(BinaryNode* node) {
        if(node == nullptr) return;

        postorderPrint(node->left);
        postorderPrint(node->right);
        std::cout << node->data << " ";
    }

    void deleteNode(BinaryNode*& targetRef) {
        BinaryNode* target = targetRef; // 삭제할 노드 자체
        
        if (target->left == nullptr) {
            targetRef = target->right; 
            delete target;        
        } else if (target->right == nullptr) {
            targetRef = target->left; 
            delete target;             
        } else {
            // 후계자 찾기: 오른쪽 서브트리에서 가장 작은 값 (가장 왼쪽 노드)
            BinaryNode* successorParent = target;
            BinaryNode* successor = target->right;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            target->data = successor->data;
            
            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else { 
                successorParent->right = successor->right;
            }

            delete successor; 
        }
    }
};

int main() {
    long long n;

    std::cin >> n;
    if (n <= 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    BinaryTree btree;
    for(long long i = 0; i < n; i++) {
        long long data;
        if (!(std::cin >> data)) break;
        btree.insert(data);
    }
    
    long long k;
    std::cin >> k;

    for(long long i = 0; i < k; i++) {
        long long data, deltype;
        std::cin >> deltype >> data;
        btree.deleteitem(data, deltype);
        std::cout << std::endl;
    }
}