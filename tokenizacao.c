#include "tokenizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

void verificaTokens(char *linha, int n) // funcao chamada pra cada linha
{
    FILE *arq = fopen("matriz.txt", "a");
    if (strnicmp(linha, "Max ", 4) == 0)
    {
        linha += 4;
        if (strnicmp(linha, "lucro ", 6) == 0)
        {
            linha += 6;
            if (strnicmp(linha, "= ", 2) == 0)
            {
                linha += 2;
                validaVariaveisFO(linha);
                if(n==0)
                {
                    for (int i = 0; i < contaVariaveisDeFolga() + 1; i++)
                    {
                        fprintf(arq, "0 ");
                    }
                    fprintf(arq, ";\n");
                    fclose(arq);
                }
            }
            else if (strnicmp(linha, "=", 1) == 0)
            {
                linha += 1;
            }
        }
        else if (strnicmp(linha, "lucro", 5) == 0)
        {
            linha += 5;
        }
        else
        {

        }
    }
    else
    {
        validaRestricoes(linha,n);
    }
}

int validaVariaveisFO(char *linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    fprintf(arq, "%d ", 1);
    fclose(arq);
    int tag = 1;
    int sucesso = 0;
    do
    {
        if (consomeVariavelFOByCopia(linha) == 1) // retorna 1 se consumiu 10x1 por exemplo, 0 se não
        {
            consomeVariavelFOByReferencia(&linha);
            if (consomeSinalByCopia(linha) == 1)
            {
                consomeSinalByReferencia(&linha);
                tag = 1;
            }
            else if (consomeSinalByCopia(linha) == 2)
            {
                consomeSinalByReferencia(&linha);
                tag = 0;
                sucesso = 1;
            }
        }
        else
            tag = 0;
    } while (tag == 1);
    return sucesso;
}

int consomeVariavelFOByReferencia(char **linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 1;
    }
    char numeros[200];
    int i = 0;
    while ((*linha)[0] == ' ') //elimina espaços brancos
        (*linha)++;
    if ((*linha)[0] == 'x' || (*linha)[0] == 'X') // ver se tem a variavel x mas sem constante
    {

        (*linha)++;
        if (isdigit((*linha)[0]) == 1)
        {
            while (isdigit((*linha)[0]) == 1)
                (*linha)++;
            fprintf(arq, "-1 "); // -1x2 -x3 -x4 -x123123 -x999
        }
    }
    else if (isdigit((*linha)[0]) == 1)   // ve se tem constante acompanhando variavel
    {                                     //   12x1  9x4  10x5  321x1
        while (isdigit((*linha)[0]) == 1) //pega todos os numeros
        {
            numeros[i++] = (*linha)[0];
            (*linha)++;
        }
        numeros[i] = '\0';
        fprintf(arq, "-%s ", numeros);
        if ((*linha)[0] == 'x' || (*linha)[0] == 'X') // pega a variavel x
        {
            (*linha)++;
            if (isdigit((*linha)[0]) == 1)
            {
                while (isdigit((*linha)[0]) == 1)
                {
                    (*linha)++;
                }
            }
        }
        else
        {
            printf("Erro nas variaveis da Funcao Objetivo na variavel de referencia");
            return 0;
        }
    }
    else
    {
        printf("Erro na validacao da variavel por referencia");
        return 0;
    }
    fclose(arq);
    return 1;
}

int consomeVariavelFOByCopia(char *linha)
{
    while (linha[0] == ' ') //elimina espaços brancos
        linha++;
    if (linha[0] == 'x' || linha[0] == 'X') // ver se tem a variavel x mas sem constante
    {
        linha++;
        if (isdigit(linha[0]) == 1)
        {
            while (isdigit(linha[0]) == 1)
                linha++;
            return 1;
        }
    }
    else if (isdigit(linha[0]) == 1) // ve se tem constante acompanhando variavel
    {
        while (isdigit(linha[0]) == 1) //pega todos os numeros
            linha++;
        if (linha[0] == 'x' || linha[0] == 'X') // pega a variavel x
        {
            linha++;
            if (isdigit(linha[0]) == 1)
            {
                while (isdigit(linha[0]) == 1)
                    linha++;
                return 1;
            }
        }
        else
        {
            printf("Erro nas variaveis da Funcao Objetivo por copia\n");
            return 0;
        }
    }
    else
    {
        printf("Erro na validacao da variavel por copia\n");
        return 0;
    }
    return 1;
}


int validaRestricoes(char *linha, int n)
{
    FILE *arq = fopen("matriz.txt", "a");
    int tag = 1;
    int sucesso = 0;
    fprintf(arq, "0 ");
    fclose(arq);
    do
    {
        if (consomeVariavelRestricoesByCopia(linha) == 1) // retorna 1 se consumiu 10x1 por exemplo, 0 se não
        {
            consomeVariavelRestricoesByReferencia(&linha);
            if (consomeSinalByCopia(linha) == 1)
            {
                consomeSinalByReferencia(&linha);
                tag = 1;
            }
            else if (consomeSinalByCopia(linha) == 2)
            {
                consomeSinalByReferencia(&linha);
                tag = 0;
                sucesso = 1;
            }
            else if(consomeSinalByCopia(linha)== 3)
            {
                vetorUnitario(n);
                if(consomeNumeroRestricoesByCopia(linha) == 1)
                {
                    consomeNumeroRestricoesByReferencia(&linha);
                }
                tag = 0;
                sucesso=1;
            }
        }
        else
            tag = 0;
    } while (tag == 1);
    return sucesso;
}

int consomeVariavelRestricoesByCopia(char *linha)
{
    while (linha[0] == ' ') //elimina espaços brancos
        linha++;
    if (linha[0] == 'x' || linha[0] == 'X') // ver se tem a variavel x mas sem constante
    {
        linha++;
        if (isdigit(linha[0]) == 1)
        {
            while (isdigit(linha[0]) == 1)
                linha++;
            return 1;
        }
    }
    else if (isdigit(linha[0]) == 1) // ve se tem constante acompanhando variavel
    {
        while (isdigit(linha[0]) == 1) //pega todos os numeros
            linha++;
        if (linha[0] == 'x' || linha[0] == 'X') // pega a variavel x
        {
            linha++;
            if (isdigit(linha[0]) == 1)
            {
                while (isdigit(linha[0]) == 1)
                    linha++;
                return 1;
            }
        }
        else
        {
            printf("Erro nas variaveis da Funcao Objetivo por copia");
            return 0;
        }
    }
    else
    {
        printf("Erro na validacao da variavel por copia");
        return 0;
    }
    return 1;
}
int consomeNumeroRestricoesByCopia(char *linha)
{
     while (linha[0] == ' ' || isdigit(linha[0]) != 1) //elimina espaços brancos
        linha++;
    if (isdigit(linha[0]) == 1)
    { 
        while (isdigit(linha[0]) == 1)
            linha++;
        return 1;
    }
    else
    {
        printf("Erro no vetor B");
        return 0;
    }
    return 1;
}
int consomeNumeroRestricoesByReferencia(char **linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    char numeros[200];
    int i=0;
    while ( (*linha)[0] == ' ' || isdigit((*linha)[0]) != 1) //elimina espaços brancos
        (*linha)++;
    if (isdigit((*linha)[0]) == 1)
    { 
        while (isdigit((*linha)[0]) == 1)
        {
            numeros[i++] = (*linha)[0];
            (*linha)++;
        }
        numeros[i] = '\0';
        fprintf(arq, "%s ", numeros);
        fprintf(arq, ";\n");
        fclose(arq);
        return 1;
    }
    else
    {
        printf("Erro no vetor B");
        fclose(arq);
        return 0;
    }
    fclose(arq);
    return 1;
}
int consomeVariavelRestricoesByReferencia(char **linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    if (arq == NULL)
    {
        printf("Erro na abertura do arquivo!");
        return 0;
    }
    char numeros[200];
    int i = 0;
    while ((*linha)[0] == ' ') //elimina espaços brancos
        (*linha)++;
    if ((*linha)[0] == 'x' || (*linha)[0] == 'X') // ver se tem a variavel x mas sem constante
    {

        (*linha)++;
        if (isdigit((*linha)[0]) == 1)
        {
            while (isdigit((*linha)[0]) == 1)
                (*linha)++;
            fprintf(arq, "1 "); // -1x2 -x3 -x4 -x123123 -x999
        }
    }
    else if (isdigit((*linha)[0]) == 1)   // ve se tem constante acompanhando variavel
    {                                     //   12x1  9x4  10x5  321x1
        while (isdigit((*linha)[0]) == 1) //pega todos os numeros
        {
            numeros[i++] = (*linha)[0];
            (*linha)++;
        }
        numeros[i] = '\0';
        fprintf(arq, "%s ", numeros);
        if ((*linha)[0] == 'x' || (*linha)[0] == 'X') // pega a variavel x
        {
            (*linha)++;
            if (isdigit((*linha)[0]) == 1)
            {
                while (isdigit((*linha)[0]) == 1)
                {
                    (*linha)++;
                }
            }
        }
        else
        {
            printf("Erro nas variaveis das restricoes na variavel de referencia");
            return 0;
        }
    }
    else
    {
        printf("Erro na validacao da variavel por referencia");
        return 0;
    }
    fclose(arq);
    return 1;
}

int consomeSinalByReferencia(char **linha) //1 se acha +, 2 se acha \n
{
    while ((*linha)[0] == ' ') //elimina espaços brancos
        (*linha)++;
    if ((*linha)[0] == '+')
    {
        (*linha)++;
        return 1;
    }
    else if ((*linha)[0] == '\n')
    {
        (*linha)++;
        return 2;
    }
    else if ((*linha)[0] == '<' )
    {
        (*linha)++;
        if((*linha)[0] == '=')
        {
            (*linha)++;
            return 3;
        }
    }
    else
    {
        printf("Erro ao consumir sinal");
        return 0;
    }
    return 0;
}
int consomeSinalByCopia(char *linha)
{
    while (linha[0] == ' ') //elimina espaços brancos
        linha++;
    if (linha[0] == '+')
    {
        linha++;
        return 1;
    }
    else if (linha[0] == '\n')
    {
        linha++;
        return 2;
    }
    else if (linha[0] == '<')
    {
        linha++;
        if(linha[0]=='=')
        {
            linha++;
            return 3;
        }
        
    }
    else
    {
        printf("Erro ao consumir sinal");
        return 0;
    }
    return 0;
}
