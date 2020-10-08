#ifndef RATIONAL_H_
#define RATIONAL_H_

#include<iostream>

class Rational{
    public:
        Rational(int, int);
        ~Rational();

        friend std::ostream& operator<<(std::ostream&, Rational const&);

    private:
        int numerator;
        int denominator;
};
#endif