#ifndef MATRIX_H_
#define MATRIX_H_

#include<cstddef>
#include<cstdio>

class Matrix{
    public:
        Matrix(int, int);
        double * operator [](int);
        ~Matrix();

        void print();
        void swapRows(int, int);

    private:
        double **matrix = NULL;
        int rows, columns;
};
#endif