#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char data;
    int val;
    struct _Node *left;
    struct _Node *right;
} Node;

int ans;


Node *makeNode(char c) {
    Node *node = malloc(sizeof(Node));
    node->data = c;
    node->val = 0;
    node->left = node->right = NULL;
    return node;
}
Node *buildTree() {
    char c;
    Node *node;
    scanf(" %c", &c);
    if (c == '+' || c == '-' || c == '*') {
        node = makeNode(c);   
        node->left = buildTree();
        node->right = buildTree();    
    }
    else {
        node = makeNode(c);
    }
    return node;
}
void set_val(Node *root) {
    if (root != NULL) {
        set_val(root->left);
        set_val(root->right);
        if (root->data == '+') {
            root->val = root->left->val + root->right->val;
        }
        else if (root->data == '-') {
            root->val = root->left->val - root->right->val;
        }
        else if (root->data == '*') {
            root->val = root->left->val * root->right->val;
        }
        else {
            root->val = root->data - '0';
        }
    }
}
void printTree(Node *root) {
    if (root != NULL) {
        printf("%c", root->data);
        printTree(root->left);
        printTree(root->right);
    }
}
void spin(Node *root) {
    Node *new_root;
    //left
    while (root->right->data == '+' || root->right->data == '-' || root->right->data == '*') {
        new_root = root->right;
        if (root->data == '+') root->val = root->left->val + new_root->left->val;
        else if (root->data == '-') root->val = root->left->val - new_root->left->val;
        else if (root->data == '*') root->val = root->left->val * new_root->left->val;

        if (new_root->data == '+') new_root->val = root->val + new_root->right->val;
        else if (new_root->data == '-') new_root->val = root->val - new_root->right->val;
        else if (new_root->data == '*') new_root->val = root->val * new_root->right->val;

        if (new_root->val < ans) ans = new_root->val;

        root->right = new_root->left;
        new_root->left = root;
        root = new_root;
    }
    //right
    while (root->left->data == '+' || root->left->data == '-' || root->left->data == '*') {
        new_root = root->left;
        if (root->data == '+') root->val = root->right->val + new_root->right->val;
        else if (root->data == '-') root->val = new_root->right->val - root->right->val ;
        else if (root->data == '*') root->val = root->right->val * new_root->right->val;

        if (new_root->data == '+') new_root->val = root->val + new_root->left->val;
        else if (new_root->data == '-') new_root->val = new_root->left->val - root->val;
        else if (new_root->data == '*') new_root->val = root->val * new_root->left->val;

        if (new_root->val < ans) ans = new_root->val;

        root->left = new_root->right;
        new_root->right = root;
        root = new_root;
    }
}
int main() {
    int n;
    scanf("%d", &n);
    Node *root = buildTree();
    set_val(root);
    ans = root->val;
    //printTree(root);
    //printf("\n");
    //printf("%d", ans);
    spin(root);
    printf("%d\n", ans);
    return 0;
}