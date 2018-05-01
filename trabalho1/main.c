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

      f = cria_arquivo(argv[2]);  //argv[2] = nome do arquivo
      cab.status = '0';

      //Descobre tamanho do arquivo e volta para o início do mesmo
      fseek(f, 0, SEEK_END);
      tam = ftell(f);
      fseek(f, 0, SEEK_SET);

      //Como os registros são de tamanho fixo, é possível calcular a quantidade de registros
      qtdRegs = tam/TAM_REG;

      break;
    }
  
  }
  return 0;
}
