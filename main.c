#include <stdio.h>
#include "simplex.c"
#include "tokenizacao.c"
#include "funcoesAuxiliares.c"


int fib(int n)
{
    if(n<=2)
        return 1;
    else
        return fib(n-1) + fib(n-2);
}
int main()
{
    int numLinhas, numColunas;
    interpretarModelo();
    interpretaMatriz(&numLinhas,&numColunas);
    float **matriz = preencheMatriz(numLinhas, numColunas);
    imprimeMatriz(matriz,numLinhas, numColunas);
    simplex(matriz, numLinhas, numColunas);
    return 0;
}

