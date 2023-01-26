#include <iostream>
#include <stack>
#include <string>
#include <map>

using namespace std;

map<char, char> parens = {
    {'{', '}'},
    {'[', ']'},
    {'(', ')'},
    {'<', '>'},
    {'s', 'm'}
};

int main() {
    string s;
    stack<char> sk, kk;
    while (getline(cin, s)) {
        bool valid = true;
        //getline(cin, s);
        for (int i = 0 ; i < s.size() ; i++) {
            string sm = "sm";
            
            if (s[i] == '{' || s[i] == '[' || s[i] == '(' || s[i] == '<' || s[i] =='s') {
                sk.push(s[i]);
            }
            else if (s[i] == '}' || s[i] == ']' || s[i] == ')' || s[i] == '>' || s[i] == 'm') {
                if (!kk.empty()) {
                    valid = false;
                    break;
                }
                if (sk.empty()) {
                    valid = false;
                    break;
                }
                else if (parens[sk.top()] != s[i]) {
                    valid = false;
                    break;
                }
                else 
                    sk.pop();
            }
            /*else if (s[i] == 's') {
                if (s[i + 1] != 'm' || i == s.length() - 1) {
                    valid = false;
                    break;
                }
            }
            else if (s[i] == 'm') {
                if (s[i - 1] != 's' || i == 0) {
                    valid = false;
                    break;
                }
            }*/
        }
        if(!sk.empty()) {

            valid = false;
            while (!sk.empty()) {
                sk.pop();
            }
            
        }

        if (valid) cout << "SM\n";
        else cout << "MS\n";
    }
    return 0;
}