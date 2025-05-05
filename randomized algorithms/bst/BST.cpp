#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

struct node{
    int key;
    double prio;
    struct node *left;
    struct node *right;
    //constructor
    node(int k) : key(k), prio(rand()), left(NULL), right(NULL) {}
};
class BST{
public:
    node *root;

    BST(){
        root = NULL;
    }

    //Insertion. root is a root of a tree, k is a key to be inserted.
    node* insert(int k){
        // insert_re is a recursive function that inserts the node into the root
        this->root = insert_re(this->root, k);
        return this->root;
    }

    //Deletion. 
    node* del(int k){
        this->root = delete_re(this->root, k);
        return this->root;
    }

    //In-order traversal. Traverses the tree and prints out the keys in order.
    //Prints the values of the tree nodes in ascending order.
    //Can use it to check the correctness of the tree (check if the printed values are sorted).
    void inorder() {
        inorder_re(this->root);
    }
    //Search. If such value doesn not exist returns 0, if exist returns the pointer's literal value.
    node* search(int k, int &count){
        return search_re(this->root, k, count);
    }
private:
    //Insertion recursive function. Root is the root of the tree, k is key (simplified so not to confuse with root->key),
    //goes left if equal, returns the root node of the tree that is being worked on.
    node* insert_re(node* root, int k) {
        if (root == NULL) {
            node* n = new (nothrow) node(k);
            if (!n) {
                cerr << "Memory allocation failed for node with key: " << k << endl;
                exit(1);
            }
            return n;
        }

        if (k <= root->key) {
            root->left = insert_re(root->left, k);
            if(root->left->prio > root->prio){
                root = right_rotate(root);
            }
        } 
        else {
            root->right = insert_re(root->right, k);
            if(root->right->prio > root->prio){
                root = left_rotate(root);
            }
        }
        return root;
    }
    //Deletion recursive function based on random prio. 
    node* delete_re(node* root, int k){
        if(root == NULL){
            return NULL;
        }

        if(root->key > k){
            root->left = delete_re(root->left, k);
        }
        else if(root->key < k){
            root->right = delete_re(root->right, k);
        }
        else if(root->left == NULL){
            root = root->right;
        }
        else if(root->right == NULL){
            root = root->left;
        }
        else if(root->right->prio > root->left->prio){
            root = left_rotate(root);
            root->left = delete_re(root->left, k);
        }
        else{
            root = right_rotate(root);
            root->right = delete_re(root->right, k);
        }
        
        return root;
    }
    //Recursive funtion to traverse tree.
    void inorder_re(node *root) {

        if (root == NULL) {
            return;
        }

        inorder_re(root->left);
        cout << root->key << " " << root->prio << "\n";
        inorder_re(root->right);
    }

    //recursive function to search from tree. count stores number of nodes visited
    node* search_re(node* root, int k, int& count) {
        if (root == NULL || root->key == k) {
            return root;
        }
        
        count++;  
        
        if (k < root->key) {
            return search_re(root->left, k, count);
        } else {
            return search_re(root->right, k, count);
        }
    }
    node* left_rotate(node* root){
        node* temp = root->right;
        root->right = temp->left;
        temp->left = root;
        return temp;
    }
    node* right_rotate(node* root){
        node* temp = root->left;
        root->left = temp->right;
        temp->right = root;
        return temp;
    }
};
// int main(){
//     srand(time(0));
//     BST bst;
//     int count = 0;
//     bst.insert(10);
//     bst.insert(15);
//     bst.insert(5);
//     bst.insert(2);
//     bst.inorder();
//     cout << bst.search(2, count); 
//     cout << "\n" << count << "\n";
//     return 0;
// }