#include<iostream>
#include "libs/matrix.h"
#include "libs/rational.h"

double abs(double x) {return (x < 0 ? -x: x);}

int toEchelonForm(Matrix &matrix){
	int rows = matrix.getRows(), columns = matrix.getColumns();
	int pivCount = 0;

	for(int a = 0; a < rows; a++)
		matrix.multiplyRow(a, Rational::inverse(matrix.gcdRow(a)));
	
	printf("simplifying matrix\n");
	std::cout << matrix << std::endl;

	for(int col = 0; col < columns; col++){
		int pivotRow = -1;
		Rational pivotValue;

		for(int row = pivCount; row < rows; row++){
			if(matrix[row][col] == Rational(0)) continue;

			if(pivotRow == -1){
				if(row > pivCount)
					matrix.swapRows(row, pivCount);

				printf("New pivot in M[%d][%d]\n",row, col);
				std::cout << matrix << std::endl;

				row = pivotRow = pivCount++;
				pivotValue = matrix[row][col];
			}else{

				std::cout << "Multiplying M["<< row << "] by "<< (-pivotValue/matrix[row][col]) <<"\n";
				matrix.multiplyRow(row, -pivotValue/matrix[row][col]);
				std::cout << matrix << std::endl;

				std::cout << "Adding M["<< pivotRow << "] to "<< "M[" << row << "]\n";
				matrix.sumRows(pivotRow, row);
				std::cout << matrix << std::endl;
			}
		}
	}
	printf("Matrix in echelon form\n");
	std::cout << matrix << std::endl;
	return pivCount;
}
void toReducedEchelonForm(Matrix &matrix){
	int columns = matrix.getColumns();
	int pivCount = toEchelonForm(matrix);

	for(int row = pivCount-1; row >= 0; row--){
		for(int col = 0; col < columns; col++){
			if(matrix[row][col] == Rational(0)) continue;

			std::cout << "Multiplying M["<< row << "] by "<< Rational::inverse(matrix[row][col]) <<"\n";
			matrix.multiplyRow(row, Rational::inverse(matrix[row][col]));
			std::cout << matrix << std::endl;

			for(int rrow = 0; rrow < row; rrow++){
				if(matrix[rrow][col] == Rational(0)) continue;
				std::cout << "Adding M["<< row << "]*"<< -matrix[rrow][col] <<" to "<< "M[" << rrow << "]\n";
				matrix.sumRows(row, rrow, -matrix[rrow][col]);
				std::cout << matrix << std::endl;
			}	
			break;
		}
	}
}

int main(){
	int N,M;
	printf("Enter the number of rows and columns (rows columns): ");
	scanf("%d %d",&N,&M);

	Matrix m(N,M);
	
	for(int a = 0; a < N; a++){
		for(int b = 0; b < M; b++){
			printf("Enter M[%d][%d]:",a,b);
			std::cin >> m[a][b];
		}
	}

	printf("\nYour matrix");
	std::cout << m << std::endl;
	toReducedEchelonForm(m);
	printf("Matrix in reduced echelon form\n");
	std::cout << m << std::endl;

	return 0;
}