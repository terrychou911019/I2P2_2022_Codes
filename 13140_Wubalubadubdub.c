#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int data;
    struct _node* left;
    struct _node* right;
} Node;

int arr[200010], idx, num, pos;

Node* makeNode(int key) {
    Node* n = malloc(sizeof(Node));
    n->data = key;
    n->left = n->right = NULL;
    return n;
}

Node* buildTree(int min, int max) {
    if (pos < 0) return NULL;
    int cur = arr[pos];
    if (cur < min || cur > max) return NULL;
    Node* r = makeNode(cur);
    pos--;
    r->right = buildTree(cur + 1, max);
    r->left = buildTree(min, cur - 1);
    return r;
}

void printPre(Node* r) {
    if (r != NULL) {
        if (r->data != arr[idx - 1]) printf(" ");
        printf("%d", r->data);
        printPre(r->left);
        printPre(r->right);
    }
}
int main() {
    while (scanf("%d", &num) != EOF) {
        arr[idx++] = num;
    }
    pos = idx - 1;
    Node* root = buildTree(-1000000000, 1000000000);
    printPre(root);
    printf("\n");
    return 0;
}