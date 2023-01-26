#include <iostream> //_Parentheses Matching
#include <string>
#include <map>
#include <stack>

using namespace std;

map<char, char> parens = {
    {'{', '}'},
    {'[', ']'},
    {'(', ')'},
    {'<', '>'}
};

int main() {
    int n;
    string s;
    cin >> n;
    getline(cin, s);
    for (int i = 1 ; i <= n ; i++) {
        bool valid = true;
        stack<char> sk;
        getline(cin, s);

        for (auto c : s) {
            if (c == '{' || c == '[' || c == '(' || c == '<') {
                sk.push(c);
            }
            else if (c == '}' || c == ']' || c == ')' || c == '>') {
                if (sk.empty()) {
                    valid = false;
                    break;
                }
                else if (parens[sk.top()] != c) {
                    valid = false;
                    break;
                }
                else {
                    sk.pop();
                }
            }
        }
        if(!sk.empty()) valid = false;

        cout << "Case " << i << ": ";
        if (valid == true) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}