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

void vetorUnitario(int n)
{
    FILE *arq = fopen("matriz.txt", "a");
    int *vet = (int*) malloc(sizeof(int)*contaVariaveisDeFolga());
    for(int i=0; i<contaVariaveisDeFolga(); i++)
        vet[i] = 0;
    vet[n-1] = 1;
    for(int i=0; i<contaVariaveisDeFolga(); i++)
        fprintf(arq,"%d ", vet[i]);
    fclose(arq);
}