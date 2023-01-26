#include <iostream>
#define maxsize 1000
class INT {
    public:
        INT() {}
        INT operator=(INT);
        INT operator+(INT);
        friend std::istream &operator>>(std::istream &, INT &);
        friend std::ostream &operator<<(std::ostream &, INT);
    protected:
        char data[maxsize + 1];
        int len;
};
//#include "function.h"
#include <cstring>
using namespace std;
INT INT::operator=(INT r) {
    for (int i = 0 ; i < r.len ; i++) {
        this->data[i] = r.data[i];
    }
    this->len = r.len;
    return *this;
}
INT INT::operator+(INT r) {
    if (this->len < r.len) {
        INT tmp = *this;
        *this = r;
        r = tmp;
    }
    int i , j;
    for (i = this->len - 1, j = r.len - 1 ; i >= 0 ; i--, j--) {
        if (j >= 0) {
            this->data[i] += r.data[j] - '0';
        }
        if (this->data[i] > '9') {
            this->data[i] -= 10;
            if (i >= 1) {
                this->data[i - 1]++;
            }
            else {
                for (int k = this->len - 1 ; k >= 0 ; k--) {
                    data[k + 1] = data[k];
                }
                data[0] = '1';
                len++;
            }
        }
    }
    return *this;
}
std::istream &operator>>(std::istream &input, INT &num) {
    input >> num.data;
    num.len = strlen(num.data);
    return input;
}
std::ostream &operator<<(std::ostream &output, INT num) {
    for (int i = 0 ; i < num.len ; i++) {
        output << num.data[i];
    }
    return output;
}
//
int main() {
    INT a, b, c;
    cin >> a >> b;
    c = a + b;
    cout << c << endl;
    return 0;
}
