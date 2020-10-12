#include<iostream>

#include "rational.h"
#include "rational.cpp"
#include "matrix.h"
#include "matrix.cpp"


Rational GCD_Row(Matrix* p, int row, int dimensions[2]){
  int j;
  Rational current_item, result, absolute_val;
  Rational zero = Rational(0);
  Rational one = Rational(1);
  result = zero;

  for (j=0; j<dimensions[1]; j++){
    current_item = (*p)[row][j];
    if (current_item == Rational(0))
      continue;

    absolute_val = Rational::abs(current_item);
    if (result == zero){
      result = absolute_val;
      continue;
    }

    result =  Rational::MCD(result, absolute_val);

    if (result == one)
      return one;
  }

  return result;
}


void PrintMatrix(Matrix* p, int dimensions[2])
{
  int count = 0;
  int i,j;

  for (i = 0; i < dimensions[0]; i++){
    std::cout << '|';

    for (j = 0; j < dimensions[1]; j++){
      if (j == dimensions[1]-1)
        std::cout << (*p)[i][j] << "|\n";
      else
        std::cout << (*p)[i][j] << ";    ";
      count++;
    }
  }

  std::cout << std::endl;
}


void RowMul(Matrix* p, int row, Rational k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    (*p)[row][j] *= k;
  }

  PrintMatrix(p, dimensions);
}


void RowDiv(Matrix* p, int row, Rational k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    (*p)[row][j] /= k;
  }

  PrintMatrix(p, dimensions);
}

void RowSum(Matrix* p, int row_to, int row_from, Rational k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    Rational sum = k * (*p)[row_from][j];
    (*p)[row_to][j] += sum;
  }

  PrintMatrix(p, dimensions);
}

void RowInter(Matrix* p, int row_to, int row_from, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    Rational temp = (*p)[row_to][j];
    (*p)[row_to][j] = (*p)[row_from][j];
    (*p)[row_from][j] = temp;
  }

  PrintMatrix(p, dimensions);
}

void OrderPivot(Matrix* p, int piv_pos[2], int dimensions[2], int piv_count)
{
  int row;
  Rational zero = Rational(0);

  if (piv_pos[0] == piv_count)
    return;

  for (row = piv_count; row < piv_pos[0]; row++){
    if ( (*p)[row][piv_pos[1]] == zero ){
      (*p).swapRows(row, piv_pos[0]);
      PrintMatrix(p, dimensions);
      return;
    }
  }
}


int ToEchelonForm(Matrix* p, int dimensions[2])
{
  int piv_count = 0;
  int i, j, pivot_row;
  Rational pivot_factor, current_item, gcd;
  Rational zero = Rational(0);

  for(i=0; i<dimensions[0]; i++){
    gcd = GCD_Row(p, i, dimensions);
    RowDiv(p, i, gcd, dimensions);
  }

  for (j = 0; j < dimensions[1]; j++){
    pivot_row = -1;

    for(i = piv_count; i < dimensions[0]; i++){
      current_item = (*p)[i][j];
      if (current_item == zero)
        continue;


      if (pivot_row == -1){
        if(current_item < zero){
          RowMul(p, i, Rational(-1), dimensions);
          current_item *= -1;
        }

        int current_pos[2] = {i,j};
        OrderPivot(p, current_pos, dimensions, piv_count);
        i = pivot_row = piv_count++;

        std::cout << "\n[NEW PIVOT]     pos:(" << i << ',' << j << ")\n";
        PrintMatrix(p, dimensions);
        std::cout << "---------------------------------------\n\n";
        pivot_factor = current_item;
      }

      else if (i > pivot_row){
        Rational abs_piv, abs_current, mcm;
        bool same_sign = (current_item>zero && pivot_factor>zero) || (current_item<zero && pivot_factor<zero);

        abs_piv = Rational::abs(pivot_factor);
        abs_current = Rational::abs(current_item);

        mcm = Rational::MCM(abs_piv, abs_current);
        if (abs_piv != abs_current)
          RowMul(p, i, mcm/abs_current, dimensions);

        if (same_sign)
          RowSum(p, i, pivot_row, -1 * mcm/abs_piv, dimensions);
        else
          RowSum(p, i, pivot_row, mcm/abs_piv, dimensions);
      }
    }
  }

  return piv_count;
}


void ToReducedEchelonForm(Matrix *p, int dimensions[2]){

  int i, j, piv_count;
  Rational pivot_factor, current_item;
  Rational zero = Rational(0);
  piv_count = ToEchelonForm(p, dimensions);

  int k;
  for (i=piv_count-1; i>0; i--){

    j = 0;
    do{
      current_item = (*p)[i][j];
      if (current_item == zero){
        j++;
        continue;
      }

      RowDiv(p, i, current_item, dimensions);
      pivot_factor = Rational(1);
      for (k=0; k<i; k++){

        current_item = (*p)[k][j];
        if (current_item == zero)
          continue;

        RowSum(p, k, i, -1 * current_item, dimensions);
      }
      j++;
    } while(j<dimensions[1] && current_item==zero);

  }

  RowDiv(p, 0, (*p)[0][0], dimensions);
}



int main(){
    int N,M;
    std::cout << "Ingrese la cantidad de filas y columnas (filas columnas): " << std::endl;
    std::cin >> N;
    std::cin >> M;
    int dim[] = {N,M};

    Matrix m(N,M);

    for(int a = 0; a < N; a++){
        for(int b = 0; b < M; b++){
            std::cout <<"ingrese M["<<a<<']' << '['<<b<<']';
            double tem;
            std::cin >> tem;
            m[a][b] = tem;
        }
    }
    std::cout << *(&m) << std::endl;

    for(int a = 0; a < N; a++)
        for(int b = 0; b < M; b++)
          std::cout << (*(&m))[a][b] << std::endl;

    PrintMatrix(&m, dim);
    std::cout << m << std::endl;

    ToReducedEchelonForm(&m, dim);
    return 0;
}
