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
 *  Criar arquivo (caso não exista) e inserir o RRN do ultimo
 *  registro removido (PILHA).
*/
FILE* cria_arquivo(char *arquivo){
    FILE *f;
    Registro *reg;
    
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
Registro *recuperar_registros(FILE *f){
    int tam;
    int qtdRegs;
    int alternando = 0, qtd = 0, i=0;
    char c;
    Registro *reg;

    //Descobre tamanho do arquivo e volta para o início do mesmo
    fseek(f, 0, SEEK_END);
    tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    //Como os registros são de tamanho fixo, é possível calcular a quantidade de registros
    qtdRegs = tam/TAM_REG;

    //Aloca a quantidade de memória necessária
    reg = (Registro *) calloc(qtdRegs, sizeof(Registro));

    char* carac= (char*)calloc(80, sizeof(char));
    while(1){

        do{
            c= fgetc(f);
            if(c != ';' && c != '\n' && c != EOF){
                carac[i] = c ;//string temporaria para pegar os registros
                i++;
            }
        } while (c != ';' && c != '\n' && c != EOF );
        carac[i] = '\0';

            if(alternando == 0){//colocando no campos campos prestadora e tam_prestadora
                reg[qtd].prestadora = carac;
                reg[qtd].tam_prestadora = i;
                printf("\n\n%d\nPrestadora: %s\n",qtd, reg[qtd].prestadora);
                alternando=1;
            }
            else if(alternando == 1){//colocando no campo de dataAtiv
                //reg[qtd].dataAtiv = carac;
                printf("Data:%s\n", carac);
                alternando=2;
            }
            else if(alternando == 2){//colocando no campo de codINEP
                reg[qtd].codINEP = atoi(carac);
                //reg[qtd].codINEP = carac;
                printf("codINEP:%d\n", reg[qtd].codINEP);
                alternando=3;
            }
            else if(alternando == 3){//colocando nos campos nomEscola e tam_nomEscola 
                reg[qtd].nomEscola = carac;
                reg[qtd].tam_nomEscola = i;
                printf("nomEscola:%s\n", reg[qtd].nomEscola);
                alternando=4;
            }
            else if(alternando == 4){//colocando nos campos municipio e tam_municipio
                reg[qtd].municipio = carac;
                reg[qtd].tam_municipio = i;
                printf("Municipio:%s\n", reg[qtd].municipio);
                alternando=5;
            }
            else if(alternando == 5){//colocando no campo de uf
                //reg[qtd].uf = carac;
                printf("UF:%s\n", carac);
                qtd++;
                alternando=0;
            }           
        //criar uma nova string temp, para pegar o valor do proximo campo
            free(carac);
            char* carac= (char*)calloc(80, sizeof(char));
            i = 0;
            printf("-----------------------\n");
        
        if(c == EOF) break;
    }
    free(carac);

    fclose(f);  //Tira o arquivo da memória

    return reg;
}
