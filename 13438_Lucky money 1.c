#include <stdio.h>
#include <stdlib.h>

//no need to submit
typedef struct _Node{
    int number;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
//

//#include "function.h"
Node* createList(int n) {
    Node *r = malloc(sizeof(Node)), *tail;
    int num = 1;
    r->number = num;
    tail = r;
    n--;
    while (n--) {
        num++;
        Node *tmp = malloc(sizeof(Node));
        tmp->number = num;
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    }
    r->prev = tail;
    tail->next = r;
    return r;
}
void solve(int n, int m) {
    Node *tmp;
    for (tmp = head ; tmp->next != head ; tmp = tmp->next) {
        printf("%d ",  tmp->number);
    }
    printf("%d\n", tmp->number);
    int a, k;
    while (m--) {
        //delete node 'd'
        scanf("%d %d", &a, &k);
        if (a == n) {
            Node *tt;
            for (tt = head ; tt->next != head ; tt = tt->next) {
                printf("%d ",  tt->number);
            }
            printf("%d\n", tt->number);
            continue;
        }
        
        Node *d = head;
        int t = a, anum;
        t--;
        while (t--) {
            d = d->next;    
        }
        anum = d->number;
        d->prev->next = d->next;
        d->next->prev = d->prev;

        Node *ip = d;
        if (a + k > n) {
            k = n - a;
        }
        while (k--) {
            ip = ip->next;
        }
        if (a == 1) {
            head = head->next;
        }
        free(d);

        //insert node 'i'
        Node *i = malloc(sizeof(Node));
        i->number = anum;
        i->next = ip->next;
        i->prev = ip; 
        i->prev->next = i;
        i->next->prev = i;

        Node *ttmp;
        for (ttmp = head ; ttmp->next != head ; ttmp = ttmp->next) {
            printf("%d ",  ttmp->number);
        }
        printf("%d\n", ttmp->number);
        
    }
}
//
int main(){

    int n, k;

    while(scanf("%d%d", &n, &k)!=EOF){
        head = createList(n);
        solve(n, k);
    }

    return 0;
}

