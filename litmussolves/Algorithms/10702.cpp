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

    std::cout << insertions << std::endl;
}