#include <stdio.h>
#include <stdlib.h>

typedef struct Node_ {
    char *c;
    struct Node_ *next;
} Node;

Node *head[100005], *tail[100005], *tmp;
int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++) {
        int size;
        scanf("%d", &size);
        if (size == 0) {
            head[i] = NULL;
            tail[i] = NULL;
        }
        else {
            head[i] = malloc(sizeof(Node));
            tail[i] = head[i];
            head[i]->c = malloc(sizeof(char) * (size + 1));
            scanf("%s", head[i]->c);
            head[i]->next = NULL;
        }
    }
    scanf("%d", &m);
    while (m--) {
        int type, a, b;
        scanf("%d %d %d", &type, &a, &b);
        if (type == 1 && tail[a]) {
            if (head[b] == NULL) {
                tmp = head[a];
                head[a] = head[b];
                head[b] = tmp;
                tmp = tail[a];
                tail[a] = tail[b];
                tail[b] = tmp;
            }
            else{
                tail[a]->next = head[b];
                head[b] = head[a];
                head[a] = NULL;
                tail[a] = NULL;
            }
        }
        if (type == 2 && tail[a]) {
            if (head[b] == NULL) {
                tmp = head[a];
                head[a] = head[b];
                head[b] = tmp;
                tmp = tail[a];
                tail[a] = tail[b];
                tail[b] = tmp;
            }
            else {
                tail[b]->next = head[a];
                tail[b] = tail[a];
                head[a] = NULL;
                tail[a] = NULL;
            }
        }
        if (type == 3) {
            tmp = head[a];
            head[a] = head[b];
            head[b] = tmp;
            tmp = tail[a];
            tail[a] = tail[b];
            tail[b] = tmp;
        }
    }
    for (int i = 1 ; i <= n ; i++) {
        while (head[i] != NULL) {
            printf("%s", head[i]->c);
            head[i] = head[i]->next;
        }
        printf("\n");
    }
    return 0;
}