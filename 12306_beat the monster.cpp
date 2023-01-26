#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct State {
    int lv, hp, mhp, dis;
    State(int lv, int hp, int mhp, int dis = 0): lv(lv), hp(hp), mhp(mhp), dis(dis) {}
};

bool vis[20][310][410]; // lv / hp / mhp

int main() {
    int l, hp, mhp, mdmg;
    int dmg[20], hl[20];
    cin >> l >> hp >> mhp >> mdmg;
    for (int i = 1 ; i <= l ; i++) {
        cin >> dmg[i] >> hl[i];
    }

    queue<State> Q;
    Q.push(State(1, hp, mhp));
    while (!Q.empty()) {
        State now = Q.front();
        if (!now.mhp) break;
        Q.pop();
        //level up
        if (now.lv < l && now.hp - mdmg > 0) {
            State next(now.lv + 1, now.hp - mdmg, now.mhp, now.dis + 1);
            if (!vis[next.lv][next.hp][next.mhp]) {
                vis[next.lv][next.hp][next.mhp] = true;
                Q.push(next);
            }
        }
        //attack
        if (now.hp - mdmg > 0 || now.mhp - dmg[now.lv] <= 0) {
            State next(now.lv, now.hp - mdmg, max(0, now.mhp - dmg[now.lv]), now.dis + 1);
            if (!vis[next.lv][next.hp][next.mhp]) {
                vis[next.lv][next.hp][next.mhp] = true;
                Q.push(next);
            }
        }
        //heal
        if (hp > mdmg && now.hp + hl[now.lv] - mdmg > 0) {
            State next(now.lv, min(hp, now.hp + hl[now.lv]) - mdmg, now.mhp, now.dis + 1);
            if (!vis[next.lv][next.hp][next.mhp]) {
                vis[next.lv][next.hp][next.mhp] = true;
                Q.push(next);
            }
        }
    }

    if (!Q.empty()) cout << Q.front().dis << "\n";
    else cout << -1 << "\n";
    return 0;
}