#ifndef REGISTRO_H
#define REGISTRO_H
#include <stdio.h>


//Definindo o tamanho do registro
#define TAM_REG 87
//Definindo o delimitador de campo
#define DEL_CAMPO 59
//Definições para verificação de arquivo
enum{
    CARREGANDO,
    RECUPERANDO
};
/*
 *  PARTE 1
 */

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
void verifica_arquivo(FILE *f, int func);
Registro* recuperar_registros(FILE *f,int qtdRegs);
void transfere_arquivo(Registro* reg, int qtdRegs);
void busca_rrn(int RRN);
void remover_registro_rrn(int RRN);
void printa_arquivo();
void recupera_rrn();
void inserir_registro(int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest);
void atualizar_registro(int rrn, int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest);
void busca_rrn_parametro(char* campo, char* valor);


/*
 *  PARTE 2
 */

 #define TAM_NO_INDICE 116
 #define TAM_BUFFER 5

 //Definindo o cabecalho do arquivo de arvore B
 typedef struct{
      char status;
      int noRaiz;
      int altura;
      int ultimoRRN;
 } Cabecalho_B;

 /*
  * N  = numero de registros na sub-arvore
  * P  = Ponteiro para a sub arvore
  * C  = Chave de busca
  * PR = Referencia para o arquivo de dados
  * Minimo de registros = 5
  * Maximo de registros = 10
 */
 //Definindo os nos da arvore B
 typedef struct{
     int n;
     int p[10];
     int c[9];
     int pr[9];
 } arvoreB; 

//Definindo a estrutura da bufferpool
typedef struct{
    arvoreB node[TAM_BUFFER];
    int RRN[TAM_BUFFER];         //Auxiliar para saber onde sera escrito no arquivo de indice
    int freq[TAM_BUFFER];
} bPool;

 /*
  *  FUNCOES
  */

//ArvoreB
FILE* criar_indice(Registro *reg, int qtdRegs);
void criar_arvore_B(Registro *reg, int qtdRegs);
void inserir_B(Registro reg, int RRN_reg, bPool *bp);
int ordena_no_B(arvoreB *node, Registro reg, int qtd);
void insere_naoCheio_B(int rrn_no, Registro reg, int RRN_reg, bPool *bp);

//Buffer pool
arvoreB *get(int RRN, bPool *bufPool);                  //Recupera o conteúdo de um nó
void put(int RRN, arvoreB* page, bPool *bufPool);       //Armazena página no buffer
void flush_full(bPool *bufPool);                        //Manda todas as páginas pro arquivo
void flush(arvoreB *page, bPool *bufPool);              //Manda uma página específica pro arquivo

#endif
