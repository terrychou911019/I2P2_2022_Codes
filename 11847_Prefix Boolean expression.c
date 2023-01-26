#include <stdio.h>
char input[35];
int i, pos;
int f() {
    int a, b;
    if (input[pos] == '&') {
        pos++;
        a = f();
        pos++;
        b = f();
        a &= b;
    }
    else if (input[pos] == '|') {
        pos++;
        a = f();
        pos++;
        b = f();
        a |= b;
    }
    else {
        a = (i >> (3 - input[pos] + 'A')) & 1;
    }
    return a;
}
int main() {
    scanf("%s", input);
    for (i = 0 ; i < 16 ; i++) {
        pos = 0;
        printf("%d %d %d %d %d\n", (i >> 3) & 1, (i >> 2) & 1, (i >> 1) & 1, (i >> 0) & 1, f());
    }
    return 0;
}