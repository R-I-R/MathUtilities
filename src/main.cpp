#include<iostream>
#include "libs/matrix.h"

int main(){
    int N,M;
    printf("Ingrese la cantidad de filas y columnas (filas columnas): ");
    scanf("%d %d",&N,&M);

    Matrix m(N,M);
    for(int a = 0; a < N; a++){
        for(int b = 0; b < M; b++){
            printf("ingrese M[%d][%d]:",a,b);
            scanf("%lf",&m[a][b]);
        }
    }

    m.print();
    m.swapRows(0,2);
    m.print();

    return 0;
}