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

    //Cria com -1 para indicar que nenhum registro foi removido
    //int RRN_Rem = -1;
    //fwrite(&RRN_Rem, sizeof(int), 1, f);

    printf("Arquivo carregado.\n");

    fclose(f);
    return f;
}


///	Imprime todos os registros do arquivo de dados na saida padrao.
void recuperar_registros(FILE *f){
    f = fopen("turmaB-dadosPBLE.csv", "r");

    //Verificando se nao eh nulo
    if(!f){
      printf("Falha no carregamento do arquivo.\n");
      //Fecha o programa
      exit(1);
    }

    //PULAR O Cabecalho

    //Criando o registro de saida que sera exibido
    Registo saida;

    //Percorrendo todo arquivo ate o FAXINAL
    while(!feof(f)){


          
    }




    fclose(f);



}
