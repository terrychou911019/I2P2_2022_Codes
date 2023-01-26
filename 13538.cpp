#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<int> sm, sw;
int smvis[100000005], swvis[100000005];

int main() {
    int m, w, e;
    cin >> m >> w >> e;
    //smvis.resize(10000005, 0);
    //swvis.resize(10000005, 0);
    for (int i = 0 ; i < m ; i++) {
        int num;
        cin >> num;
        
            sm.insert(num);
            //smvis[num] += 1;
        
    }
    for (int i = 0 ; i < w ; i++) {
        int num;
        cin >> num;
        
            sw.insert(num);
            //swvis[num] += 1;
        
    }
    
    if (sw.size() < sm.size()) {
        while (e--) {
            int target, flag = 0, cnt = 0;
            cin >> target;
            for (auto num : sw) {
                auto it = sm.find(target - num);
                if (it != sm.end()) {
                    //cnt += smvis[*it];
                    cnt++;
                }
            }
            
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
                    //cnt += swvis[*it];
                    cnt++;
                }
            }
            
            cout << cnt << "\n";
        }
    }
    return 0;
}