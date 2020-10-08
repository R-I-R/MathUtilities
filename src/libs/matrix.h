#ifndef MATRIX_H_
#define MATRIX_H_

#include<iostream>

class Matrix{
    public:
        Matrix(int, int);
        ~Matrix();

        double * operator [](int);
        friend std::ostream& operator<<(std::ostream&, Matrix const&);

        int getRows();
        int getColumns();

        void swapRows(int, int);

    private:
        double **matrix = NULL;
        int rows, columns;
};
#endif