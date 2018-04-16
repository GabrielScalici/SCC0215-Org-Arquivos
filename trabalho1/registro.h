#ifndef REGISTRO_H
#define REGISTRO_H

/*
 *  ESTRUTURAS
 */
 //Definindo o cabecalho
 typedef struct{
      char status;
      int topoPilha;
 } Cabecalho;

//Definindo os registros
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
void verifica_arquivo(FILE *f);
void recuperar_registros(FILE *f);

#endif
