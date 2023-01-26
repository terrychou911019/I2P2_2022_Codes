#include <iostream>
#include <string.h>
//#include <iostream>
#include <math.h>
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};
//#include "function.h"
//using namespace std;
Array_BST::Array_BST() {
    for (int i = 0 ; i < 1025 ; i++) array[i] = 0;
}
void Array_BST::insert(const int &key) {
    int idx = 1, cur_height = 0;
    while (array[idx] != 0) {
        if (key == array[idx]) return;
        else {
            if (key < array[idx]) idx = 2 * idx;
            else idx = 2 * idx + 1;
            cur_height++;
        }
    }
    array[idx] = key;
    cur_height++;
    if (cur_height > Height) Height = cur_height;
}
bool Array_BST::search(const int &key) const {
    int idx = 1;
    while (array[idx] != 0) {
        if (key == array[idx]) return true;
        else if (key < array[idx]) idx = 2 * idx;
        else if (key > array[idx]) idx = 2 * idx + 1;
    }
    return false;
}
List_BST::List_BST() {
    root = nullptr;
}
void List_BST::insert(const int &key) {
    int cur_height = 0;
    if (root == nullptr) {
        root = createLeaf(key);
        cur_height++;
    }
    else {
        ListNode *p = root, *r = nullptr;
        while (p != nullptr) {
            if (key == p->key) return;
            else {
                r = p;
                if (key < p->key) p = p->left;
                else p = p->right;
                cur_height++;
            }
        }
        if (key < r->key) r->left = createLeaf(key);
        else r->right = createLeaf(key);
        cur_height++;
    }
    if (cur_height > Height) Height = cur_height;
}
bool List_BST::search(const int &key) const {
    ListNode *cur = root;
    while (cur != nullptr) {
        if (key == cur->key) return true;
        else if (key < cur->key) cur = cur->left;
        else if (key > cur->key) cur = cur->right;
    }
    return false;
}
ListNode* List_BST::createLeaf(int key) const {
    ListNode *n = new ListNode(key);
    n->left = n->right = nullptr;
    return n;
}
void List_BST::deleteTree(ListNode *root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}
//

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
