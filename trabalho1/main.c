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

      f = cria_arquivo(argv[2]);  //argv[2] = nome do arquivo
      cab.status = '0';

      reg = recuperar_registros(f);

      break;
    }
    case(RECUPERA):{
      //todo
      break;
    }
  
  }
  return 0;
}
