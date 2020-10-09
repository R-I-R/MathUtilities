#ifndef MATRIX_H_
#define MATRIX_H_

#include<iostream>
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

    private:
        Rational **matrix = NULL;
        int rows, columns;
};
#endif