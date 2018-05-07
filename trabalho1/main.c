#include <stdio.h>
#include <stdlib.h>
#include "registro.h"

enum options{
  LEITURA = 1,
  RECUPERA,
  BUSCAPARAM,
  BUSCARRN,
  REMOCAO,
  INSERE,
  ATUALIZA,
  COMPACTA,
  RECUPERAREMOVIDOS
};

int main(int argc, char *argv[]){
  FILE *f;
  Cabecalho cab;  //Cabeçalho do arquivo
  Registro *reg;  //Vetor de registros
  int qtdRegs;    //Quantidade de registros no arquivo

  int opt = atoi(argv[1]);    //argv[1] = opção escolhida

  switch(opt){
    case(LEITURA):{
      int tam;    //Tamanho do arquivo
      int i;
      char c;

      f = cria_arquivo(argv[2]);  //argv[2] = nome do arquivo
      cab.status = '0';
      
      //Descobre tamanho do arquivo e volta para o início do mesmo
    qtdRegs=0;
    i=0;
    c = fgetc(f);
    while(c!= EOF){
      if(c == '\n')qtdRegs++;
      c = fgetc(f);
    }

    fseek(f, 0, SEEK_SET);
    
    printf("%d\n",qtdRegs);
      reg = recuperar_registros(f,qtdRegs);
              
     //           printf("\n\n0\t Prestadora: %s - %d\n", reg[1].prestadora, reg[1].tam_prestadora);
   //             printf("Data:%s\n", reg[1].dataAtiv);
       //         printf("codINEP:%d\n", reg[1].codINEP);
              // printf("nomEscola:%s\n", reg[1].nomEscola);
                printf("TAM nomEscola:%d\n", reg[0].tamEscola);
             //   printf("UF:%s\n", reg[1].uf);
               // printf("Municipio:%s\n", reg[1].municipio);
                
                
      transfere_arquivo(reg, qtdRegs);

      break;
    }
    case(RECUPERA):{
      //todo
      break;
    }
  
  }
return 0;
}