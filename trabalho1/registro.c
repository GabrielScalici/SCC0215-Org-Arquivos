/*
 *  TRABALHO DE ORGANIZAÇÃO DE ARQUIVOS
 *
 *  NOMES:                    NUMERO USP
 *  GABRIEL SCALICI           9292970
 *
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
FILE* cria_arquivo(){
    // Leitura do arquivo
    FILE *f = fopen("turmaB-dadosPBLE.csv", "rb");

    //Verificando se foi aberto corretamente
    verifica_arquivo(f);

    //Setar -1 no topo da pilha do cabecalho pois indica que nao teve remocao ainda
    int RRN_Rem = -1;
    //Setar 0 no status (Atualizar para 1 somente quando tudo tiver dado sucesso)
    int status = 0;

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



}
