#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Seg {
    int left, right;
    Seg(int l, int r): left(l), right(r) {} 
};

struct cmp {
    bool operator() (const Seg &lhs, const Seg &rhs) const {
        int nor_l = (lhs.right - lhs.left) / 2;
        int nor_r = (rhs.right - rhs.left) / 2;
        if (nor_l != nor_r) 
            return nor_l > nor_r;
        else 
            return lhs.left < rhs.left;
    }
};

int main() {
    int n, m, s, d;
    vector<int> id2pos;
    set<int> pos;
    set<Seg, cmp> ss;
    cin >> n >> m >> s;
    d = n + 1;
    id2pos.resize(m + 1, -1);
    pos.insert(0);
    pos.insert(n + 1);
    ss.insert(Seg(0, n + 1));

    for (int i = 0 ; i < 2 * m ; i++) {
        char cmd;
        int x;
        cin >> cmd >> x;
        if (cmd == 'i') {
            auto it = ss.begin();
            int left = it->left, right = it->right;
            int mid = (left + right) / 2;
            if (left != 0) 
                d = min(d, mid - left);
            if (right != n + 1) 
                d = min(d, right - mid);
            ss.erase(it);
            ss.insert(Seg(left, mid));
            ss.insert(Seg(mid, right));
            pos.insert(mid);
            id2pos[x] = mid;
        }
        else if (cmd == 'o') {
            int mid = id2pos[x];
            auto it = pos.find(mid);
            auto l_it = it, r_it = it;
            int left = *(--l_it), right = *(++r_it);
            ss.erase(Seg(left, mid));
            ss.erase(Seg(mid, right));
            ss.insert(Seg(left, right));
            pos.erase(mid);
            id2pos[x] = -1;
        }
    }

    if (d >= s) 
        cout << "YES\n";
    else 
        cout << "NO\n";
    if (d != n + 1) 
        cout << d << "\n";
    else 
        cout << "INF\n";
    return 0;
}