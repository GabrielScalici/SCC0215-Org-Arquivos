#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    //variaveis para capturar os parametros passados via chamada do programa
    char param1[5];
    int param2;
    char param3[10];
    
    if(argc != 4){
	printf("Numero de parametros invalido! Quantidade esperada eh 3 e o informado eh %d.\n", argc);
	return -1;
    }
    
	
    //capturando os parâmetros passados (atenção ao uso do strncpy, o strcpy não é recomendado - ver na documentação C)
    strncpy(param1, argv[1], 5);
    param2 = atoi(argv[2]);
    strncpy(param3, argv[3], 10);

    //termando com null as strings devido as peculiaridades da linguagem C (em memória principal apenas - no trabalho não é para gravar o \0 pois não estamos usando delimitadores!)
    param1[5] = '\0';
    param3[10] = '\0';

    //realize os demais processamento aqui... 

    //Para mandar os resultados para a saída padrão, basta usar o printf normalmente, por exemplo:
    printf("O primeiro parametro tem o valor: %s\n", param1);
    printf("O segundo parametro tem o valor: %d\n", param2);
    printf("O terceiro parametro tem o valor: %s\n", param3);

    /*note que o argv[0] corresponde a chamada usada para executar o programa:*/
    printf("Nome da execução: %s\n", argv[0]);

    /* note que o número de parâmetros e seus tipos de dados podem mudar dependendo do item do trabalho. 
       Então utilize o primeiro parâmetro informado (que é sempre o identificador do item do trabalho) para saber quantos parâmetros que devem ser lidos, e quais serão eles para realizar o devido processamento.
    */

    

    return 0;
}
