#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "simplex.c"
#include "tokenizacao.c"
#define l 4
#define c 8


int main()
{

    //abrindo o arquivo
    float **matriz = alocaMatriz(l, c);
    preencheMatriz(matriz, l, c, 0);
    // imprimeMatriz(matriz, l, c);
    //simplex(matriz, l, c);
    return 0;
}

