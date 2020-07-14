#include "tokenizacao.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

int contaVariaveisDeFolga()
{
    FILE *arq = NULL;
    char caracter;
    int flag = 0;
    int contFolgas = 0;
    if ((arq = fopen("simplex.txt", "r")) != NULL)
    {
        while ((caracter = fgetc(arq)) != EOF)
        {
            if (caracter == '<')
            {
                flag++;
                if ((caracter = fgetc(arq)) != EOF)
                {
                    if (caracter == '=')
                    {
                        flag++;
                    }
                }
                if (flag == 2)
                {
                    contFolgas++;
                }
            }
            flag = 0;
        }
    }
    return contFolgas;
}
void verificaTokens(char *linha) // funcao chamada pra cada linha
{
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
                validaVariaveisFOByCopia(linha);
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
        validaRestricoesByCopia(linha);
    }
}


int validaVariaveisFOByCopia(char *linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    fprintf(arq, "%d ", 1);
    int tag = 1;
    int sucesso = 0;
    printf("%s", linha);
    do
    {
        if (consomeVariavelByCopia(linha) == 1) // retorna 1 se consumiu 10x1 por exemplo, 0 se não
        {
            consomeVariavelByReferencia(&linha);
            printf("Consumiu linha>%s", linha);
            if (consomeSinalByCopia(linha) == 1)
            {
                consomeSinalByReferencia(&linha);
                printf("Consumiu sinal>%s", linha);
                tag = 1;
            }
            else if (consomeSinalByCopia(linha) == 2)
            {
                consomeSinalByReferencia(&linha);
                printf("Validacao de linha concluida com sucesso\n");
                tag = 0;
                sucesso = 1;
            }
        }
        else
            tag = 0;
    } while (tag == 1);
    fclose(arq);
    return sucesso;
}


int validaRestricoesByCopia(char *linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    fprintf(arq, "%d ", 1);
    int tag = 1;
    int sucesso = 0;
    printf("%s", linha);
    do
    {
        if (consomeVariavelByCopia(linha) == 1) // retorna 1 se consumiu 10x1 por exemplo, 0 se não
        {
            consomeVariavelByReferencia(&linha);
            printf("Consumiu linha>%s", linha);
            if (consomeSinalByCopia(linha) == 1)
            {
                consomeSinalByReferencia(&linha);
                printf("Consumiu sinal>%s", linha);
                tag = 1;
            }
            else if (consomeSinalByCopia(linha) == 2)
            {
                consomeSinalByReferencia(&linha);
                printf("Validacao de linha concluida com sucesso\n");
                tag = 0;
                sucesso = 1;
            }
        }
        else
            tag = 0;
    } while (tag == 1);
    fclose(arq);
    return sucesso;
}

int consomeVariavelByCopia(char *linha)
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


int validaVariaveisByReferencia(char **linha)
{
    FILE *arq = fopen("matriz.txt", "a");
    fprintf(arq, "%d ", 1);
    int tag = 1;
    int sucesso = 0;
    printf("%s", (*linha));
    do
    {
        if (consomeVariavelByCopia((*linha)) == 1) // retorna 1 se consumiu 10x1 por exemplo, 0 se não
        {
            consomeVariavelByReferencia(&(*linha));
            printf("Consumiu linha>%s", (*linha));
            if (consomeSinalByCopia((*linha)) == 1)
            {
                consomeSinalByReferencia(&(*linha));
                printf("Consumiu sinal>%s", (*linha));
                tag = 1;
            }
            else if (consomeSinalByCopia((*linha)) == 2)
            {
                consomeSinalByReferencia(&(*linha));
                printf("Validacao de linha concluida com sucesso\n");
                tag = 0;
                sucesso = 1;
            }
        }
        else
            tag = 0;
    } while (tag == 1);
    fclose(arq);
    return sucesso;
}

int consomeVariavelByReferencia(char **linha)
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
            fprintf(arq, "-1 ");

            return 1;
        }
    }
    else if (isdigit((*linha)[0]) == 1) // ve se tem constante acompanhando variavel
    {
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
                return 1;
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
    return 1;
    fclose(arq);
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
    else
    {
        printf("Erro ao consumir sinal");
        return 0;
    }
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
    else
    {
        printf("Erro ao consumir sinal");
        return 0;
    }
}
