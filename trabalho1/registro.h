#ifndef REGISTRO_H
#define REGISTRO_H

//Definindo o tamanho do registro
#define TAM_REG 87

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
    int tam_nomEscola;
    char* nomEscola;
    int tam_municipio;
    char* municipio;
    int tam_prestadora;
    char* prestadora;
} Registro;

/*
 *  FUNCOES
 */
FILE* cria_arquivo();
void verifica_arquivo(FILE *f);
void recuperar_registros(FILE *f);

#endif
