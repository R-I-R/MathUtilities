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
		for(int b = 0; b < data.columns; b++) out << std::setw(10) << data.matrix[a][b] <<'\t';
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

Rational Matrix::gcdRow(int row){
	Rational result = matrix[row][0];
	for(int a = 1; a < columns; a++)
		result = Rational::MCD(result,matrix[row][a]);
	return (result != Rational(0) ? result: Rational(1));
}

void Matrix::multiplyRow(int row, Rational scalar){
	for(int a = 0; a < columns; a++)
		matrix[row][a] *= scalar;
}
void Matrix::sumRows(int fromRow, int toRow, Rational scalar){
	for(int a = 0; a < columns; a++)
		matrix[toRow][a] += matrix[fromRow][a]*scalar;
}
