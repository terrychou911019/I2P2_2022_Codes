#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} BTNode;


BTNode *root, *now, *pre_now;

BTNode *find(BTNode *n, int target) {
    
    if (n == NULL) return NULL;

    if (n->data == target) {
        return n;
    }
    else {
        BTNode *ans = NULL;
        if(ans == NULL) ans = find(n->left, target);
        if(ans == NULL) ans = find(n->right, target);
        
        return ans;
    }
}
int main() {
    int n, q;
    root = malloc(sizeof(BTNode));
    root->data = 1;
    root->left = root->right = root->parent = NULL;
    /*now = root;
    pre_now = now;
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        if (l == 0 || r == 0) {
            continue;
        }
        else {
            if (now->data != 1) {
                if (pre_now->left->data == i) now = pre_now->left;
                else if (pre_now->right->data == i) now = pre_now->right;
            }
            now->left = malloc(sizeof(BTNode));
            now->left->data = l;
            now->left->left = now->left->right = NULL;
            now->left->parent = now;
            now->right = malloc(sizeof(BTNode));
            now->right->data = r;
            now->right->left = now->right->right = NULL;
            now->right->parent = now;
            pre_now = now;
        }
    }*/
    root->data = 1;
    root->left = malloc(sizeof(BTNode));
    root->left->data = 2;
    root->right = malloc(sizeof(BTNode));
    root->right->data = 3;
    root->left->left = malloc(sizeof(BTNode));
    root->left->left->data = 4;
    root->left->right = malloc(sizeof(BTNode));
    root->left->right->data = 5;
    root->left->left->left = root->left->left->right = NULL;
    root->left->right->left = root->left->right->right = NULL;
    root->right->left = root->right->right = NULL;
    scanf("%d", &q);
    while (q--) {
        int a, b;
        scanf("%d", &a);
        //printf("%d %d %d\n", root->data, root->left->data, root->left->right->data);
        BTNode *k = find(root, a);
        printf("%d\n", k->data);
    }
    return 0;
}