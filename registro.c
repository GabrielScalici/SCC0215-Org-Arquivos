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


///	Imprime todos os registros do arquivo de dados na saida padrao.
void recuperar_registros(FILE *f){
    f = fopen("turmaB-dadosPBLE.csv", "r");
    //Verificando se foi aberto corretamente
    if(!f){
      //Saida padrao para erros
      printf("Falha no processamento do arquivo.\n");
      //Fecha o programa
      exit(1);
    }

    Registro saida;
    int i = 1;///Variavel utilizada apenas para questao de formatacao da saida.
    char c;

    fseek(f, sizeof(int), SEEK_SET);///Pula o topo da Pilha.
    while(!feof(f)){
        //Sempro de char a char
        fread(&c, sizeof(char), 1, f);
        //Verificando se aquele registro nao foi removido de forma logica
        while(c == '*'){
            fseek(f, sizeof(Registro) - sizeof(char), SEEK_CUR);
            fread(&c, sizeof(char), 1, f);
            //Verifica se todos os arquivos foram removidos
            if(feof(f)){
            	printf("Todos os dados foram deletados .\n");
            	fclose(f);
            	return;
            }
        }
        //Caso nao seja removido logicamente
        fseek(f, -sizeof(char), SEEK_CUR);//Pula o topo da Pilha.
        fread(&saida, sizeof(Registro), 1, f);//Ler o registro
        //Verificando por medida de seguranca se nao ha registros
        if(feof(f)){
        	if(i == 1)
        		printf("Nao ha registros no arquivo.\n");
          break; //Nao precisa fechar o arquivo pois esta fechando quando sair do loop
        }
        //Caso nao tenha dado errros, entao exibe para o usuario
        printf("%d %s %s %d %s %d %s %d %s\n", saida.codINEP, saida.dataAtiv, saida.uf, strlen(saida.nomEscola), saida.nomEscola, strlen(saida.municipio), saida.municipio, strlen(saida.prestadora), saida.prestadora);

        //Atualizando para mostrar outros registros
        i++;
    }
    //Fecha o arquivo quando acabar todas as operacoes
    fclose(f);
}
