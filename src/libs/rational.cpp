#include "rational.h"

int maximumCommonDivisor(int a, int b){
    if(b == 0) return a;
    return maximumCommonDivisor(b, a%b);
}
int minimumCommonMultiple(int a, int b){
    return (a*b)/maximumCommonDivisor(a,b);
}


Rational::Rational(): numerator(0), denominator(1){}
Rational::Rational(int numerator, int denominator): numerator((denominator < 0 ? -1:1)*numerator), denominator((denominator < 0 ? -1:1)*denominator){}
Rational::Rational(int number): numerator(number), denominator(1){}
Rational::Rational(double decimal){ // pasar de decimal a fraccion mediante busqueda binaria
    double precision = 1e-9; //error relativo

    int signo = decimal < 0 ? -1: 1;
    decimal *= signo;

    if(decimal == 0 || decimal < precision){numerator = 0; denominator = 1; return;} // si es menor a la precision lo damos por 0

    double error = decimal * precision; // error absoluto
    int n = int(decimal); // consigo la parte entera
    decimal -= n; // me quedo con la parte decimal

    if(decimal < error){numerator = n*signo; denominator = 1; return;} // si el decimal es mas pequeño q el error sera igual a la parte entera
    if(1 - error < decimal){numerator = (n+1)*signo; denominator = 1; return;} // si el decimal es mayor al error por arriba es igual al sig numero entero

    int minNumerator = 0, minDenominator = 1; // la fraccion mas pequeña 0/1
    int maxNumerator = 1, maxDenominator = 1; // la fraccion mas grande 1/1

    while(true){
        int pivNumerator = minNumerator + maxNumerator, pivDenominator = minDenominator + maxDenominator;

        if(pivDenominator * (decimal + error) < pivNumerator){  // si la fraccion es mayor q el decimal + error, reduzco el limite superior
            maxDenominator = pivDenominator;
            maxNumerator = pivNumerator;
        }else if(pivDenominator * (decimal - error) > pivNumerator){ // si la fraccion es menor q el decimal - error, aumento el limite inferior
            minNumerator = pivNumerator;
            minDenominator = pivDenominator;
        }else{
            numerator = signo*(n*pivDenominator + pivNumerator); // si la fraccion esta dentro del margen de error, es la correcta
            denominator = pivDenominator;
            return;
        }
    }
}
Rational::~Rational(){}

Rational::operator double() const{return double(numerator)/double(denominator);}

Rational Rational::operator -() const{Rational res = *this; res.numerator *= -1; return res;}
Rational Rational::operator +(Rational const& r) const{Rational res = *this; res += r; return res;}
Rational Rational::operator -(Rational const& r) const{Rational res = *this; res -= r; return res;}
Rational Rational::operator *(Rational const& r) const{Rational res = *this; res *= r; return res;}
Rational Rational::operator /(Rational const& r) const{Rational res = *this; res /= r; return res;}

Rational& Rational::operator =(Rational const& r){denominator = r.denominator; numerator = r.numerator; return *this;}
Rational& Rational::operator +=(Rational const& r){
    int mcm = minimumCommonMultiple(r.denominator,denominator);
    numerator = (numerator * mcm/denominator) + (r.numerator * mcm/r.denominator);
    denominator = mcm;
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

Rational Rational::abs(Rational const& r){return (r < 0 ? -r: r);}