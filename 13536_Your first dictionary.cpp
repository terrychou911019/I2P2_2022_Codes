#include <iostream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

int main() {
    set<string> s;
    string str;
    while (cin >> str) {
        for (int i = 0 ; i < str.size() ; i++) {
            str[i] = tolower(str[i]);
        }
        if (s.find(str) == s.end()) {
            s.insert(str);
        }
    }
    for (auto it = s.begin() ; it != s.end() ; it++) {
        cout << *it << "\n";
    }
    return 0;
}