#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;

int main() {
    vector<int> v[2];
    int x, y, q;
    cin >> x >> y >> q;
    for (int i = 0; i < x; i++) {
        int a;
        cin >> a;
        v[0].push_back(a);
    }
    for (int i = 0; i < y; i++) {
        int a;
        cin >> a;
        v[1].push_back(a);
    }
    sort(v[0].begin(), v[0].end());
    v[0].resize(unique(v[0].begin(), v[0].end()) - v[0].begin());
    sort(v[1].begin(), v[1].end());
    v[1].resize(unique(v[1].begin(), v[1].end()) - v[1].begin());
    int mn = v[0].size() > v[1].size();
    int mx = 1 - mn;
    while (q--) {
        int a;
        cin >> a;
        bool find = 0;
        for (int i = 0; i < v[mn].size(); i++) {
            int ii = v[mn][i];
            auto ind = lower_bound(v[mx].begin(), v[mx].end(), a - ii);
            if (ind != v[mx].end() && *ind == a - ii) {
                find = 1;
                break;
            }
        }
        cout << (find ? "Yes" : "No") << '\n';
    }
    return 0;
}
