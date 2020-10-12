#ifndef MATRIX_H_
#define MATRIX_H_

#include<iostream>
#include<iomanip>
#include "rational.h"

class Matrix{
	public:
		Matrix(int, int);
		~Matrix();

		Rational * operator [](int);
		friend std::ostream& operator<<(std::ostream&, Matrix const&);

		int getRows();
		int getColumns();

		void swapRows(int, int);

		Rational gcdRow(int);
		void multiplyRow(int, Rational);
		void sumRows(int, int, Rational = 1);


	private:
		Rational **matrix = NULL;
		int rows, columns;
};
#endif