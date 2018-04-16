#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"


/*
    DISPOSICAO DOS CAMPOS NO ARQUIVO
    PRESTADORA, DATA, CODIGO, NOME_ESCOLA, MUNICIPIO ,UF

    REGISTRO REMOVIDO: USAR SEEK_CUR
    RECUPERAR TODOS OS DADOS SEEK_SET

*/


/*
 *	Criar arquivo (caso não exista) e inserir o RRN do ultimo
 *  registro removido (PILHA).
*/
FILE* cria_arquivo(){
    // Leitura do arquivo
    FILE *f = fopen("turmaB-dadosPBLE.csv", "rb");

    //Verificando se foi aberto corretamente
    verifica_arquivo(f);

    printf("Arquivo carregado.\n");
    fclose(f);
    return f;
}

//Funcao auxiliar para verificar se o srquivo foi aberto corretamente
void verifica_arquivo(FILE *f){
    if(!f){
        printf("Falha no carregamento do arquivo.\n");
        exit(1);
    }
}

//funcao para ler todos os registros
void recuperar_dados(FILE *f){
  x



}
