#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
    char data;
    struct _node *left;
    struct _node *right;
} BTNode;

char input[260];
int pos;

void output(BTNode *r) {
    if (r->left != NULL) output(r->left);
    printf("%c", r->data);
    if (r->right != NULL) {
        if (r->right->data == '&' || r->right->data == '|') {
            printf("(");
            output(r->right);
            printf(")");
        }
        else {
            output(r->right);
        }
    }
}
void freetree(BTNode *root) {
    if (root != NULL) {
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}
BTNode *makenode(char c);
BTNode *expr();
BTNode *factor();

int main() {
    scanf("%s", input);
    pos = strlen(input) - 1;
    BTNode *root = expr();
    output(root);
    freetree(root);
    return 0;
}
BTNode *makenode(char c) {
    BTNode *node = malloc(sizeof(BTNode));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}
BTNode *expr() {
    char c;
    BTNode *node = NULL, *right = NULL;
    if (pos >= 0) {
        right = factor();
        if (pos > 0) {
            c = input[pos];
            if (c == '&' || c == '|') {
                node = makenode(c);
                node->right = right;
                pos--;
                node->left = expr();
            }
            else node = right;
        }
        else node = right;
    }
    return node;
}
BTNode *factor() {
    char c;
    BTNode *node = NULL;
    if (pos >= 0) {
        c = input[pos--];
        if (c >= 'A' && c <= 'D') {
            node = makenode(c);
        }
        else if (c == ')') {
            node = expr();
            if (input[pos--] != '(') {
                printf("error\n");
                freetree(node);
            }
        }
    }
    return node;
}
