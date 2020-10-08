#include<iostream>
#include "libs/matrix.h"
#include "libs/rational.h"

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

    Rational r1, r2(5), r3(3,4);
    std::cout << r1 <<" "<< r2 <<" "<< r3 << '\n';
    r1 += 3;
    r2 /= r3;
    std::cout << r1 <<" "<< r2 <<" "<< r3 << '\n';
    r3 *= 2;
    r2 -= Rational(2,3);
    std::cout << r1 <<" "<< r2 <<" "<< r3 << '\n';

    return 0;
}