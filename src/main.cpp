#include<iostream>
#include "libs/matrix.h"
#include "libs/rational.h"

double abs(double x) {return (x < 0 ? -x: x);}

int main(){
    int N,M;
    printf("Ingrese la cantidad de filas y columnas (filas columnas): ");
    scanf("%d %d",&N,&M);

    Matrix m(N,M);
    
    for(int a = 0; a < N; a++){
        for(int b = 0; b < M; b++){
            printf("ingrese M[%d][%d]:",a,b);
            double tem;
            scanf("%lf",&tem);
            m[a][b] = tem;
        }
    }

    std::cout << m << std::endl;
    m.swapRows(0,2);
    std::cout << m << std::endl;

    return 0;
}