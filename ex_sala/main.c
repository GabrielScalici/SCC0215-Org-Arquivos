#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definindo os registros
typedef struct{
   char name[20];
   char email[30];
   int age;
} REGISTRO;

//Adicionando os registros
FILE* adicionar_registros(){

  FILE* f;
  //instanciando o registro
  REGISTRO entrada;

  //Pegando os valores digitados pelo USUARIO
  printf("DIGITE O NOME\n");
  scanf("%s", &entrada.name);
  printf("DIGITE O EMAIL\n");
  scanf("%s", &entrada.email);
  printf("DIGITE A IDADE\n");
  scanf("%d", &entrada.age);

  //Abrindo o arquivo para escrita
  f = fopen("dados.dat", "a+b");

  if(!f){
    printf("Erro ao abrir arquivo\n");
  }

  //escrevendo no final o final para nao sobrescrever
  fseek(f, 0, SEEK_END);
  fwrite(&entrada, sizeof(entrada), 1, f);

  //fechando o arquivo
  fclose(f);
  return f;
}

//Lendo todos os registros do arquivo
void recuperar_dados(){
  FILE* f;
  REGISTRO saida;
  int i = 0;

  f = fopen("dados.dat", "rb");

  while(fread(&saida, sizeof(saida), 1, f) != 0){
    printf(" RRN: %d\n NOME: %s\n EMAIL: %s\n IDADE: %d\n", i, saida.name, saida.email, saida.age);
    i++;
  }
  printf("\n\n\n");
  fclose(f);

}

//Pesquisando registro pelo rrn
void pesquisar_rrn(int rrn){
  FILE* f;
  REGISTRO saida;

  f = fopen("dados.dat", "rb+");

  //colocando no rrn correto
  fseek(f, (rrn)*sizeof(saida), SEEK_SET);
  fread(&saida, sizeof(saida), 1, f);

  //Caso encontre, entao imprima
  printf("RRN: %d\n NOME: %s\n EMAIL: %s\n IDADE: %d\n", rrn, saida.name, saida.email, saida.age);
  printf("\n\n\n");

  fclose(f);
}

//Printando o menu
void menu(){

  printf("---- MENU ----\n");
  printf("1. CRIAR REGISTRO\n");
  printf("2. MOSTRAR DADOS\n");
  printf("3. RECUPERAR PELO RRN\n");
  printf("0. SAIR DO PROGRAMA\n");

}


//Funcao principal
int main(){

  FILE* f;
  int op = 1, rrn;

  while(op != 0){

    //MOSTRANDO O MENU
    menu();

    //OPCAO DO USUARIO
    scanf("%d", &op);

    switch (op) {
      //Adicionar arquivos
      case 1:
        f = adicionar_registros();
        break;
      //Pesquisar todos os dados
      case 2:
        recuperar_dados();
        break;
      //Recuperar pelo RRN
      case 3:
        printf("Digite o rrn:\n");
        scanf("%d", &rrn);
        pesquisar_rrn(rrn);
        break;
    }
}

  return 0;
}
