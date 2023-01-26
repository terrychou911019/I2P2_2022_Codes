#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

void readVector(vector<int> &v) {
    int num;
    while (cin >> num && num != 0) {
        v.push_back(num);
    }
}
int getValue(vector<int> v) {
    int val = 0;
    for (int i = 0 ; i < v.size() ; i++) {
        val += v[i] * (v.size() - i);
    }
    return val;
}
void printVector(vector<int> &v) {
    for (auto it : v) {
        cout << it << " ";
    }
    cout << "\n";
}

struct cmp {
    bool operator() (const vector<int> &lhs, const vector<int> &rhs) {
        return getValue(lhs) < getValue(rhs);
    }
};

set<vector<int>, cmp> s;

int main() {
    string cmd;
    while (cin >> cmd) {
        if (cmd == "insert") {
            vector<int> new_vec;
            readVector(new_vec);
            //auto search = s.find(new_vec);
            for (auto it : s) {
                if (getValue(new_vec) == getValue(it)) {
                    cout << "exist\n";
                    reverse(new_vec.begin(), new_vec.end());
                    break;
                }
            }
            s.insert(new_vec);
        }
        else if (cmd == "range_out") {
            vector<int> v1, v2;
            readVector(v1);
            readVector(v2);
            int from = getValue(v1), to = getValue(v2);
            for (auto it : s) {
                if (getValue(it) >= from && getValue(it) <= to) {
                    printVector(it);
                }
            }
        }
        else if (cmd == "output") {
            for (auto it : s) {
                printVector(it);
            }
        }
    }

    return 0;
}