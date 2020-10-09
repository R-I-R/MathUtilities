#include<iostream>
#include "libs/matrix.h"
#include "libs/rational.h"

double abs(double x) {return (x < 0 ? -x: x);}

int main(){
    /*int N,M;
    printf("Ingrese la cantidad de filas y columnas (filas columnas): ");
    scanf("%d %d",&N,&M);

    Matrix m(N,M);
    
    for(int a = 0; a < N; a++){
        for(int b = 0; b < M; b++){
            printf("ingrese M[%d][%d]:",a,b);
            scanf("%lf",&m[a][b]);
        }
    }

    std::cout << m << std::endl;
    m.swapRows(0,2);
    std::cout << m << std::endl;*/

    Rational x(0.0), y(1.0), z(-1.0);

    std::cout << x << " " << y << " " << z << std::endl;

    return 0;
}