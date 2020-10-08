#include "rational.h"

int maximumCommonDivisor(int a, int b){
    if(b == 0) return a;
    return maximumCommonDivisor(b, a%b);
}
int minimumCommonMultiple(int a, int b){
    return (a*b)/maximumCommonDivisor(a,b);
}

Rational::Rational(): numerator(0), denominator(1){}
Rational::Rational(int numerator, int denominator): numerator(numerator), denominator(denominator){}
Rational::Rational(int number): numerator(number), denominator(1){}
Rational::Rational(double){

}
Rational::~Rational(){}

Rational::operator double() const{return double(numerator)/double(denominator);}

Rational Rational::operator -() const{Rational res = *this; res.denominator *= -1; return res;}
Rational Rational::operator +(Rational const& r) const{Rational res = *this; res += r; return res;}
Rational Rational::operator -(Rational const& r) const{Rational res = *this; res -= r; return res;}
Rational Rational::operator *(Rational const& r) const{Rational res = *this; res *= r; return res;}
Rational Rational::operator /(Rational const& r) const{Rational res = *this; res /= r; return res;}

Rational& Rational::operator =(Rational const& r){denominator = r.denominator; numerator = r.numerator; return *this;}
Rational& Rational::operator +=(Rational const& r){
    numerator = (numerator * r.denominator) + (r.numerator * denominator);
    denominator *= r.denominator;
    *this = Rational::reduce(*this);
    return *this;
}
Rational& Rational::operator *=(Rational const& r){
    denominator *= r.denominator;
    numerator *= r.numerator;
    *this = Rational::reduce(*this);
    return *this;
}
Rational& Rational::operator -=(Rational const& r){*this += -r; return *this;}
Rational& Rational::operator /=(Rational const& r){*this *= Rational::inverse(r); return *this;}

bool Rational::operator <(Rational const& r){return this->compare(r) == -1;}
bool Rational::operator >(Rational const& r){return this->compare(r) == 1;}
bool Rational::operator <=(Rational const& r){return this->compare(r) <= 0;}
bool Rational::operator >=(Rational const& r){return this->compare(r) >= 0;}
bool Rational::operator !=(Rational const& r){return this->compare(r) != 0;}
bool Rational::operator ==(Rational const& r){return this->compare(r) == 0;}

std::ostream& operator<<(std::ostream& out, Rational const& r){out << r.numerator<<'/'<<r.denominator; return out;}

int Rational::getNumerator(){return numerator;}
int Rational::getDenominator(){return denominator;}

int Rational::compare(Rational const& r){
    int r1 = numerator * r.denominator;
    int r2 = r.numerator * denominator;
    if(r1 == r2) return 0;
    else if(r1 < r2) return -1;
    else return 1;
}

Rational Rational::reduce(Rational const& r){
    int mcd = maximumCommonDivisor(r.numerator, r.denominator);
    return Rational(r.numerator / mcd, r.denominator / mcd);
}

Rational Rational::inverse(Rational const& r){return Rational(r.denominator, r.numerator);}