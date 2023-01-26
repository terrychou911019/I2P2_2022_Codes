#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

int goalRow[] = {-1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
int goalCol[] = {-1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

class State {
public:
    int puzzle[4][4];
    int heuristic;
    int steps;
    int prevMove;
    int ex, ey;
    State(int p[4][4]) {
        for (int i = 0 ; i < 4 ; i++) {
            for ( int j = 0 ; j < 4 ; j++) {
                this->puzzle[i][j] = p[i][j];
            }
        }
        //this->heuristic = 0;
        this->steps = 0;
        this->prevMove = -1;
        this->ex = this->ey = -1;
        setHeuristic();
    }
    State(const State &rhs) {
        for (int i = 0 ; i < 4 ; i++) {
            for ( int j = 0 ; j < 4 ; j++) {
                this->puzzle[i][j] = rhs.puzzle[i][j];
            }
        }
        this->heuristic = rhs.heuristic;
        this->steps = rhs.steps;
        this->prevMove = rhs.prevMove;
        this->ex = rhs.ex;
        this->ey = rhs.ey;
        //setHeuristic();
    }
    void setHeuristic() {
        int h = 0;
        for (int i = 0 ; i < 4 ; i++) {
            for (int j = 0 ; j < 4 ; j++) {
                if (puzzle[i][j]) {
                    int goalX = goalRow[puzzle[i][j]];
                    int goalY = goalCol[puzzle[i][j]];
                    h += abs(goalX - i) + abs(goalY - j);
                    if (i == goalX) {
                        for (int k = j ; k < 4 ; k++) {
                            if (puzzle[i][k] > 0 && i == goalRow[puzzle[i][k]] && 
                                puzzle[i][j] > puzzle[i][k]) 
                                h += 2;
                        }
                    }
                    if (j == goalY) {
                        for (int k = i ; k < 4 ; k++) {
                            if (puzzle[k][j] > 0 && j == goalCol[puzzle[k][j]] && 
                                puzzle[i][j] > puzzle[k][j]) 
                                h += 2;
                        }
                    }
                }
            }
        }
        heuristic = h;
    }
    void update(int pd, int newX, int newY) {
        prevMove = pd;
        swap(puzzle[ex][ey], puzzle[newX][newY]);
        ex = newX;
        ey = newY;
        steps++;
        setHeuristic();
    }

    bool operator< (const State &rhs) const {
        return steps + heuristic > rhs.steps + rhs.heuristic; // ?
    }
};

int main() {
    int p[4][4];
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            cin >> p[i][j];
        }
    }
    State start(p);
    for (int i = 0 ; i < 4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            if (!p[i][j]) {
                start.ex = i;
                start.ey = j;
            }
        }
    }

    priority_queue<State> pq;
    pq.push(start);
    while (!pq.empty()) {
        State cur = pq.top();
        if (cur.heuristic == 0) {
            cout << cur.steps << "\n";
            break;
        }
        pq.pop();

        for (int i = 0 ; i < 4 ; i++) {
            int newX = cur.ex + dx[i];
            int newY = cur.ey + dy[i];
            if (newX < 0 || newX >= 4 ||
                newY < 0 || newY >= 4)
                continue;
            if (i == (cur.prevMove ^ 1))
                continue;
            State next = cur;
            next.update(i, newX, newY);
            pq.push(next);
        }
    }
    if (pq.empty()) cout << -1 << "\n";
    return 0;
}