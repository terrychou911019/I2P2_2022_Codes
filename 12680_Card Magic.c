#include<stdio.h>
#include<stdlib.h>
//no need to submit
typedef struct _Node{
    int size;
    int* data;
    struct _Node* next;
} Node;
//

//#include "function.h"
Node* ReadOneList() {
    Node *r = malloc(sizeof(Node));
    scanf("%d: ", &r->size);
    r->data = malloc(sizeof(int) * (r->size));
    for (int i = 0 ; i < r->size ; i++) {
        scanf("%d", &(r->data[i]));
    }
    r->next = NULL;
    return r;
}
void PrintList(Node* n) {
    n = n->next;
    while (n != NULL) {
        for (int i = 0 ; i < n->size ; i++) {
            printf("%d", n->data[i]);
            if (i != n->size - 1) printf(" ");
        }
        printf("\n");
        n = n->next;
    }
}
void Merge(Node* n, int x, int y) {
    x--, y--;
    Node *from = n->next, *to = n->next, *pre_from = n, *pre_to = n;
    while (x--) {
        from = from->next;
        pre_from = pre_from->next;
    }
    while (y--) {
        to = to->next;
        pre_to = pre_to->next;
    }
    
    Node *new = malloc(sizeof(Node));
    new->size = from->size + to->size;
    new->data = malloc(sizeof(int) * (new->size));
    for (int i = 0 ; i < to->size ; i++) {
        new->data[i] = to->data[i];
    }
    for (int i = 0 ; i < from->size ; i++) {
        new->data[to->size + i] = from->data[i];
    }
    if (pre_from == to) {
        pre_to->next = new;
        new->next = from->next;
    }
    else if (pre_to == from) {
        pre_from->next = new;
        new->next = to->next;
    }
    else {
        pre_to->next = new;
        new->next = to->next;
        pre_from->next = from->next;
    }
    free(from->data);
    free(to->data);
    free(from);
    free(to);
}
void Cut(Node* n, int x, int i) {
    x--;
    Node *c = n->next, *pre_c = n;
    while (x--) {
        c = c->next;
        pre_c = pre_c->next;
    }
    Node *new_1 = malloc(sizeof(Node)), *new_2 = malloc(sizeof(Node));
    new_1->size = i;
    new_2->size = c->size - i;
    new_1->data = malloc(sizeof(int) * new_1->size);
    new_2->data = malloc(sizeof(int) * new_2->size);
    for (int i = 0 ; i < new_1->size ; i++) {
        new_1->data[i] = c->data[i];
    }
    for (int i = 0 ; i < new_2->size ; i++) {
        new_2->data[i] = c->data[new_1->size + i];
    }
    new_1->next = new_2;
    pre_c->next = new_1;
    new_2->next = c->next;
    free(c->data);
    free(c);
}
//

int main(){
    Node* dummy_head;
    Node* tail;

    dummy_head = (Node*) malloc( sizeof(Node) );
    dummy_head->data = NULL;
    dummy_head->size = -1;

    tail = dummy_head;

    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=0; i<N; i++){
        tail->next = ReadOneList();
        tail = tail->next;   
    }
    char act[10];
    int x, y;
    for(int i=0; i<M; i++){
        scanf("%s %d %d", act, &x, &y);
        if( act[0] == 'M' ){
            Merge(dummy_head, x, y);
        }
        else{
            Cut(dummy_head, x, y);
        }
    }
    PrintList(dummy_head);
    return 0;
}
