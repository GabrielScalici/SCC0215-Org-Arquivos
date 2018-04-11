#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"

/*
 *	Criar arquivo (caso não exista) e inserir o RRN do ultimo
 *  registro removido (PILHA).
*/
FILE* cria_arquivo(){
    // Leitura do arquivo
    FILE *f = fopen("turmaB-dadosPBLE.csv", "r");

    //Verificando se foi criado com sucesso
    if(!f){
      printf("Falha no carregamento do arquivo.\n");
      //Fecha o programa
      exit(1);
    }
    printf("Arquivo carregado.\n");

    fclose(f);
    return f;
}
