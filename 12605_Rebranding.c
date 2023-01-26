#include <stdio.h>
char name[200010], alpha[30];
int idx[30];
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", name);
    for (int i = 0 ; i < 26 ; i++) {
        alpha[i] = (char)('a' + i);
        idx[i] = i;
    }
    while (m--) {
        char x, y;
        char tc;
        int ti;
        scanf(" %c %c", &x, &y);
        tc = alpha[idx[x - 'a']];
        alpha[idx[x - 'a']] = alpha[idx[y - 'a']];
        alpha[idx[y - 'a']] = tc;
        ti = idx[x - 'a'];
        idx[x - 'a'] = idx[y - 'a'];
        idx[y - 'a'] = ti;       
    }
    for (int i = 0 ; i < n ; i++) {
        printf("%c", alpha[name[i] - 'a']);
    }
    printf("\n");
    return 0;
}