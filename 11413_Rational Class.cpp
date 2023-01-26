#include <iostream>
class Rational
{
    public:
        Rational( int = 0, int = 1 ); // default constructor
        Rational addition( const Rational & ) const; // function addition
        Rational multiplication( const Rational & ) const; // function multi.
        void printRational () const; // print rational format

    private:
        int numerator; // integer numerator
        int denominator; // integer denominator
        void reduce();
}; // end class Rational

int gcd(int a, int b);
//#include "function.h" // include definition of class Rational
#include <cmath>
using namespace std;
Rational::Rational(int son, int mom) {
    numerator = son;
    denominator = mom;
    if (mom < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    reduce();
}
Rational Rational::addition(const Rational &d) const {
    int mom = denominator * (d.denominator);
    int son = numerator * (d.denominator) + (d.numerator) * denominator;
    Rational xx(son, mom);
    return xx;
}
Rational Rational::multiplication(const Rational &d) const {
    int mom = denominator * (d.denominator);
    int son = numerator * (d.numerator);
    Rational xx(son, mom);
    return xx;
}
void Rational::printRational() const {
    cout << this->numerator << "/" << this->denominator << "\n";
}
void Rational::reduce() {
    int common = gcd(abs(this->numerator), this->denominator);
    numerator = numerator / common;
    denominator = denominator / common;
}
//

int main()
{
    char s1;
    int s2, s3, s4, s5;

    Rational x;
    while(cin >>s1>>s2>>s3>>s4>>s5)
    {
        if(cin.eof())
        {
		    break;
        }
        Rational c(s2, s3), d(s4, s5);
        if(s1 == '+')
        {
            x = c.addition( d ); // adds object c and d; sets the value to x
            x.printRational(); // prints rational object x
        }
        else if(s1 == '*')
        {
            x = c.multiplication( d ); // multiplies object c and d
            x.printRational(); // prints rational object x
        }
    }
}

int gcd(int a, int b){
    return (b == 0) ? a : gcd(b, a % b);
}
