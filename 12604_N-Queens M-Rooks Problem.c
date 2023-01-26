#include <stdio.h>
char board[10][10];
int N, M, cnt, num_queen, num_rook;
int valid_queen(int row, int col) {
    for (int i = 1 ; i <= row ; i++) {
        if (col - i >= 0 && (board[row - i][col - i] == 'Q' || board[row - i][col - i] == 'R')) return 0;
        if (col + i < N + M && (board[row - i][col + i] == 'Q' || board[row - i][col + i] == 'R')) return 0;
        if (board[row - i][col] == 'Q' || board[row - i][col] == 'R') return 0;
    }
    return 1;
}
int valid_rook(int row, int col) {
    for (int i = 1 ; i <= row ; i++) {
        if (col - i >= 0 && (board[row - i][col - i] == 'Q')) return 0;
        if (col + i < N + M && (board[row - i][col + i] == 'Q')) return 0;
        if (board[row - i][col] == 'Q' || board[row - i][col] == 'R') return 0;
    }
    return 1;
}
void place(int row) {
    if (row == N + M) {
        //print();
        cnt++;
        return;
    }
    for (int col = 0 ; col < N + M ; col++) {
        if (num_queen < N && valid_queen(row, col)) {
            num_queen++;
            board[row][col] = 'Q';
            place(row + 1);
            num_queen--;
            board[row][col] = 'X';
        }
        if (num_rook < M && valid_rook(row, col)) {
            num_rook++;
            board[row][col] = 'R';
            place(row + 1);
            num_rook--;
            board[row][col] = 'X';
        }
    }
}
void print() {
    for (int i = 0 ; i < N + M ; i++) {
        for (int j = 0 ; j < N + M ; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    while (scanf("%d %d", &N, &M) != EOF) {
        cnt = 0;
        for (int i = 0 ; i < N + M ; i++) {
            for (int j = 0 ; j < N + M ; j++) {
                board[i][j] = 'X';
            }
        }
        place(0);
        
        printf("%d\n", cnt);
    }
    return 0;
}