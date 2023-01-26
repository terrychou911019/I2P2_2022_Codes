#include <stdio.h>
#include <math.h>
int n, x[200010];
int main() {
    scanf("%d", &n);
    for (int i = 0 ; i <= n ; i++) scanf("%d", &x[i]);
    int rb = x[0], lb = x[0];
    for (int i = 1 ; i <= n ; i++) {
        if (x[i] > rb) rb = x[i];
        if (x[i] < lb) lb = x[i];
    }
    printf("%d\n", 2 * abs(rb - lb));
    return 0;
}