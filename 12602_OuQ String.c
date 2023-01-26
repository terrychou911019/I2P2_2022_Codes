#include <stdio.h>
char s1[5];
long long int len[60];
char find(int k, long long int ch) {
    if (k == 1) return s1[ch];
    if (ch == 0) return 'O';
    else if (ch == len[k - 1] + 1) return 'u';
    else if (ch == len[k] - 1) return 'Q';
    else {
        if (0 < ch && ch < len[k - 1] + 1) return find(k - 1, ch - 1);
        else return find(k - 1, ch - 1 - len[k - 1] - 1);
    }
}
int main() {
    int k;
    long long int l, r;
    len[1] = 3;
    s1[0] = 'O';
    s1[1] = 'u';
    s1[2] = 'Q';
    for (int i = 2 ; i <= 50 ; i++) {
        len[i] = len[i - 1] * 2 + 3;
    }
    while (scanf("%d %lld %lld", &k, &l, &r) != EOF) {
        for (int i = l ; i <= r ; i++) {
            printf("%c", find(k, i));
        }
        printf("\n");
    }
    return 0;
}