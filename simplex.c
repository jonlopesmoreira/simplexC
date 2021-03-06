#include "simplex.h"
#include "funcoesAuxiliares.h"
#include "tokenizacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float **alocaMatriz(int lin, int col)
{
    float **matriz = (float **)malloc(sizeof(float *) * lin);
    for (int i = 0; i < lin; i++)
    {
        matriz[i] = (float *)malloc(sizeof(float) * col);
    }
    return matriz;
}
int interpretarModelo()
{
    FILE *arquivo = fopen("model.txt", "r");
    FILE *arquivo2 = fopen("matriz.txt", "w");
    fclose(arquivo2);
    char linha[100];
    int i=0,  n = 0;
    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 0;
    }
    else
    {
        n = contaVariaveisDeFolga();
        printf("Numero de variaveis de folga: %d\n", n);
        while (fgets(linha, 100, arquivo) != NULL)
        {
            printf("%s", linha);
            verificaTokens(linha, i++);
        }
        printf("\n");
    }
    fclose(arquivo);
    return 1;
}

int interpretaMatriz(int *numLinhas, int *numColunas)
{
    FILE *arq = fopen("matriz.txt", "r");
    char numero[100];
    int flag = 0;
    (*numColunas)=0;
    (*numLinhas)=0;

    while(fscanf(arq, "%s", numero) != EOF)
    {
        if(strcmp(numero, ";")==0)
        {
            flag=1;
            (*numLinhas)++;
        }
         if(flag==0)
            (*numColunas)++;   
    }
     if(feof(arq))
        puts("\nO arquivo inteiro foi lido.\n");
    else 
    {
        puts("O indicador de fim de arquivo (EOF) não está marcado. Um erro ocorreu.");
        fclose(arq);
        return 0;
    }
    fclose(arq);
    return 1;
}
float **preencheMatriz(int lin, int col)
{
    FILE *arq = fopen("matriz.txt", "r");
    float numero;
    char trash[10];
    float **matriz = (float**) malloc(sizeof(float*)*lin);

    for (int i = 0; i < lin; i++)
       matriz[i] = (float*) malloc(sizeof(float)*col);
    
    for( int i=0; i<lin; i++)
    {
        for(int j=0; j<col; j++)
        {
            fscanf(arq,"%f", &numero);
            matriz[i][j] = numero;
        }
        fscanf(arq,"%s", trash);
    }
    fclose(arq);
    return matriz;

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
        if (tag)
            imprimeMatriz(matriz, lin, col);
    } while (tag == 1);
}