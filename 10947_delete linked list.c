#include <stdio.h>
#include <stdlib.h>
//no need to submit
typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

//#include "function.h"
void deleteNode(Node ** nd, int data) {
    if (data == 1) {
        *nd = (*nd)->next;
        return;
    }
    Node *pre = NULL, *now = *nd;
    data--;
    while (now != NULL && data--) {
        pre = now;
        now = now->next;
    }
    if (now != NULL) {
        pre->next = now->next;
        free(now);
    }
}
Node* createList() {
    int n;
    Node *tmp, *head, *tail;
    scanf("%d", &n);
    if (n == -1) return NULL;
    head = (Node *)malloc(sizeof(Node));
    head->data = n;
    head->next = NULL;
    tail = head;
    while(scanf("%d", &n) == 1 && n != -1) {
        tmp = (Node *)malloc(sizeof(Node));
        tmp->data = n;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }
    return head;
}
//

void printList(Node *head){
    Node *temp;
    for(temp = head; temp!=NULL; temp=temp->next) {
        printf("%d ", temp->data);
    }
}

void freeList(Node *head){
    Node *temp;
    for(temp=head; temp!=NULL; temp=head){
        head = head->next;
        free(temp);
    }
}

int main()
{
    Node *head;
    int data;

    head = createList();

    while(1){
        scanf("%d", &data);
        if(data>-1){
            deleteNode(&head,data);
        }else break;

    }

    printList(head);
    freeList(head);
    return 0;
}