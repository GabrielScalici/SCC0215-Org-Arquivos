#ifndef REGISTRO_H
#define REGISTRO_H
#include <stdio.h>
//Definindo o tamanho do registro
#define TAM_REG 87
//Definindo o delimitador de campo
#define DEL_CAMPO 59

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
    char* dataAtiv;
    char* uf;
    int tamEscola;
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
Registro* recuperar_registros(FILE *f,int qtdRegs);
void transfere_arquivo(Registro* reg, int qtdRegs);
void busca_rrn(int RRN);
void remover_registro_rrn(int RRN);
void printa_arquivo();
void recupera_rrn();
void inserir_registro(int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest);
void atualizar_registro(int rrn, int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest);
void printa_arquivo_seletivo(char* campo, char* valor);

#endif
