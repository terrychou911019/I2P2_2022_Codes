#include<iostream>
#include <string>
using namespace std;
class String_Calculator {
    public:
        String_Calculator(){};
        String_Calculator(const string);
        String_Calculator& Add(const string);
        String_Calculator& Subtract(const string);
        String_Calculator& DividedBy(const string);
        void output() const;

    private:
        string s = "";
}; //end class String_Calculator

//#include"function.h"
//#include <iostream>
//using namespace std;

String_Calculator::String_Calculator(const string str) {
    s = str;
}
String_Calculator& String_Calculator::Add(const string str) {
    s += str;
    return *this;
}
String_Calculator& String_Calculator::Subtract(const string str) {
    string tmp = "error";
    int found = s.find(str);
    if (found != string::npos) {
        s.erase(found, str.size());
    }
    else {
        s = tmp;
    }
    return *this;
}
String_Calculator& String_Calculator::DividedBy(const string str) {
    int cnt = 0, pos = 0;
    int found = s.find(str, pos);
    while (found != string::npos) {
        cnt++;
        pos = found + 1;
        found = s.find(str, pos);
    }
    s = to_string(cnt);
    return *this;
}
void String_Calculator::output() const {
    cout << s << "\n";
}
//

int main(){
    int n;
    string x, y;
    cin >> n;
    while(n--){
        cin >> x >> y;
        String_Calculator a(x), ans;
        ans = a.Subtract(y).Add(y).DividedBy(y);
        ans.output();
    }
}
