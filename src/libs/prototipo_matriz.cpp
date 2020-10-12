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


int ToEchelonForm(Matrix* p, int dimensions[2])
{
  int piv_count = 0;
  int i, j, pivot_row;
  Rational pivot_value, current_item, gcd;
  Rational zero = Rational(0);

  //divide cada fila por su MCD por propositos de claridad
  for(i=0; i<dimensions[0]; i++){
    gcd = GCD_Row(p, i, dimensions);
    RowDiv(p, i, gcd, dimensions);
  }

  //iteracion por columnas para seleccion del pivote y formacion de ceros inferiores
  for (j = 0; j < dimensions[1]; j++){
    pivot_row = -1;

    //por cada columna se revisaran las filas
    for(i = piv_count; i < dimensions[0]; i++){
      current_item = (*p)[i][j];

      //si el elemento es cero se continua iterando las filas
      if (current_item == zero)
        continue;

      //de no existir otro pivote en la columna, se selecciona el elemento actual como pivote
      if (pivot_row == -1){
        //se deja el elemento pivote en positivo por propositos de claridad
        if(current_item < zero){
          RowMul(p, i, Rational(-1), dimensions);
          current_item *= -1;
        }
        pivot_value = current_item;

        //si es que hay ceros sobreponiendose a la fila que deberia ocupar el pivote, se intercambian filas
        if (i > piv_count){
          //fila del pivote corresponde con numero de cuenta de pivotes
          (*p).swapRows(i, piv_count);
          PrintMatrix(p, dimensions);
        }

        //se devuelve el iterador de filas a la fila del pivote para reducir los elementos de las filas inferiores
        i = pivot_row = piv_count++; //incapie en el posfijo, la cuenta suma despues de la igualacion

        std::cout << "\n[NEW PIVOT]     pos:(" << i << ',' << j << ")\n";
        PrintMatrix(p, dimensions);
        std::cout << "---------------------------------------\n\n";
      }

      //caso de ya haber encontrado un pivote en la columna, se reduciran los elementos de las filas inferiores
      else {

        //si es que los valores del elemento iterado y el pivote NO son iguales
        //    se escala la fila del elemento iterado de modo que este iguale al pivote pero en signo contrario
        if (pivot_value != current_item)
          RowMul(p, i, -pivot_value/current_item, dimensions);

        //se forma un cero en m[i][j]
        RowSum(p, i, pivot_row, 1, dimensions);
      }
    }
  }

  //se retorna el numero de pivotes contados en el escalonado (con propositos de utilidad en la reduccion)
  return piv_count;
}


void ToReducedEchelonForm(Matrix *p, int dimensions[2]){

  int i, j, piv_count;
  Rational pivot_value, current_item;
  Rational zero = Rational(0);
  piv_count = ToEchelonForm(p, dimensions);

  int k;
  //se itera por filas partiendo por la correspondiente al ultimo elemento pivote
  for (i=piv_count-1; i>0; i--){

    j = 0;
    pivot_value = zero;
    do{
      //iteracion por columnas para encontrar elemento pivote dentro de la fila
      //primer elemento no nulo de la columna corresponde al pivote
      //mientras encuentre ceros sigue iterando
      //habiendo encontrado un pivote se rompe la condicion pivot_value==zero del do while
      pivot_value = (*p)[i][j];
      if (pivot_value == zero){
        j++;
        continue;
      }

      RowDiv(p, i, pivot_value, dimensions);

      //habiendo encontrado al elemento pivote, se resta hacía arriba formando ceros en la columna pivote
      for (k=0; k<i; k++){

        current_item = (*p)[k][j];
        if (current_item == zero)
          continue;

        RowSum(p, k, i, -1 * current_item, dimensions);
      }
      j++;
    } while(j<dimensions[1] && pivot_value==zero);

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
    std::cout << m << std::endl;

    for(int a = 0; a < N; a++)
        for(int b = 0; b < M; b++)
          std::cout << (*(&m))[a][b] << std::endl;

    PrintMatrix(&m, dim);
    std::cout << m << std::endl;

    ToReducedEchelonForm(&m, dim);
    return 0;
}
