#include <iostream>
#include <set>

using namespace std;

set<int> sm, sw;

int main() {
    int m, w, e;
    cin >> m >> w >> e;
    for (int i = 0 ; i < m ; i++) {
        int num;
        cin >> num;
        sm.insert(num);
    }
    for (int i = 0 ; i < w ; i++) {
        int num;
        cin >> num;
        sw.insert(num);
    }
    if (sw.size() < sm.size()) {
        sm.swap(sw);
    }
    while (e--) {
        int target, flag = 0;
        cin >> target;
        for (auto num : sm) {
            auto it = sw.find(target - num);
            if (it != sw.end()) {
                flag = 1;
                break;
            }
        }
        if (flag) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}