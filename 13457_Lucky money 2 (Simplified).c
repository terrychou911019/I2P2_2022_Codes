#include <stdio.h>
#include <stdlib.h>
//no need to submit
typedef struct _Node{
    int age;
    struct _Node* prev;
    struct _Node* next;
}Node;

extern Node* head;
Node* createList(int N);
Node* solve(int N, int M);
//
//#include "function.h"
typedef struct _child {
    int age;
    int ip;
} Child;

Child *AS;
Node **NP;

Node* createList(int N) {
    AS = (Child *)malloc(sizeof(Child) * N);
    head = (Node *)malloc(sizeof(Node) * N);
    for (int i = 0 ; i < N ; i++) {
        scanf("%d", &AS[i].age);
        AS[i].ip = i;
        head[i].age = AS[i].age;
    }
    for (int i = 1 ; i < N ; i++) {
        head[i - 1].next = &(head[i]);
        head[i].prev = &(head[i - 1]);
    }
    head[N - 1].next = &(head[0]);
    head[0].prev = &(head[N - 1]);

    NP = (Node **)malloc(sizeof(Node *) * N);
    for (int i = 0 ; i < N ; i++) {
        NP[i] = &(head[AS[i].ip]);
    }
    return head;
}

void clockwise(int A, int K) {
    Node *cur = NP[A - 1]->next;
    NP[A - 1]->next->prev = NP[A - 1]->prev;
    NP[A - 1]->prev->next = NP[A - 1]->next;
    K--;
    while (K--) {
        cur = cur->next;
    }
    NP[A - 1]->next = cur->next;
    NP[A - 1]->prev = cur;
    cur->next->prev = NP[A - 1];
    cur->next = NP[A - 1];
}

Node* solve(int N, int M) {
    int A, K;
    while (M--) {
        scanf("%d %d", &A, &K);
        clockwise(A, K);
    }
    return NP[0];
}
//
Node* head;

int main(){

    int N, M;

    scanf("%d%d", &N, &M);
    head = createList(N);
    Node *p = solve(N, M);
    for(int i = 0; i < N; i++){
        printf("%d ", p -> age);
        p = p -> next;
    }
    printf("\n");
    return 0;
}

