#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _Node {
    int num;
    int val;
    struct _Node *left;
    struct _Node *right;
} Node;

Node *number[3010];
char input[20220403], value_str[3010];
int pos, len, max_num;

Node *makeNode(int num) {
    Node *node = malloc(sizeof(Node));
    node->num = num;
    node->val = -1;
    node->left = node->right = NULL;
    return node;
}

Node *buildTree() {
    int num = 0;
    //Node *node = NULL;
    if (pos <= len - 1) {
        while (isdigit(input[pos]) && pos <= len - 1) {
            num = num * 10 + (input[pos] - '0');
            pos++;
        }

        if (num > max_num) max_num = num;

        number[num] = makeNode(num);

        if (input[pos] == '?') {
            pos++;
            number[num]->left = buildTree();
            number[num]->right = buildTree();
        }
        else if (input[pos] == ':') {
            pos++;
        }
    }
    return number[num];
}

void printTree(Node *root) {
    if (root != NULL) {
        printf("%d ", root->num);
        printTree(root->left);
        printTree(root->right);
    }
}

int find(Node *root) {
    if (root->left == NULL && root->right == NULL) return root->val;
    if (root->val) return find(root->left);
    else return find(root->right);
}

int main() {
    scanf("%s", input);
    len = strlen(input);
    pos = 0;
    Node *root = buildTree();
    //printTree(root);
    //printf("%d", max_num);
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", value_str);
        for (int i = 1 ; i <= max_num ; i++) {
            number[i]->val = value_str[i - 1] - '0';
        }
        //for (int i = 1 ; i <= max_num ; i++) printf("%d", number[i]->val);
        //printf("\n");
        printf("%d\n", find(root));
    }
    
    return 0;
}