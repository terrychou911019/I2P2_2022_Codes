#include <iostream>
#include <queue>
#include <set>

using namespace std;

struct State {
    int px, py, dots_cnt, steps_cnt, bi_dots;
    State(): dots_cnt(0), steps_cnt(0), bi_dots(0) {}
    bool operator< (const State &r) const {
        if (px != r.px) return px < r.px;
        if (py != r.py) return py < r.py;
        if (bi_dots != r.bi_dots) return bi_dots < r.bi_dots;
        return false;
    }
};

int t, n, m, dotx[6], doty[6], dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1}, flag;
char board[300][300];
char c;

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m;
        cin.get();
        State start;
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < m ; j++) {
                board[i][j] = cin.get();
                if (board[i][j] == 'o') {
                    start.px = i;
                    start.py = j;
                }
                if (board[i][j] == '.') {
                    dotx[start.dots_cnt] = i;
                    doty[start.dots_cnt] = j;
                    start.dots_cnt++;
                }
            }
            cin.get();
        }
        queue<State> q;
        set<State> vis;
        q.push(start);
        vis.insert(start);
        flag = 0;
        while (!q.empty() && !flag) {
            State now = q.front();
            q.pop();
            for (int i = 0 ; i < 4 ; i++) {
                State next = now;
                next.px = now.px + dx[i];
                next.py = now.py + dy[i];
                if (0 <= next.px && next.px < n &&
                    0 <= next.py && next.py < m &&
                    board[next.px][next.py] != '#') {

                    for (int k = 0 ; k < start.dots_cnt ; k++) {
                        if (next.px == dotx[k] && next.py == doty[k] && 
                            (next.bi_dots & (1 << k)) == 0) {

                            next.dots_cnt--;
                            next.bi_dots ^= (1 << k);
                            break;
                        }
                    }
                    next.steps_cnt++;
                    if (next.dots_cnt == 0) {
                        flag = 1;
                        cout << next.steps_cnt << "\n";
                        break;
                    }
                    if (vis.find(next) == vis.end()) {
                        q.push(next);
                        vis.insert(next);
                    }
                }
            }
        }
    }
    return 0;
}