#include <stdio.h>
#include "simplex.c"
#include "tokenizacao.c"
#include "funcoesAuxiliares.c"

int main()
{
    int numLinhas, numColunas;
    interpretarModelo();
    interpretaMatriz(&numLinhas,&numColunas);
    float **matriz = preencheMatriz(numLinhas, numColunas);
    imprimeMatriz(matriz,numLinhas, numColunas);
    return 0;
}

