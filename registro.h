#ifndef REGISTRO_H
#define REGISTRO_H

//Definicao do registro
typedef struct{
    int codINEP;
    char dataAtiv[10];
    char uf[2];
    char* nomEscola;
    char* municipio;
    char* prestadora;
} Registro;

#endif
