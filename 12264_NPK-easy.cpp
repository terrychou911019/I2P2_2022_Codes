#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

list<int> line;
queue<int> country[3];

int main() {
    int n;
    cin >> n;
    while (n--) {
        string cmd;
        cin >> cmd;
        if (cmd == "ENQUEUE") {
            int x;
            cin >> x;
            int cn = x % 3;
            country[cn].push(x);
            auto it = find(line.begin(), line.end(), cn);
            if (it == line.end()) {
                line.push_back(cn);
            }
        }
        else if (cmd == "DEQUEUE") {
            int cn = line.front();
            cout << country[cn].front() << "\n";
            country[cn].pop();
            if (country[cn].empty()) line.pop_front();
        }
    }
    return 0;
}