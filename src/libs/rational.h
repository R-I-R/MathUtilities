#ifndef RATIONAL_H_
#define RATIONAL_H_

#include<iostream>

int maximumCommonDivisor(int, int);
int minimumCommonMultiple(int, int);

class Rational{
	public:
		Rational();
		Rational(int, int);
		Rational(int);
		Rational(double);
		~Rational();

		operator double() const;

		Rational operator +(Rational const&) const;
		Rational operator -(Rational const&) const;
		Rational operator -() const;
		Rational operator *(Rational const&) const;
		Rational operator /(Rational const&) const;

		Rational& operator =(Rational const&);
		Rational& operator +=(Rational const&);
		Rational& operator -=(Rational const&);
		Rational& operator *=(Rational const&);
		Rational& operator /=(Rational const&);

		bool operator <(Rational const&);
		bool operator >(Rational const&);
		bool operator <=(Rational const&);
		bool operator >=(Rational const&);
		bool operator !=(Rational const&);
		bool operator ==(Rational const&);
		
		friend std::ostream& operator<<(std::ostream&, Rational const&);
		friend std::istream& operator>>(std::istream&, Rational&);

		int getNumerator();
		int getDenominator();

		static Rational reduce(Rational const&);
		static Rational inverse(Rational const&);
		static Rational abs(Rational const&);
		static Rational MCD(Rational const&, Rational const&);
		static Rational MCM(Rational const&, Rational const&);

	private:
		int numerator;
		int denominator;

		int compare(Rational const&);
};
#endif