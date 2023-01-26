#include <iostream>
#include <set>

using namespace std;

set<int> sm, sw;
int smvis[20000010], swvis[20000010];

int main() {
    int m, w, e;
    cin >> m >> w >> e;
    for (int i = 0 ; i < m ; i++) {
        int num;
        cin >> num;
        sm.insert(num);
        smvis[num + 10000000]++;
    }
    for (int i = 0 ; i < w ; i++) {
        int num;
        cin >> num;
        sw.insert(num);
        swvis[num + 10000000]++;
    }
    if (sw.size() < sm.size()) {
        while (e--) {
        int target, flag = 0, cnt = 0;
        cin >> target;
        for (auto num : sw) {
            
            auto it = sm.find(target - num);
            if (it != sm.end()) {
                //flag = 1;
                //break;
                //cnt++;
                cnt = cnt + (swvis[num + 10000000] * smvis[target - num + 10000000]);
            }
            
        }
        //if (flag) cout << "Yes\n";
        //else cout << "No\n";
        cout << cnt << "\n";
        }
    }
    else {
    while (e--) {
        int target, flag = 0, cnt = 0;
        cin >> target;
        for (auto num : sm) {
            

            auto it = sw.find(target - num);
            if (it != sw.end()) {
                //flag = 1;
                //break;
                //cnt++;
                cnt = cnt + (smvis[num + 10000000] * swvis[target - num + 10000000]);
            }
            
        }
        //if (flag) cout << "Yes\n";
        //else cout << "No\n";
        cout << cnt << "\n";
    }
    }
    return 0;
}