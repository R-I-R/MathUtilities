#include "matrix.h"

Matrix::Matrix(int rows, int columns): rows(rows),columns(columns){
    this->matrix = new double*[rows];
    for(int a = 0; a < rows; a++) this->matrix[a] = new double[columns];
}

double * Matrix::operator [](int i)  {return (this->matrix[i]);}

Matrix::~Matrix(){
    if(this->matrix){
        for(int a = 0; a < rows; a++) delete[] this->matrix[a];
        delete[] this->matrix;
        this->matrix = NULL;
    }
}
