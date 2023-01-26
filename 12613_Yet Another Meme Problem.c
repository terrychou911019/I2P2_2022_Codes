#include <stdio.h>
int t, a, b, ans, num;
int main() {
    scanf("%d", &t);
    while (t--) { 
        scanf("%d %d", &a, &b);
        for (ans = 0, num = 9 ; num <= b ; num = num * 10 + 9) ans++;
        printf("%lld\n", (long long int)a * ans);
    }
    return 0;
}