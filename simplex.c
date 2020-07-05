#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define l 4
#define c 8

float **alocaMatriz(int lin, int col);
void preencheMatriz(float **matriz, int lin, int col);
void imprimeMatriz(float **matriz, int lin, int col);
void simplex(float **matriz, int lin, int col);
int verificaNegativo(float **matriz, int col);
int indiceColunaPivo(float **matriz, int col);
int indiceLinhaPivo(float **matriz, int lin, int col);
void normalizaLinhaPivo(float **matriz, int lin, int con);
void operacoesElementares(float **matriz, int lin, int col);
float *linhaPivo(float **matriz, int lin, int col);
void simplex();

int main()
{
    float **matriz= alocaMatriz(l, c);
    preencheMatriz(matriz, l, c);
    imprimeMatriz(matriz, l, c);
    simplex(matriz, l, c);
    return 0;
}

float **alocaMatriz(int lin, int col)
{
    float **matriz = (float **)malloc(sizeof(float *) * lin);
    for (int i = 0; i < lin; i++)
    {
        matriz[i] = (float *)malloc(sizeof(float) * col);
    }
    return matriz;
}
void preencheMatriz(float **matriz, int lin, int col)
{
    /*
    matriz[0][0] = 1;
    matriz[0][1] = -10;
    matriz[0][2] = -12;
    matriz[0][3] = -0;
    matriz[0][4] = 0;
    matriz[0][5] = 0;
    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 1;
    matriz[1][4] = 0;
    matriz[1][5] = 100;
    matriz[2][0] = 0;
    matriz[2][1] = 1;
    matriz[2][2] = 3;
    matriz[2][3] = 0;
    matriz[2][4] = 1;
    matriz[2][5] = 270;
    */
    for(int i=0; i<lin; i++)
    {
        for(int j=0; j<col; j++)
        {
            printf("[%d][%d] ", i,j);
            scanf("%f", &matriz[i][j]);
        }
    }
    
}
void imprimeMatriz(float **matriz, int lin, int col)
{
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%7.3f ", matriz[i][j]);
        printf("\n");
    }
}

int verificaNegativo(float **matriz, int col)
{
    for (int i = 0; i < col; i++)
    {
        if (matriz[0][i] < 0)
            return 1;
    }
    return 0;
}
int indiceColunaPivo(float **matriz, int col)
{
    float menor = matriz[0][1];
    int indiceMenor = 1;
    int i = 1;
    for (i = 1; i < col; i++)
    {
        if (matriz[0][i] < menor)
        {
            menor = matriz[0][i];
            indiceMenor = i;
        }
    }
    return indiceMenor;
}
int indiceLinhaPivo(float **matriz, int lin, int col)
{
    float menor = 9999999;
    float op = 0;
    int index = indiceColunaPivo(matriz, col);
    float ind;
    for (int i = 1; i < lin; i++)
    {
        if (matriz[i][index] != 0)
            op = matriz[i][col - 1] / matriz[i][index];
        if (op < menor && op > 0)
        {
            menor = op;
            ind = i;
        }
    }
    return ind;
}

void normalizaLinhaPivo(float **matriz, int lin, int col)
{
    int pivoI = indiceLinhaPivo(matriz, lin, col);
    int pivoJ = indiceColunaPivo(matriz, col);
    float pivo = matriz[pivoI][pivoJ];
    for (int i = 0; i < col; i++)
        matriz[pivoI][i] = matriz[pivoI][i] / pivo;
    printf("\n");
}

float *linhaPivo(float **matriz, int lin, int col)
{
    float *vet = (float *)malloc(sizeof(float) * col);
    int pivoI = indiceLinhaPivo(matriz, lin, col);
    for (int i = 0; i < col; i++)
    {
        vet[i] = matriz[pivoI][i];
    }
    return vet;
}
void operacoesElementares(float **matriz, int lin, int col)
{
    int pivoI = indiceLinhaPivo(matriz, lin, col);
    int pivoJ = indiceColunaPivo(matriz, col);
    float *linha = linhaPivo(matriz, lin, col);
    for (int i = 0; i < lin; i++)
    {
        if (i != pivoI)
        {
            float piv = matriz[i][pivoJ] * -1;
            for (int j = 0; j < col; j++)
                matriz[i][j] = linha[j] * piv + matriz[i][j];
        }
    }
    printf("\n");
}

void simplex(float **matriz, int lin, int col)
{
    int tag = verificaNegativo(matriz, col);
    do
    {
        tag = verificaNegativo(matriz, col);
        normalizaLinhaPivo(matriz, lin, col);
        operacoesElementares(matriz, lin, col);
        if(tag)
            imprimeMatriz(matriz, lin, col);
    }while(tag==1);
}