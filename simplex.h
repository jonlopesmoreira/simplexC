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
