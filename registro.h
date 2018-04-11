#ifndef REGISTRO_H
#define REGISTRO_H

/*
 *  ESTRUTURAS
 */
typedef struct{
    int codINEP;
    char dataAtiv[10];
    char uf[2];
    char* nomEscola;
    char* municipio;
    char* prestadora;
} Registro;

/*
 *  FUNCOES
 */
FILE* cria_arquivo();

#endif
