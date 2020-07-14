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