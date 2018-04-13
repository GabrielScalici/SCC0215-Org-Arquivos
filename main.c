#include <stdio.h>
#include <stdlib.h>
#include "registro.h"


///STRINGS DO MENU
void menu()
{
    printf("\n\tMENU\n");
    printf("1. LER REGISTROS\n");
    printf("2. BUSCAR TODOS OS REGISTROS\n");
    printf("3. BUSCAR REGISTROS COM CRITERIO DE BUSCA\n");
    printf("4. VER REGISTROS PELO RRN\n");
    printf("5. REMOVER REGISTROS PELO RRN\n");
    printf("6. INSERIR REGISTRO\n");
    printf("7. ATUALIZAR REGISTRO\n");
    printf("8. COMPACTAR ARQUIVO\n");
    printf("9. REGISTROS REMOVIDOS\n");
    printf("0. SAIR DO PROGRAMA\n");
    printf("Opcao desejada: ");
}


int main(int argc, char *argv[]){

  FILE *f;

  // Criando o arquivo de registros com base no csv
  f = cria_arquivo();

  //recuperar_registros(f);

  return 0;
}
