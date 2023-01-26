#include <stdio.h>
#include <stdlib.h>

typedef struct _BTNode {
    int data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

typedef struct _LLNode {
    BTNode *root;
    struct _LLNode *next;
} LLNode;

LLNode *getTree(int l, int r) {
    LLNode *head = NULL, *tail = NULL;
    if (l > r) {
        head = malloc(sizeof(LLNode));
        head->root = NULL;
        head->next = NULL;
        return head;
    }
    for (int i = l ; i <= r ; i++) {
        LLNode *ltree = getTree(l, i - 1);
        LLNode *rtree = getTree(i + 1, r);
        while (ltree != NULL) {
            LLNode *r_itr = rtree;
            while (r_itr != NULL) {
                BTNode *node = malloc(sizeof(BTNode));
                node->data = i;
                node->left = ltree->root;
                node->right = r_itr->root;

                LLNode *ln = malloc(sizeof(LLNode));
                ln->root = node;
                ln->next = NULL;
                if (head == NULL) {
                    head = tail = ln;
                }
                else {
                    tail->next = ln;
                    tail = ln;
                }
                r_itr = r_itr->next;
            }
            ltree = ltree->next;
        }
    }
    return head;
}

void printPre(BTNode *root) {
    if (root != NULL) {
        printf(" %d", root->data);
        printPre(root->left);
        printPre(root->right);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    LLNode *LLHead = getTree(1, n);
    while (LLHead != NULL) {
        BTNode *root = LLHead->root;
        printf("%d", root->data);
        printPre(root->left);
        printPre(root->right);
        printf("\n");
        LLHead = LLHead->next;
    }
    return 0;
}