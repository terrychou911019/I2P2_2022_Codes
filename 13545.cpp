#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

list<int> line;
queue<int> friends[100005];
//vector<int> friends[100000];
map<int, int> x2f; // x to friends groups

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1 ; i <= m ; i++) {
        int k;
        cin >> k;
        for (int j = 0 ; j < k ; j++) {
            int x;
            cin >> x;
            x2f[x] = i;
        }
    }
    while (n--) {
        int f_cnt = m;
        string cmd;
        cin >> cmd;
        if (cmd == "ENQUEUE") {
            int x;
            cin >> x;
            auto it = x2f.find(x);
            if (it != x2f.end()) {
                int f = x2f[x];
                friends[f].push(x);
                auto it = find(line.begin(), line.end(), f);
                if (it == line.end()) {
                    line.push_back(f);
                }
            }
            else {
                f_cnt++;
                x2f[x] = f_cnt;
                int f = x2f[x];
                friends[f].push(x);
                line.push_back(f);
                
            }
        }
        else if (cmd == "DEQUEUE") {
            if (line.empty()) {
                cout << "The queue is empty\n";
            }
            else {
                int f = line.front();
                cout << friends[f].front() << "\n";
                friends[f].pop();
                if (friends[f].empty())
                    line.pop_front();
            }
        }
        else if (cmd == "LEAVE") {
            int x;
            cin >> x;
            int f = x2f[x];
            
        }
    }
    return 0;
}