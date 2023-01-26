#include <stdio.h>
#include <stdlib.h>

int child[200010][2], parent[200010], idx[200010], ans, root; 

void solve(int l, int r, int root) {
    if (ans == 0) return;
    if (child[root][0] && child[root][1]) {
        if (l <= idx[child[root][0]] && idx[child[root][0]] < idx[root] && idx[root] < idx[child[root][1]] && idx[child[root][1]] <= r) {
            solve(l, idx[root] - 1, child[root][0]);
            solve(idx[root] + 1, r, child[root][1]);
        }
        else if (l <= idx[child[root][1]] && idx[child[root][1]] < idx[root] && idx[root] < idx[child[root][0]] && idx[child[root][0]] <= r) {
            solve(l, idx[root] - 1, child[root][1]);
            solve(idx[root] + 1, r, child[root][0]);
        }
        else ans = 0;
    }
    else if (child[root][0]) {
        if (l <= idx[child[root][0]] && idx[child[root][0]] < idx[root]) {
            solve(l, idx[root] - 1, child[root][0]);
        }
        else if (idx[root] < idx[child[root][0]] && idx[child[root][0]] <= r) {
            solve(idx[root] + 1, r, child[root][0]);
        }
        else ans = 0;
    }
    else if (child[root][1]) {
        if (l <= idx[child[root][1]] && idx[child[root][1]] < idx[root]) {
            solve(l, idx[root] - 1, child[root][1]);
        }
        else if (idx[root] < idx[child[root][1]] && idx[child[root][1]] <= r) {
            solve(idx[root] + 1, r, child[root][1]);
        }
        else ans = 0;

    }
    else return;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int c1, c2;
        ans = 1;
        root = 0;
        for (int i = 0 ; i <= n ; i++) {
            child[i][0] = child[i][1] = parent[i] = idx[i] = 0;
        }
        for (int i = 1 ; i <= n ; i++) {
            scanf("%d %d", &c1, &c2);
            child[i][0] = c1;
            child[i][1] = c2;
            parent[c1] = parent[c2] = i;
        }
        for (int i = 1 ; i <= n ; i++) {
            int num;
            scanf("%d", &num);
            idx[num] = i;
        }
        for (int i = 1 ; i <= n ; i++) {
            if (parent[i] == 0) {
                root = i;
                break;
            }
        }
        solve(1, n, root);
        if (ans == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
