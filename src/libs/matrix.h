#ifndef MATRIX_H_
#define MATRIX_H_

#include<cstddef>

class Matrix{
    public:
        Matrix(int, int);

        double * operator [](int);

        ~Matrix();

    private:
        double **matrix;
        int rows, columns;
};
#endif