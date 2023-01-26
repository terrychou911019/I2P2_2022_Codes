#include <stdio.h>
#include <stdlib.h>
//no need to submit
typedef struct _Node{
    int number, age;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
Node* createList(int n);
Node* solve(int n, int m);
//

//#include "function.h"
typedef struct child{
    int age;
    int ip;//initial position
} Child;

//age sequence
Child *AS;
//pointers to each node directly
Node **NP;

int compare_child (const void *a, const void *b)
{
    const Child *ia = (const Child *) a;
    const Child *ib = (const Child *) b;
    return (*ia).age-(*ib).age;
}

Node* createList(int n)
{
    int i;

    AS = (Child *)malloc(sizeof(Child)*(n));
    head = (Node *)malloc(sizeof(Node)*(n));

    for(i=0;i<n;i++)
    {
        scanf("%d",&(AS[i].age));
        AS[i].ip=i;
        head[i].age=AS[i].age;
    }

    //create the doubly circular linked list
    for(i=1;i<n;i++)
    {
        head[i-1].next=&(head[i]);
        head[i].prev=&(head[i-1]);
    }
    head[n-1].next=&(head[0]);
    head[0].prev=&(head[n-1]);

    //sort
    qsort(AS, n, sizeof(Child), compare_child);

    //Let NP[i] point to the node of the ith youngest child
    NP = (Node**)malloc(sizeof(Node*)*(n));
    for(i=0;i<n;i++) NP[i]=&head[AS[i].ip];

    return head;
}

void clockwise(int A, int K)
{
    int i;
    Node* cur = NP[A-1]->next;
    NP[A-1]->prev->next = NP[A-1]->next;
    NP[A-1]->next->prev = NP[A-1]->prev;

    for(i=1;i<K;i++)
    {
        cur = cur->next;
    }
    NP[A-1]->prev = cur;
    NP[A-1]->next = cur->next;
    cur->next->prev = NP[A-1];
    cur->next = NP[A-1];
}

void counterclockwise(int A, int K)
{
    int i;
    Node* cur = NP[A-1]->prev;
    NP[A-1]->prev->next = NP[A-1]->next;
    NP[A-1]->next->prev = NP[A-1]->prev;

    for(i=1;i<K;i++)
    {
        cur = cur->prev;
    }
    NP[A-1]->next = cur;
    NP[A-1]->prev = cur->prev;
    cur->prev->next = NP[A-1];
    cur->prev = NP[A-1];
}

Node* solve(int n, int m)
{
    int i;
    int A,K;
    char Dir[2];

    for(i=0;i<m;i++)
    {
        scanf("%d%d%s",&A,&K,Dir);
        if(n<=2);//do nothing
        else if(Dir[0]=='R')
            clockwise(A,K);
        else
            counterclockwise(A,K);
    }

    return NP[0];
}

//



int main(){

    int n, k;

    scanf("%d%d", &n, &k);
    head = createList(n);
    Node *p = solve(n, k);
    for(int i = 0; i < n; i ++){
        printf("%d ", p -> age);
        p = p -> next;
    }
    printf("\n");
    return 0;
}

