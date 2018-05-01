/*
 *  TRABALHO DE ORGANIZAÇÃO DE ARQUIVOS
 *
 *  NOMES:                      NUMERO USP
 *  GABRIEL SCALICI             9292970
 *  RODRIGO NOVENTA JR          9791243
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"


/*
    DISPOSICAO DOS CAMPOS NO ARQUIVO
    PRESTADORA, DATA, CODIGO, NOME_ESCOLA, MUNICIPIO ,UF

    DISPOSICAO QUE DEVE SER EXIBIDA AO USUARIO
    CODIGO, DATA, UF, (TAMANHO_NOME_ESCOLA), ESCOLA, (TAMANHO MUNICIPIO), MUNICIPIO, (TAMANHO PRESTADORA), PRESTADORA

    REGISTRO REMOVIDO: USAR SEEK_CUR
    RECUPERAR TODOS OS DADOS SEEK_SET
*/


/*
 *	Criar arquivo (caso não exista) e inserir o RRN do ultimo
 *  registro removido (PILHA).
*/
FILE* cria_arquivo(char *arquivo){
    FILE *f;
    
    f = fopen(arquivo, "rb");       //Abre o arquivo em modo de leitura binária
    verifica_arquivo(f);            //Verifica se o arquivo abriu corretamente

    printf("Arquivo carregado.\n"); 

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



}
