#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int data;
    int visit;
    struct _Node *left;
    struct _Node *right;
    struct _Node *parent;
} Node;

char ans[3010];
int a, b, pos;
Node *node_arr[3010];

Node *makeNode(int k) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = k;
    tmp->right = tmp->left = tmp->parent = NULL;
    return tmp;
}

void route(int from, int to) {

    if (from == to) {
        int now = b, prev = 0;
        while (now != a) {
            prev = now;
            now = node_arr[now]->visit;
            if (node_arr[prev] == node_arr[now]->parent) ans[pos++] = 'P';
            else if (node_arr[prev] == node_arr[now]->left) ans[pos++] = 'L';
            else if (node_arr[prev] == node_arr[now]->right) ans[pos++] = 'R';
        }
    }
    else {
        if (node_arr[from]->parent != NULL && node_arr[from]->parent->visit == 0) {
            node_arr[from]->parent->visit = from;
            route(node_arr[from]->parent->data, to);
        }
        if (node_arr[from]->left != NULL && node_arr[from]->left->visit == 0) {
            node_arr[from]->left->visit = from;
            route(node_arr[from]->left->data, to);
        }
        if (node_arr[from]->right != NULL && node_arr[from]->right->visit == 0) {
            node_arr[from]->right->visit = from;
            route(node_arr[from]->right->data, to);
        }
    }
}
int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++) node_arr[i] = makeNode(i);
    for (int i = 1 ; i <= n ; i++){
        int l, r;
        scanf("%d %d", &l, &r);
        
        if (l == 0) node_arr[i]->left = NULL;
        else {
            node_arr[i]->left = node_arr[l];
            node_arr[l]->parent = node_arr[i];
        }
        if (r == 0) node_arr[i]->right = NULL;
        else {
            node_arr[i]->right = node_arr[r];
            node_arr[r]->parent = node_arr[i];
        }
    }
    scanf("%d", &q);
    while (q--) {
        pos = 0;
        scanf("%d %d", &a, &b);
        for (int i = 1 ; i <= n ; i++) node_arr[i]->visit = 0, ans[i] = 0;
        route(a, b);
        for (int i = pos - 1 ; i >= 0 ; i++) {
            printf("%c", ans[i]);
        }
        printf("\n");
        
    }
    return 0;
}