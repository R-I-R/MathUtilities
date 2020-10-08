#include <iostream>

void CreateMatrix();

int GCD(int a, int b){
  if (b == 0)
    return a;
  return GCD(b, a%b);
}

int LCM(int a, int b){
  return (a / GCD(a,b)) * b;
}

int GCD_Row(int* p, int row, int dimensions[2]){
  int result = -1;
  int j, current_item, absolute_val;

  for (j=0; j<dimensions[1]; j++){
    current_item = *(p + row*dimensions[1] + j);
    if (current_item == 0)
      continue;

    absolute_val = (current_item > 0) ? current_item : -1 * current_item;

    if (result == -1){
      result = absolute_val;
      continue;
    }

    result = GCD(result, absolute_val);

    if (result == 1)
      return 1;
  }

  return result;
}


void PrintMatrix(int* p, int dimensions[2])
{
  int count = 0;
  int i = 0;
  int j = 0;

  for (i = 0; i < dimensions[0]; i++){
    std::cout << '|';
    for (j = 0; j < dimensions[1]; j++){
      if (j == dimensions[1]-1)
        std::cout << *(p+count) << "|\n";
      else
        std::cout << *(p+count) << ";    ";
      count++;
    }
  }

  std::cout << std::endl;
}

void RowMul(int* p, int row, int k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    *(p + row*dimensions[1] + j) *= k;
  }

  PrintMatrix(p, dimensions);
}

void RowDiv(int* p, int row, int k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    *(p + row*dimensions[1] + j) /= k;
  }

  PrintMatrix(p, dimensions);
}

void RowSum(int* p, int row_to, int row_from, int k, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    int sum = k * (*(p + row_from*dimensions[1] + j));
    *(p + row_to*dimensions[1] + j) += sum;
  }

  PrintMatrix(p, dimensions);
}

void RowInter(int* p, int row_to, int row_from, int dimensions[2])
{
  int j;

  for (j = 0; j < dimensions[1]; j++){
    int temp = *(p + row_to*dimensions[1] + j);
    *(p + row_to*dimensions[1] + j) = *(p + row_from*dimensions[1] + j);
    *(p + row_from*dimensions[1] + j) = temp;
  }

  PrintMatrix(p, dimensions);
}

void OrderPivot(int* p, int piv_pos[2], int dimensions[2], int piv_count)
{
  int row;

  if (piv_pos[0] == piv_count)
    return;

  for (row = piv_count; row < piv_pos[0]; row++){
    if ( *(p + row*dimensions[1] + piv_pos[1]) == 0 ){
      RowInter(p, row, piv_pos[0], dimensions);
      return;
    }
  }
}

void ToEchelonForm(int* p, int dimensions[2])
{
  int piv_count = 0;
  int i, j, pivot_row, pivot_factor, current_item, gcd;

  for(i=0; i<dimensions[0]; i++){
    gcd = GCD_Row(p, i, dimensions);
    RowDiv(p, i, gcd, dimensions);
  }

  for (j = 0; j < dimensions[1]; j++){
    pivot_row = -1;

    for(i = piv_count; i < dimensions[0]; i++){
      current_item = *(p + i*dimensions[1] + j);
      if (current_item == 0)
        continue;


      if (pivot_row == -1){
        if(current_item < 0){
          RowMul(p, i, -1, dimensions);
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
        int abs_piv, abs_current, lcm;
        int same_sign = (current_item>0 && pivot_factor>0) || (current_item<0 && pivot_factor<0);

        abs_piv = (pivot_factor>0) ? pivot_factor : -1 * pivot_factor;
        abs_current = (current_item>0) ? current_item : -1 * current_item;

        lcm = LCM(abs_piv, abs_current);

        RowMul(p, i, lcm/abs_current, dimensions);
        if (same_sign)
          RowSum(p, i, pivot_row, -1 * lcm/abs_piv, dimensions);
        else
          RowSum(p, i, pivot_row, lcm/abs_piv, dimensions);
      }
    }
  }

  int k;
  for (i=piv_count-1; i>0; i--){
    gcd = GCD_Row(p, i, dimensions);
    RowDiv(p, i, gcd, dimensions);

    j = 0;
    do{
      current_item = *(p + i*dimensions[1] + j);
      if (current_item == 0){
        j++;
        continue;
      }

      pivot_factor = current_item;
      for (k=0; k<i; k++){

        current_item = *(p + k*dimensions[1] + j);
        if (current_item == 0)
          continue;

        int abs_piv, abs_current, lcm;
        int same_sign = (current_item>0 && pivot_factor>0) || (current_item<0 && pivot_factor<0);

        abs_piv = (pivot_factor>0) ? pivot_factor : -1 * pivot_factor;
        abs_current = (current_item>0) ? current_item : -1 * current_item;

        lcm = LCM(abs_piv, abs_current);

        RowMul(p, k, lcm/abs_current, dimensions);
        if (same_sign)
          RowSum(p, k, i, -1 * lcm/abs_piv, dimensions);
        else
          RowSum(p, k, i, lcm/abs_piv, dimensions);
      }
      j++;
    } while(j<dimensions[1] && current_item==0);

  }

  gcd = GCD_Row(p, 0, dimensions);
  RowDiv(p, 0, gcd, dimensions);
}


int main()
{
  int matrix[4][5] = {{1,2,3,4,4},{2,3,5,1,3},{3,6,2,3,2},{2,5,8,4,1}};
  int dimensions[2] = {4,5};

  ToEchelonForm(&matrix[0][0], dimensions);
  PrintMatrix(&matrix[0][0], dimensions);

  //delete[] matrix;
  return 0;
}
