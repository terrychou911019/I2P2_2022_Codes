#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char ch;
    struct _Node *prev;
    struct _Node *next;
} Node;


int main() {
    char c;
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        Node *head = malloc(sizeof(Node)), *tail, *cursor;

        head->next = NULL;
        head->prev = NULL;
        tail = head;
        cursor = head;
        while (n--) {
            scanf(" %c", &c);
            if (c == 'L') {
                if (cursor->prev != NULL)
                cursor = cursor->prev;
            }
            else if (c == 'R') {
                if (cursor->next != NULL)
                cursor = cursor->next;
            }
            else if (c == 'B') {
                Node *d = cursor;
                if (cursor == tail) {
                    cursor = cursor->prev;
                    cursor->next = NULL;
                    tail = cursor;
                    free(d);
                }
                else {
                    cursor = cursor->prev;
                    cursor->next = d->next;
                    d->next->prev = cursor;
                    free(d);
                }
                
            }
            else {
                Node *tmp = malloc(sizeof(Node));
                tmp->ch = c;
                
                if (cursor == tail) {
                    tmp->prev = cursor;
                    cursor->next = tmp;
                    cursor = tmp;
                    tail = cursor;
                    tail->next = NULL;
                }
                
                else {
                    tmp->next = cursor->next;
                    tmp->prev = cursor;
                    cursor->next->prev = tmp;
                    cursor->next = tmp;
                    cursor = tmp;
                }
            }
        }
        Node *n;
        for (n = head->next ; n->next != NULL ; n = n->next) {
            printf("%c", n->ch);
            free(n);
        }
        printf("%c\n", n->ch);
        free(n);
    }
        
    return 0;
}