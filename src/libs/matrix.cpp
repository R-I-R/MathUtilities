#include "matrix.h"

Matrix::Matrix(int rows, int columns): rows(rows),columns(columns){
    this->matrix = new Rational*[rows];
    for(int a = 0; a < rows; a++) this->matrix[a] = new Rational[columns];
}

Matrix::~Matrix(){
    if(this->matrix){
        for(int a = 0; a < rows; a++) delete[] this->matrix[a];
        delete[] this->matrix;
        this->matrix = NULL;
    }
}

Rational * Matrix::operator [](int i)  {return (this->matrix[i]);}

std::ostream& operator <<(std::ostream &out, Matrix const& data){
    for(int a = 0; a < data.rows; a++){
        for(int b = 0; b < data.columns; b++) out << data.matrix[a][b] <<'\t';
        out << "\n";
    }
    return out;
}

int Matrix::getRows(){return rows;}
int Matrix::getColumns(){return columns;}


void Matrix::swapRows(int row1, int row2){
    Rational *temp;
    temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}
