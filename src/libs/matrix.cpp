#include "matrix.h"

//Constructor
Matrix::Matrix(int rows, int columns): rows(rows),columns(columns){
	this->matrix = new Rational*[rows];
	for(int a = 0; a < rows; a++) this->matrix[a] = new Rational[columns];
}

//Destructor
Matrix::~Matrix(){
	if(this->matrix){
		for(int a = 0; a < rows; a++) delete[] this->matrix[a];
		delete[] this->matrix;
		this->matrix = NULL;
	}
}

// sobreescribo operador []
Rational * Matrix::operator [](int i)  {return (this->matrix[i]);}

// sobreescribo operador << para poder printear la matriz
std::ostream& operator <<(std::ostream &out, Matrix const& data){
	for(int a = 0; a < data.rows; a++){
		for(int b = 0; b < data.columns; b++) out << std::setw(10) << data.matrix[a][b] <<'\t';
		out << "\n";
	}
	return out;
}

// devuelve el numero de filas
int Matrix::getRows(){return rows;}

//devuelve el numero de columnas
int Matrix::getColumns(){return columns;}

// intercambia dos filas
void Matrix::swapRows(int row1, int row2){
	Rational *temp;
	temp = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = temp;
}

// devuelve el maximo comun divisor de la fila
Rational Matrix::gcdRow(int row){
	Rational result = matrix[row][0];
	for(int a = 1; a < columns; a++)
		result = Rational::MCD(result,matrix[row][a]);
	return (result != Rational(0) ? result: Rational(1));
}

// multiplica la fila por un escalar
void Matrix::multiplyRow(int row, Rational scalar){
	for(int a = 0; a < columns; a++)
		matrix[row][a] *= scalar;
}

// suma la fila origen multiplicada por un escalar a la fila destino
void Matrix::sumRows(int fromRow, int toRow, Rational scalar){
	for(int a = 0; a < columns; a++)
		matrix[toRow][a] += matrix[fromRow][a]*scalar;
}
