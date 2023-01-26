#include <stdio.h>
char board[105][105], input[10010], str[15] = "ICPCASIASG";
int n, t, flag = 0;
void next(int cur_x, int cur_y, int target) {
    if (target == 10) {
        flag = 1;
        return;
    }
    for (int i = -2 ; i <= 2 ; i++) {
       for (int j = -2 ; j <= 2 ; j++) {
           if (i * i + j * j == 5 && 0 <= cur_x + i && cur_x + i < n && 0 <= cur_y + j && cur_y + j < n) {
               if (board[cur_x + i][cur_y + j] == str[target]) {
                   next(cur_x + i, cur_y + j, target + 1);
               }
           }
           
       }
    }
}
int main() {
    scanf("%d", &n);
    scanf("%s", input);
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            board[i][j] = input[t];
            t++;
        }
    }
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            if (board[i][j] == str[0] && !flag) {
                next(i, j, 1);
            }
        }
    }
    if (flag) printf("YES\n");
    else printf("NO\n");
    return 0;
}