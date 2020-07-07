#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#define l 4
#define c 8

float **alocaMatriz(int lin, int col);
int preencheMatriz(float **matriz, int lin, int col, int metodo);
void imprimeMatriz(float **matriz, int lin, int col);
void simplex(float **matriz, int lin, int col);
int verificaNegativo(float **matriz, int col);
int indiceColunaPivo(float **matriz, int col);
int indiceLinhaPivo(float **matriz, int lin, int col);
void normalizaLinhaPivo(float **matriz, int lin, int con);
void operacoesElementares(float **matriz, int lin, int col);
float *linhaPivo(float **matriz, int lin, int col);
void simplex();

void tokenizar(char *linha);
void verificaTokens(char *linha);
void validaVariaveisFO(char *linha);
void consomeVariavel(char **linha);
int consomeSinal(char **linha);


int main()
{

    //abrindo o arquivo
    float **matriz = alocaMatriz(l, c);
    preencheMatriz(matriz, l, c, 0);
    // imprimeMatriz(matriz, l, c);
    //simplex(matriz, l, c);
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
int preencheMatriz(float **matriz, int lin, int col, int metodo)
{
    FILE *arquivo = fopen("matriz.txt", "r");
    char linha[100];
    if (metodo == 1)
    {
        for (int i = 0; i < lin; i++)
        {
            for (int j = 0; j < col; j++)
            {
                printf("[%d][%d] ", i, j);
                scanf("%f", &matriz[i][j]);
            }
        }
    }
    else
    {
        if (arquivo == NULL)
        {
            printf("Erro na abertura do arquivo!");
            return 1;
        }
        else
        {
            float r;
            char car;
            fgets(linha, 100, arquivo);
            verificaTokens(linha);
            // printf("%s", linha);
            // while (!feof(arquivo))
            {
                //fgets(linha, 100, arquivo);
                //tokenizar(linha);
                //verificaTokens(linha);
                /*fscanf(arquivo, "%c", &car);
               if(!feof(arquivo))
               {
                   printf("%c", car);
               }
               */
            }
        }
    }
    fclose(arquivo);
    return 0;
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

void tokenizar(char *linha)
{
    int i = 0;
    while (linha[i] != '\0')
    {
        printf("%c", linha[i++]);
    }
}

void verificaTokens(char *linha)
{
    int n = strlen(linha);
    // for(int i=0; i<n; i++)
    //{
    if (strnicmp(linha, "Max ", 4) == 0)
    {
        printf("Achou Max\n");
        linha += 4;
        if (strnicmp(linha, "lucro ", 6) == 0)
        {
            linha += 6;
            printf("Achou Lucro 6\n");
            if (strnicmp(linha, "= ", 2) == 0)
            {
                linha += 2;
                printf("Achou igual 2\n");
                validaVariaveisFO(linha);
            }
            else if (strnicmp(linha, "=", 1) == 0)
            {
                linha += 1;
                printf("Achou igual 1\n");
            }
        }
        else if (strnicmp(linha, "lucro", 5) == 0)
        {
            linha += 5;
            printf("Achou Lucro 5\n");
        }
        else
        {
            printf("nao achou lucro");
        }
    }
    else
    {
        printf("Nao achou\n");
    }
    //}
}

void validaVariaveisFO(char *linha)
{
    int n = strlen(linha);
    int i = 0;
    printf("%s", linha);
    consomeVariavel(&linha);
    printf("%s", linha);
    consomeSinal(&linha);
    printf("%s", linha);
    consomeVariavel(&linha);
    printf("%s", linha);
    consomeSinal(&linha);
  
}

void consomeVariavel(char **linha)
{
    while ((*linha)[0] == ' ') //elimina espaços brancos
            (*linha)++;
    if ((*linha)[0] == 'x' || (*linha)[0] == 'X') // ver se tem a variavel sem constante
    {
            (*linha)++;
        if (isdigit((*linha)[0]) == 1)
        {
            while (isdigit((*linha)[0]) == 1)
            (*linha)++;
        }
    }
    else if (isdigit((*linha)[0]) == 1) // ve se tem constante acompanhando variavel
    {
                while (isdigit((*linha)[0]) == 1) //pega todos os numeros
            (*linha)++;
        if ((*linha)[0] == 'x' || (*linha)[0] == 'X')
        {
            (*linha)++;
            if (isdigit((*linha)[0]) == 1)
            {
                while (isdigit((*linha)[0]) == 1)
            (*linha)++;
            }
        }
    }
    else
    {
        printf("Erro na validacao da variavel");
    }
}

int consomeSinal(char **linha)
{
    while ((*linha)[0] == ' ') //elimina espaços brancos
        (*linha)++;
    if((*linha)[0] == '+')
    {
        (*linha)++;
        return 1;
    }
    else if((*linha)[0] == '\n')
    {
        return 2;
    }
    else
    {
        printf("Erro ao consumir sinal");
        return 0;
    }
}