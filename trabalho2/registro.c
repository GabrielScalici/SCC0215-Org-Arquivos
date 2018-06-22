/*
 *  TRABALHO DE ORGANIZAÇÃO DE ARQUIVOS
 *
 *  NOMES:                      NUMERO USP
 *  GABRIEL SCALICI             9292970
 *  RODRIGO NOVENTA JR          9791243
 *	EDUARDO ALVES BARATELA      10295270
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registro.h"
#include <limits.h>


/*
    DISPOSICAO DOS CAMPOS NO ARQUIVO
    PRESTADORA, DATA, CODIGO, NOME_ESCOLA, MUNICIPIO ,UF
    DISPOSICAO QUE DEVE SER EXIBIDA AO USUARIO
    CODIGO, DATA, UF, (TAMANHO_NOME_ESCOLA), ESCOLA, (TAMANHO MUNICIPIO), MUNICIPIO, (TAMANHO PRESTADORA), PRESTADORA
    REGISTRO REMOVIDO: USAR SEEK_CUR
    RECUPERAR TODOS OS DADOS SEEK_SET
*/


/*
 *  Criar arquivo (caso não exista) e inserir o RRN do ultimo
 *  registro removido (PILHA).
*/
FILE* cria_arquivo(char *arquivo){
    FILE *f;

    f = fopen(arquivo, "rb");       //Abre o arquivo em modo de leitura binária
    verifica_arquivo(f, CARREGANDO);            //Verifica se o arquivo abriu corretamente

    printf("Arquivo carregado.\n");

    return f;
}

//Funcao auxiliar para verificar se o srquivo foi aberto corretamente
void verifica_arquivo(FILE *f, int func){
    if(!f){
        if(func == 0)   printf("Falha no carregamento do arquivo.\n");
        if(func == 1)   printf("Falha no processamento do arquivo.\n");
        exit(1);
    }
}

//funcao para ler todos os registros e alocar na RAM
Registro *recuperar_registros(FILE *f, int qtdRegs){
    int tam;
    int alternando = 0, qtd = 0, i=0;
    char c;
    Registro *reg;

    //Aloca a quantidade de memória necessária
    reg = (Registro *) calloc(qtdRegs, sizeof(Registro));

    while(1){
        char* carac= (char*)calloc(80, sizeof(char));
        do{
            c= fgetc(f);
            if(c != ';' && c != '\n' && c != EOF){
                carac[i] = c ;//string temporaria para pegar os registros
                i++;
            }
        } while (c != ';' && c != '\n' && c != EOF );
        carac[i] = '\0';

        if(i > 0){    //caso o campo nao esteja preenchido
            if(alternando == 0){//colocando no campos campos prestadora e tam_prestadora
                reg[qtd].tam_prestadora = i;
                reg[qtd].prestadora = (char*) malloc(sizeof(char)*(strlen(carac)));
                strncpy(reg[qtd].prestadora, carac,strlen(carac));
                alternando=1;
            }
            else if(alternando == 1){//colocando no campo de dataAtiv
                reg[qtd].dataAtiv = (char*) malloc(sizeof(char)*10);
           		strncpy(reg[qtd].dataAtiv, carac,10);
                alternando=2;
            }
            else if(alternando == 2){//colocando no campo de codINEP
                reg[qtd].codINEP = atoi(carac);
                alternando=3;
            }
            else if(alternando == 3){//colocando nos campos nomEscola e tam_nomEscola
                reg[qtd].tamEscola = i;
                reg[qtd].nomEscola = (char*) malloc(sizeof(char)*(strlen(carac)));
                strncpy(reg[qtd].nomEscola, carac, strlen(carac));
                alternando=4;
            }
            else if(alternando == 4){//colocando nos campos municipio e tam_municipio
                reg[qtd].municipio= (char*) malloc(sizeof(char)*(strlen(carac)));
                strncpy(reg[qtd].municipio, carac,strlen(carac));
                reg[qtd].tam_municipio = strlen(carac);
                alternando=5;
            }
            else if(alternando == 5){//colocando no campo de uf
                reg[qtd].uf = (char*) malloc(sizeof(char)*2);
                strncpy(reg[qtd].uf, carac,2);
               // strncpy(reg[qtd].uf, carac,2);
                qtd++;
                alternando=0;
            }
        }
        else {
        	if(alternando == 1 && carac[0]== '\0'){
        		reg[qtd].dataAtiv = (char*) malloc(sizeof(char)*10);
        		strncpy(reg[qtd].dataAtiv,"0000000000",10);
        	}
            else if(alternando == 5 && carac[0]== '\0'){
                reg[qtd].uf = (char*) malloc(sizeof(char)*2);
            	strncpy(reg[qtd].dataAtiv,"00",2);
            }
            else if(alternando == 0)reg[qtd].tam_prestadora = 0;
            else if(alternando == 3)reg[qtd].tamEscola = 0;
            else if(alternando == 4)reg[qtd].tam_municipio = 0;
         	alternando++;  //se houver um campo sem informacao pula para o proximo campo
		}
        //criar uma nova string temp, para pegar o valor do proximo campo
            free(carac);
            i = 0;

        if(feof(f)) break; //ou c == EOF (?)
    }

    fclose(f);  //Tira o arquivo da memória
    return reg;
}

//funcao pra tranferir os registros para o arquivo de saida ja com o cabecalho
void transfere_arquivo(Registro* reg, int qtdRegs){
    FILE* f;
    int tamAtual;
    char c = '0';
    f = fopen("teste.bin", "wb");
    verifica_arquivo(f, CARREGANDO);

    //Cria um cabecalho auxiliar
    Cabecalho cab;
    cab.status = '1';          //consistente
    cab.topoPilha = -1;      //pilha vazia por enquanto

    //Escreve o cabecalho no arquivo
    fwrite(&cab.status, sizeof(char), 1, f);
    fwrite(&cab.topoPilha,sizeof(int),1,f);
    printf("%c \n",cab.status);
    printf("%d \n",cab.topoPilha);


    //Escreve todos os registros no arquivo na ordem correta
    for (int i = 0; i < qtdRegs; ++i){
        fwrite(&reg[i].codINEP,sizeof(int),1,f);
        fwrite(reg[i].dataAtiv,sizeof(char),10,f);
        fwrite(reg[i].uf,sizeof(char),2,f);
        fwrite(&reg[i].tamEscola,sizeof(int),1,f);
        fwrite(reg[i].nomEscola,reg[i].tamEscola,1,f);
        fwrite(&reg[i].tam_municipio,sizeof(int),1,f);
        fwrite(reg[i].municipio,reg[i].tam_municipio,1,f);
        fwrite(&reg[i].tam_prestadora,sizeof(int),1,f);
        fwrite(reg[i].prestadora,reg[i].tam_prestadora,1,f);

       /*Testando no terminal as variaves
        printf("%d ", reg[i].codINEP);
        printf("%s ", reg[i].dataAtiv);
        printf("%s ", reg[i].uf);
        printf("%d-", reg[i].tamEscola);
        printf("%s ", reg[i].nomEscola);
        printf("%d-", reg[i].tam_municipio);
        printf("%s ", reg[i].municipio);
        printf("%d-", reg[i].tam_prestadora);
        printf("%s \n", reg[i].prestadora);

       */
        tamAtual = (((28 + reg[i].tamEscola) + reg[i].tam_municipio) + reg[i].tam_prestadora);
        if(tamAtual < TAM_REG){
        	for(int i =0; i< (TAM_REG - tamAtual);i++)fwrite(&c,sizeof(char),1,f);
        }
       // fwrite(&reg[i],TAM_REG, 1, f);
    }

    fclose(f);
}

void busca_rrn(int RRN){
    char status = '0';
    //Abrindo o arquivo e verificando sua condição
    FILE *f = fopen("teste.bin", "rb");
    verifica_arquivo(f, RECUPERANDO);

    //Alterar o status
    fwrite(&status, sizeof(char), 1, f);

    //Variavies para exibicao dos CAMPOS
    int cod;
    char data[11];
    char uf[3];
    int tam_escola;
    char* nome_escola;
    int tam_mun;
    char* muni;
    int tam_prest;
    char* prest;

    //Arrumando strings para exibicao
    data[10] = '\0';
    uf[2] = '\0';

    //Pular o status e topo da pilha
    fseek(f, 5, SEEK_SET);

    ///Vai para o RRN desejado
    fseek(f, RRN * 87, SEEK_CUR);

    //Lendo o primeiro caracter e analisando se o registro foi removido
    int rem;
    fread(&rem , sizeof(int), 1, f);
    if((rem == -1) || (feof(f))){
        ///Arquivo removido ou RRN não existe
        printf("\nRegistro inexistente.\n");
        status = 1;
        //Voltando para atualizar o status
        fseek(f, 0, SEEK_SET);
        fwrite(&status, sizeof(char), 1, f);
        fclose(f);
        return;
    }
    else{
        //Retorna para a posição no início do registro
        fseek(f, -sizeof(int), SEEK_CUR);

        //Lendo Campo por campo do registro
          fread(&cod, sizeof(int), 1, f);
          printf("%d ", cod);
          fread(data, sizeof(char), 10, f);
          printf("%s ", data);
          fread(uf, sizeof(char), 2, f);
          printf("%s ", uf);
          fread(&tam_escola, sizeof(int), 1, f);
          printf("%d ", tam_escola);
          nome_escola = (char*) malloc(sizeof(char)*(tam_escola)+1);
          nome_escola[tam_escola] = '\0';
          fread(nome_escola, tam_escola, 1, f);
          printf("%s ", nome_escola);
          fread(&tam_mun, sizeof(int), 1, f);
          printf("%d ", tam_mun);
          muni = (char*) malloc(sizeof(char)*(tam_mun)+1);
          muni[tam_mun] = '\0';
          fread(muni, tam_mun, 1, f);
          printf("%s ", muni);
          fread(&tam_prest, sizeof(int), 1, f);
          printf("%d ", tam_prest);
          prest = (char*) malloc(sizeof(char)*(tam_prest)+1);
          prest[tam_prest] = '\0';
          fread(prest, tam_prest, 1, f);
          printf("%s\n", prest);

    }

    status = 1;
    //Voltando para atualizar o status
    fseek(f, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, f);
    fclose(f);

}

void remover_registro_rrn(int RRN){
    int status = 0;

    //Abrindo o arquivo
    FILE *f = fopen("teste.bin", "r+b");
    verifica_arquivo(f, RECUPERANDO);

    //Alterar o status
    fwrite(&status, sizeof(char), 1, f);

    //Variaveis auxiliares
    int rrn_topo_pilha;
    int remover = -1;

    //Le o RRN no topo da pilha.
    fread(&rrn_topo_pilha, sizeof(int), 1, f);

    ///Vai para o RRN desejado
    fseek(f, RRN * 87, SEEK_CUR);

    //Lendo o primeiro inteiro e analisa se o registro foi removido
    int rem;
    fread(&rem , sizeof(int), 1, f);
    if((rem == -1) || (feof(f))){
        ///Arquivo removido ou RRN não existe
        printf("\nRegistro inexistente.\n");
        status = 1;
        //Voltando para atualizar o status
        fseek(f, 0, SEEK_SET);
        fwrite(&status, sizeof(char), 1, f);
        fclose(f);
        return;
    }else{

        //Retorna para a posição no início do registro
        fseek(f, -sizeof(int), SEEK_CUR);

        //Armazenando na variavel auxiliar o valor para indicar remoção logica
        fwrite(&remover, sizeof(int), 1, f);

        //Atualizando os valores da pilha com o removido
        fwrite(&rrn_topo_pilha, sizeof(int), 1, f);

        //Atualizar o topo da pilha com o valor desse RRN
        fseek(f, 0, SEEK_SET);

        //Pular o status do cabecalho e atualiza o topo da pilha
        fseek(f, sizeof(char), SEEK_SET);

        //Escrever no topo da pilha
        fwrite(&RRN, sizeof(int), 1, f);

        //Indicando para o usuário que foi removido com sucesso
        printf("Registro removido com sucesso.\n");
    }


    status = 1;
    //Voltando para atualizar o status
    fseek(f, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, f);
    fclose(f);
}
void printa_arquivo(){
    FILE *f;
    Cabecalho cab;
    Registro reg;
    int i = 0;
    //int aux;

    f = fopen("teste.bin", "r+b");  //Abre o arquivo
    verifica_arquivo(f, RECUPERANDO);            //Verifica o arquivo

    //Lê o cabeçalho
    fread(&cab.status, sizeof(char), 1, f);
    fread(&cab.topoPilha, sizeof(int), 1, f);

    if(cab.status == '0'){  //Significa que o arquivo de dados está inconsistente
        //printf("Falha no processamento do arquivo.\n");   //Coloca mesmo?
        exit(-1);
    }

    fseek(f, 0, SEEK_SET);                      //Volta pro início do arquivo
    cab.status = '0';                           //Novo status do arquivo
    fwrite(&cab.status, sizeof(char), 1, f);    //Escreve o novo status do arquivo

    //Posição do primeiro registro
    fseek(f, 5, SEEK_SET);

    // printf("%c\t%d\n", cab.status, cab.topoPilha);

    while(!feof(f)){
        fread(&reg.codINEP, sizeof(int), 1, f);
        //Quebra a execução se já for o fim do arquivo
        //Tem que ocorrer após a primeira leitura do arquivo
        if(feof(f)) break;
        printf("%d ", reg.codINEP);

        reg.dataAtiv = (char *) calloc(10, sizeof(char));
        fread(reg.dataAtiv, sizeof(char), 10, f);
        printf("%s ", reg.dataAtiv);
        free(reg.dataAtiv);

        reg.uf = (char *) calloc(2, sizeof(char));
        fread(reg.uf, sizeof(char), 2, f);
        printf("%s ", reg.uf);
        free(reg.uf);

        fread(&reg.tamEscola, sizeof(int), 1, f);
        reg.nomEscola = (char *) calloc(reg.tamEscola + 1, sizeof(char));
        fread(reg.nomEscola, reg.tamEscola * sizeof(char), 1, f);
        reg.nomEscola[reg.tamEscola] = '\0';
        printf("%d %s ", reg.tamEscola, reg.nomEscola);
        free(reg.nomEscola);

        fread(&reg.tam_municipio, sizeof(int), 1, f);
        reg.municipio = (char *) calloc(reg.tam_municipio + 1, sizeof(char));
        fread(reg.municipio, reg.tam_municipio * sizeof(char), 1, f);
        reg.municipio[reg.tam_municipio] = '\0';
        printf("%d %s ", reg.tam_municipio, reg.municipio);
        free(reg.municipio);

        fread(&reg.tam_prestadora, sizeof(int), 1, f);
        reg.prestadora = (char *) calloc(reg.tam_prestadora + 1, sizeof(char));
        fread(reg.prestadora, reg.tam_prestadora * sizeof(char), 1, f);
        reg.prestadora[reg.tam_prestadora] = '\0';
        printf("%d %s\n", reg.tam_prestadora, reg.prestadora);
        free(reg.prestadora);

        i++;
        fseek(f, (TAM_REG * i) + 5, SEEK_SET);
    }

    fseek(f, 0, SEEK_SET);
    cab.status = '1';
    fwrite(&cab.status, sizeof(char), 1, f);

    fclose(f);

    return;
}

void recupera_rrn(){
  int status = 0;

  //Abrindo o arquivo
  FILE *f = fopen("teste.bin", "r+b");
  verifica_arquivo(f, RECUPERANDO);

  //Alterar o status
  fwrite(&status, sizeof(char), 1, f);

  //Variaveis auxiliares
  int rrn_topo_pilha;
  int rrn_prox_pilha;

  //Le o RRN no topo da pilha.
  fread(&rrn_topo_pilha, sizeof(int), 1, f);

  if(rrn_topo_pilha != -1){

    rrn_prox_pilha = rrn_topo_pilha;

    do{
      //Printa o primeiro rrn removido
      printf("%d ", rrn_prox_pilha);

      ///Vai para o RRN desejado
      fseek(f, (rrn_prox_pilha * 87) + 5, SEEK_SET);

      //Pular o primeiro valor que indica que foi removido
      fseek(f, sizeof(int), SEEK_CUR);

      //Pegar o proximo item na pilha
      fread(&rrn_prox_pilha, sizeof(int), 1, f);

      //Enquanto nao encontrar o fim (nao exibir -1)
    }while(rrn_prox_pilha != -1);

    printf("\n");

  }else{
    printf("Pilha vazia.");
  }

  status = 1;
  //Voltando para atualizar o status
  fseek(f, 0, SEEK_SET);
  fwrite(&status, sizeof(char), 1, f);
  fclose(f);

}

void inserir_registro(int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest){
  int status = 0;

  //Abrindo o arquivo
  FILE *f = fopen("teste.bin", "r+b");
  verifica_arquivo(f, RECUPERANDO);

  //Alterar o status
  fwrite(&status, sizeof(char), 1, f);

  int rrn_topo_pilha;
  int aux_prox_rrn;

  //Le o RRN no topo da pilha.
  fread(&rrn_topo_pilha, sizeof(int), 1, f);

  //Checando se ha algum registro REMOVIDO
  if(rrn_topo_pilha == -1){
      //Caso nao tenha removido nenhum, adicionar no final do arquivo
      fseek(f, 0, SEEK_END);
  }
  else{
      //Caso haja um removido, va para ele
      fseek(f, rrn_topo_pilha * 87, SEEK_CUR);

      //Pular o primeiro valor que indica que foi removido
      fseek(f, sizeof(int), SEEK_CUR);

      //Salvar o proximo removido para atualizar o topo da pilha
      fread(&aux_prox_rrn, sizeof(int), 1, f);

      //Voltar para o topo pilha no cabecalho
      fseek(f, 1 , SEEK_SET);

      //Atualizando o topo da pilha
      fwrite(&aux_prox_rrn, sizeof(int), 1, f);

      //Ir para o registro certo novamente
      fseek(f, rrn_topo_pilha * 87, SEEK_CUR);

    }

    int tam_nome_esc = strlen(nome_esc);
    int tam_muni = strlen(muni);
    int tam_prest = strlen(prest);

    //Adicionar o novo registro
    fwrite(&cod, sizeof(int), 1, f);
    fwrite(data, sizeof(char), 10, f);
    fwrite(uf, sizeof(char), 2, f);
    fwrite(&tam_nome_esc, sizeof(int), 1, f);
    fwrite(nome_esc, sizeof(char), tam_nome_esc, f);
    fwrite(&tam_muni, sizeof(int), 1, f);
    fwrite(muni, sizeof(char), tam_muni, f);
    fwrite(&tam_prest, sizeof(int), 1, f);
    fwrite(prest, sizeof(char), tam_prest, f);

    printf("Registro inserido com sucesso.\n");

    //Atualizando o status
    status = 1;
    //Voltando para atualizar o status
    fseek(f, 0, SEEK_SET);
    fwrite(&status, sizeof(char), 1, f);
    fclose(f);

}

void atualizar_registro(int rrn, int cod, char data[10], char uf[2], char* nome_esc, char* muni, char* prest){
  int status = 0;

  //Abrindo o arquivo
  FILE *f = fopen("teste.bin", "r+b");
  verifica_arquivo(f, RECUPERANDO);

  //Alterar o status
  fwrite(&status, sizeof(char), 1, f);

  //Pular topo da pilha
  fseek(f, sizeof(int), SEEK_CUR);

  //Buscar o RRN a ser atualizado
  fseek(f, rrn * 87, SEEK_CUR);

  //Lendo o primeiro inteiro e analisa se o registro foi removido
  int rem;
  fread(&rem , sizeof(int), 1, f);
  if((rem == -1) || (feof(f))){
      ///Arquivo removido ou RRN não existe
      printf("\nRegistro inexistente.\n");
      status = 1;
      //Voltando para atualizar o status
      fseek(f, 0, SEEK_SET);
      fwrite(&status, sizeof(char), 1, f);
      fclose(f);
      return;
  }else{

    //Retorna para a posição no início do registro
    fseek(f, -sizeof(int), SEEK_CUR);

    //Pegando os tamanhos dos campos variaveis
    int tam_nome_esc = strlen(nome_esc);
    int tam_muni = strlen(muni);
    int tam_prest = strlen(prest);

    //Adicionar o novo registro
    fwrite(&cod, sizeof(int), 1, f);
    fwrite(data, sizeof(char), 10, f);
    fwrite(uf, sizeof(char), 2, f);
    fwrite(&tam_nome_esc, sizeof(int), 1, f);
    fwrite(nome_esc, sizeof(char), tam_nome_esc, f);
    fwrite(&tam_muni, sizeof(int), 1, f);
    if(tam_muni == 0){

    }
    fwrite(muni, sizeof(char), tam_muni, f);
    fwrite(&tam_prest, sizeof(int), 1, f);
    fwrite(prest, sizeof(char), tam_prest, f);

    printf("Registro alterado com sucesso.\n");
  }
  //Atualizando o status
  status = 1;
  //Voltando para atualizar o status
  fseek(f, 0, SEEK_SET);
  fwrite(&status, sizeof(char), 1, f);
  fclose(f);

}


//funcao 3
void busca_rrn_parametro(char* campo, char* valor){
    FILE *f;
    Cabecalho cab;
    Registro *reg = NULL;
    int i = 0;
    int qtd;
    //Variavies para exibicao dos CAMPOS
    int cod;
    char data[11];
    char uf[3];
    int tam_escola;
    char* nome_escola;
    int tam_mun;
    char* muni;
    int tam_prest;
    char* prest;

    f = fopen("teste.bin", "r+b");

    verifica_arquivo(f, RECUPERANDO);    //Verifica se carregou o arquivo
    printf("Arquivo aberto\n");

	fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro


	if(strcmp(campo, "codINEP")==0){
		//Leitura de todos os registros
		while(!feof(f)){
			if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro

      	 	//Andando pelo registro até chegar no campo codINEP
      	 	fseek(f,(i*87),SEEK_CUR);

		    if(cod == atoi(valor))busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		    i++;
		}
	}
	else if(strcmp(campo, "dataAtiv")==0){
		//Leitura de todos os registros
		while(!feof(f)){
		    if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro
      	 	fseek(f,((i*87)+4),SEEK_CUR);

      	 	//Andando pelo registro até chegar no campo dataAtiv
          	fread(data, sizeof(char), 10, f);

		    if(strcmp(data,valor)==0)busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		    i++;
		}
	}
	else if(strcmp(campo, "uf")==0){
		//Leitura de todos os registros
		while(!feof(f)){
			if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro
      	 	fseek(f,((i*87)+14),SEEK_CUR);

      	 	//Andando pelo registro até chegar no campo UF
	        fread(uf, sizeof(char), 2, f);

		    if(strcmp(uf,valor)==0)busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		    i++;
		}
	}
	else if(strcmp(campo, "nomeEscola")==0){
		//Leitura de todos os registros
		while(!feof(f)){
		    if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro
      	 	fseek(f,((i*87)+16),SEEK_CUR);

      	 	//Andando pelo registro até chegar no campo nomeEscola
          	fread(&tam_escola, sizeof(int), 1, f);
          	nome_escola = (char*) malloc(sizeof(char)*(tam_escola)+1);
    	    nome_escola[tam_escola] = '\0';
    	    fread(nome_escola, tam_escola, 1, f);

		    if(strcmp(nome_escola,valor)==0)busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		    i++;
		}
	}
	else if(strcmp(campo, "municipio")==0){
		//Leitura de todos os registros
		while(!feof(f)){
			if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro
      	 	fseek(f,((i*87)+16),SEEK_CUR);

          	//Andando pelo registro até chegar no campo municipio
          	fread(&tam_escola, sizeof(int), 1, f);
          	fseek(f,tam_escola,SEEK_CUR);
          	fread(&tam_mun, sizeof(int), 1, f);
          	muni = (char*) malloc(sizeof(char)*(tam_mun)+1);
          	muni[tam_mun] = '\0';
         	fread(muni, tam_mun, 1, f);

		    if(strcmp(muni,valor)==0)busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		  	i++;
		}
	}
	else if(strcmp(campo, "prestadora")==0){
		//Leitura de todos os registros
		while(!feof(f)){
			if(i>0)fseek(f,5,SEEK_SET);//posicionando o ponteiro pro primeiro registro
      	 	fseek(f,(i*87)+16,SEEK_CUR);

          	//Andando pelo registro até chegar no campo prestadora
          	fread(&tam_escola, sizeof(int), 1, f);
			fseek(f,tam_escola,SEEK_CUR);
          	fread(&tam_mun, sizeof(int), 1, f);
          	fseek(f,tam_mun,SEEK_CUR);
          	fread(&tam_prest, sizeof(int), 1, f);
          	prest = (char*) malloc(sizeof(char)*(tam_prest)+1);
          	prest[tam_prest] = '\0';
          	fread(prest, tam_prest, 1, f);

		    if(strcmp(prest,valor)==0)busca_rrn(i);//chama a funcao pra printar o registro que satisfaz
		    i++;
		}
	}

    fclose(f);  //Fecha o arquivo
}

/* *********************
********* T2 ***********
********************** */

//Indice
FILE* criar_indice(Registro *reg, int qtdRegs){
    FILE* b;

    //Criando o arquivo de indices chamado de (arvoreB.bin)
    b = fopen("arvoreB.bin", "wb");
    verifica_arquivo(b, CARREGANDO);

    //Criando o cabecalho arvore B chamado (arvoreB.bin)
    criar_arvore_B(reg, qtdRegs);

    return b;
}

//Funcao para carregar o arquivo de arvore B
void criar_arvore_B(Registro *reg, int qtdRegs){
    FILE *b;
    bPool *bp;  //Tem que ver se é *bp ou só bp (dai passa & nas funcoes)
    arvoreB *root = NULL;
    int tamAtual = 0;       //Numero de nós na árvore
    int i, j = 0;

    b = fopen("arvoreB.bin", "w+b");

    //Cria um cabecalho auxiliar
    Cabecalho_B cab;
    cab.status = '1';           //consistente
    cab.noRaiz = -1;            //Arvore vazia por enquanto
    cab.altura = 0;
    cab.ultimoRRN = -1;

    //Escreve o cabecalho no arquivo
    fseek(b, 0, SEEK_SET);
    fwrite(&cab.status, sizeof(char), 1, b);
    fwrite(&cab.noRaiz,sizeof(int),1,b);
    fwrite(&cab.altura,sizeof(int),1,b);
    fwrite(&cab.ultimoRRN,sizeof(int),1,b);
    printf("cab.status %c\n", cab.status);
    printf("cab.noRaiz %d\n", cab.noRaiz);
    printf("cab.altura %d\n", cab.altura);
    printf("cab.ultimoRRN %d\n", cab.ultimoRRN);

    fclose(b);

    //Inicializando a ArvoreB
    root = (arvoreB *) realloc(root, sizeof(arvoreB) * (tamAtual + 1));
    tamAtual++; //=1
    root[0].n = 0;
    for(i = 0;i < 9;i++){
        root[0].p[i] = -1;
        root[0].c[i] = -1;
        root[0].pr[i] = -1;
    }

    //Inicializando o buffer pool
    bp = (bPool *) calloc(1, sizeof(bPool));
    for(i = 0;i < TAM_BUFFER;i++){
        bp->RRN[i] = -1;
        bp->freq[i] = 0;
    }
 
    //insere todos os registros do arquivo de dados no arquivo de indices
    for(int i = 0; i < qtdRegs; i++){
        //printf("%d\t%d\n", i, reg[i].codINEP);

        
    }
/*
    //-----------------SÓ PRA TESTAR-----------------------
    b = fopen("arvoreB.bin", "rb");
    fseek(b, 13 + 4 + 4 + 4, SEEK_SET);
    int resp;
    fread(&resp, sizeof(int), 1, b);
    printf("RESP = %d\n", resp); */
}

void inserir_B(Registro reg, int RRN_reg, bPool *bp){
/*
    Pseudocódigo Cormen:

    B-TREE-INSERT(k, T){ //k = nova chave, T = Arvore B
            if(n[raiz]==9){
                aloca novaRaiz	//no nosso caso seria achar o proximo espaço vazio no arquivo
                cab.raiz = novaRaiz	//atualiza o cabeçalho
                n[novRaiz] = 0
                p1[novaRaiz] = raiz(antiga)
                SPLIT(novaRaiz, 5, raiz(antiga))
                B-TREE-INSERT-NONFULL(raiz, k)
            }
            else B-TREE-INSERT-NONFULL(raiz, k)
    }
    */
}

int ordena_no_B(arvoreB *node, Registro reg, int qtd){
	int i = qtd;

    while(i >= 0 && reg.codINEP < node->c[i]){
        node->p[i] = node->p[i-1];
        node->c[i] = node->c[i-1];
        node->pr[i] = node->pr[i-1];
        i--;
    }

    printf("i = %d\n", i);

    for (int j = 0; j <= qtd; j++){
      printf("node->p[%d] = %d\n", j, node->p[j]);
      printf("node->c[%d] = %d\n", j, node->c[j]);
      printf("node->pr[%d] = %d\n", j, node->pr[j]);
    }

    return i;
}

void insere_naoCheio_B(int rrn_no, Registro reg, int RRN_reg, bPool *bp){
  /*
  B-TREE-INSERT-NONFULL(x, k){ //x = nó, k = nova chave
        i = n[x]
        if(p1[x] == -1){ //se p1 for nulo, ou seja, se o nó for uma folha
        while(i>=0 && k<ci[x]){
            ci+1[x] = ci[x] //no nosso caso é escrever tudo 4 bytes pra frente(incluindo c, pr e p)
            i--
        }
        ci+1[x] = k
        n[x]++
        }
        else{
        while(i>=0 && k<ci[x])
            i--
        i++
        FSEEK(pi[x]) //pula até o filho do no x no arquivo de indice
        if(n[pi[x]] == 9){
            SPLIT(x, i+1, pi[x])
            if(k > ci[x]) i++ (?)
        }
        B-TREE-INSERT-NONFULL(pi[x], k) //recursao até chegar em um nó folha
        }
    }
  */
}

//Funcao de split para a insercao na arvore B
void split_B(){
  /*
  SPLIT(no pai, i, no filhoCheio){
         aloca novoNo //aloca no ultimoRRN+1
          n[novoNo] = 4

          for(j = 0; j++; j<4){}
              cj[novoNo] = cj+5[filhoCheio]
              prj[novoNo] = prj+5[filhoCheio]
          }

          if(p0[filhoCheio] != -1){ //checa se nao é no folha
            for(j=0; j++; j<5)
              pj[novoNo] = pj+5[filhoCheio]
          }
          n[filhoCheio] = 4

          for(j=n[pai]; j--; j <=i){  //ordena os ponteiros do no pai até o espaco do novo ponteiro
            pj+1[pai] = pj[pai]
          }
          //atençao que é i e nao j aqui embaixo
          pi[pai] = rrn de novoNo  //(nosso caso será o ultimoRRN)

          for(j = n[pai]-1; j--; j<i)
            cj+1[pai] = cj[pai]
            prj+1[pai] = prj[pai]
          }
          ci-1[pai] = c4[filhoCheio]
          pri-1[pai] = pr4[filhoCheio]

          n[pai]++

          ESCREVE(novoNo)
          ESCREVE(pai)
          ESCREVE(filhoCheio)
        }
  */

}

void pesquisa_B(){
  /*
    PESQUISA(no x, int k){
      int i = 0

      FSEEK PULANDO CABECALHO
      FSEEK x*TAMANHO_INDICE

      fread(n[x])
      fread[p[0]]
      fread(c[0])
      fread(pr[0])
      while(i<n[x] && k > c[i]){
        i++
        fread[p[i]]
        fread(c[i])
        fread(pr[i])
      }
      fread[p[i]]

      if(i<n[x] && k == c[i]){
        busca(c[i] ou pr[i]) //busca essa chave no arquivo de dados
        return
      }

      if(p[0] == -1){
        printf(nao encontrado)
        return
      }
      else PESQUISA(p[i], k);
    }
  */
}


/*
 * BUFFER POOL
 */

arvoreB* get(int RRN, bPool *bufPool){

    //if esta no bufferpool
        //1: copie o conteúdo da página requerida para uma variável auxiliar do tipo arvoreB, chamada P
        //2: realize possíveis restruturações na organização do buffer (LFU)
        //3: retorne P

    //else nao esta no buffer
        //1: recupere o conteúdo da página do disco e armazena em uma variável auxiliar do tipo IndexPage, chamada P
        //2: insira P no buffer, chamando a função put
        //3: retorne P.

    arvoreB *aux;
    int i, j;
    FILE *b;

    aux = (arvoreB *) calloc(1, sizeof(arvoreB));

    //Página está no buffer
    for(i = 0;i < TAM_BUFFER;i++){          //Procura no buffer pelo RRN do nó
        if(bufPool->RRN[i] == RRN){         //RRN está no buffer
            aux->n = bufPool->node[i].n;    
            for(j = 0;j < bufPool->node[i].n;j++){        //Roda por todos os registros do nó
                //Copia todo o conteudo do nó que está no buffer para uma auxiliar 
                aux->p[j] = bufPool->node[i].p[j];
                aux->c[j] = bufPool->node[i].c[j];
                aux->pr[j] = bufPool->node[i].pr[j];
            }
            aux->p[j] = bufPool->node[i].p[j];          //Copia o último ponteiro (n+1)
            bufPool->freq[i]++;                         //Atualiza a frequência

            break;                                      //Sai do for()
        }
    }

    //Página não está no buffer
    //Verifica se percorreu todo o buffer
    if(i == TAM_BUFFER){
        b = fopen("arvoreB.bin", "r+b");
        //Checar cabeçalho
        //Pulando o cabeçalho
        fseek(b, TAM_CAB_INDICE, SEEK_SET);
        //Indo pro RRN desejado
        fseek(b, RRN*TAM_NO_INDICE, SEEK_CUR);

        //Copia todo o conteudo do nó que está no buffer para uma auxiliar 
        fread(&aux->n, 1, sizeof(int), b);
        for(j = 0;j < bufPool->node[i].n;j++){          //Roda por todos os registros do nó
            fread(&aux->p[i], 1, sizeof(int), b);
            fread(&aux->c[i], 1, sizeof(int), b);
            fread(&aux->pr[i], 1, sizeof(int), b);
        }
        fread(&aux->p[i], 1, sizeof(int), b);           //Copia o ultimo ponteiro (n+1)

        //Coloca no buffer
        put(RRN, aux, bufPool);
    }

    return aux;

}

void put(int RRN, arvoreB *page, bPool *bufPool){

    //if nao esta no buffer POOL
        //1: copie o conteúdo da página para uma variável auxiliar do tipo IndexPage, chamada P  (Não vi necessidade)
        //2: se o buffer conter espaço disponível : insira P no espaço disponível
        //3: caso contrário : remova uma página N do buffer e insira P (LFU)

    //else se esta no buffer
        //1: recupere a página armazenada no buffer e atualize seu conteúdo
        //2: marque que P é uma página modificada
        //3: reorganize a estrutura interna do buffer (LFU)

    int i, j;
    int isVazio = 0;    //0 = cheio, >0 espaço vazio, n = primeiro espaço vazio
    //Variáveis pra localizar o menos utilizado (LFU)
    int menor = INT_MAX;      
    int pos = -1;
    int aux;

    //Página está no buffer
    for(i = 0;i < TAM_BUFFER;i++){          //Procura no buffer pelo RRN do nó
        //se freq == 0 significa que não tem uma página alocada, portanto o buffer não está cheio
        if(bufPool->freq[i] == 0 && isVazio == 0)    isVazio = i;    
        if(bufPool->RRN[i] == RRN){
            for(j = 0;j < 9;j++){
                bufPool->node[i].p[j] = page->p[j];
                bufPool->node[i].c[j] = page->c[j];
                bufPool->node[i].pr[j] = page->pr[j];
            }
            bufPool->node[i].p[j] = page->p[j];         //Copia o último ponteiro (n+!)
            bufPool->freq[i]++;                         //Atualiza a frequencia

            break;                                      //Sai do for()
        }
    }

    //Página não está no buffer
    //Verifica se percorreu todo o buffer
    if(i == TAM_BUFFER){     
        if(isVazio != 0){
            //Copia a árvore pro buffer
            bufPool->node[isVazio].n = page->n;
            for(j = 0;j < 9;j++){
                bufPool->node[isVazio].p[j] = page->p[j];
                bufPool->node[isVazio].c[j] = page->c[j];
                bufPool->node[isVazio].pr[j] = page->pr[j];
            }
            bufPool->node[isVazio].p[j] = page->p[j];             //Copia o último ponteiro (n+1)
        }else{
            //Acha a página menos frequentada
            for(j = 0;j < TAM_BUFFER;j++){
                if(bufPool->freq[j] < menor){
                    menor = bufPool->freq[i];
                    pos = j;
                }
            }

            //Escreve a página no arquivo de índice
            //flush(bPool->node[j], bPool);
            //Troca a página menos frequentada
            bufPool->node[pos].n = page->n;
            for(j = 0;j < 9;j++){
                bufPool->node[pos].p[j] = page->p[j];
                bufPool->node[pos].c[j] = page->c[j];
                bufPool->node[pos].pr[j] = page->pr[j];
            }
            bufPool->node[isVazio].p[j] = page->p[j];               //Copia o último ponteiro (n+1)
            bufPool->freq[isVazio] = 1;                             //Primeiro acesso
        }
    }
}

void flush_full(bPool* bufPool){
    //Escrever no disco todas as paginas com modificacoes presentes no buffer
}

void flush(arvoreB* page, bPool* bufPool){
    //Escrever no disco uma pagina que foi modificada
    //Sempre chamada durante a realizacao as trocas de pagina a serem armazenadas no buffer
}
