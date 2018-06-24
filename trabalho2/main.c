#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registro.h"

enum options{
	LEITURA = 1,
	RECUPERA = 2,
	BUSCAPARAM = 3,
	BUSCARRN = 4,
	REMOCAO = 5,
	INSERE = 6,
	ATUALIZA = 7,
	COMPACTA = 8,
	RECUPERAREMOVIDOS = 9,
	INSERIR_ARQ_INDICE = 10,
  	INSERIR_INDICE = 11,
	BUSCA_INDICE = 12
};

int main(int argc, char *argv[]){
	FILE *f;
	FILE *b;
	Cabecalho cab;  //Cabeçalho do arquivo
	Registro *reg;  //Vetor de registros
  bPool *bp;
	int qtdRegs;    //Quantidade de registros no arquivo

	int opt = atoi(argv[1]);    //argv[1] = opção escolhida

  //Inicializando o buffer pool
  bp = (bPool *) calloc(1, sizeof(bPool));
  for(int i = 0;i < TAM_BUFFER;i++){
      bp->RRN[i] = -1;
      bp->freq[i] = 0;
  }

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

			printf("\n\n0\t Prestadora: %s - %d\n", reg[1].prestadora, reg[1].tam_prestadora);
			printf("Data:%s\n", reg[1].dataAtiv);
			printf("codINEP:%d\n", reg[1].codINEP);
			printf("nomEscola:%s\n", reg[1].nomEscola);
			printf("TAM nomEscola: %d\n", reg[1].tamEscola);
			printf("UF:%s\n", reg[1].uf);
			printf("Municipio:%s\n", reg[1].municipio);


			transfere_arquivo(reg, qtdRegs);

			fclose(f);

			break;
		}
		case(RECUPERA):{
			printa_arquivo();
			break;
		}
		case(BUSCAPARAM):{
			busca_rrn_parametro(argv[2],argv[3]);
			break;
		}
		case(BUSCARRN):{
			int rrn = atoi(argv[2]);
			busca_rrn(rrn);
			break;
		}
		case(REMOCAO):{
			int rrn = atoi(argv[2]);
			remover_registro_rrn(rrn);
			break;
		}
		case(RECUPERAREMOVIDOS):{
			recupera_rrn();
			break;
		}
		case(INSERE):{
			int cod = atoi(argv[2]);
			char* data = argv[3];
			char* uf = argv[4];
			char* nome_esc = argv[5];
			char* muni = argv[6];
			char* prest = argv[7];

			inserir_registro(cod, data, uf, nome_esc, muni, prest);

			break;
		}
		case(ATUALIZA):{
			int rrn = atoi(argv[2]);
			int cod = atoi(argv[3]);
			char* data = argv[4];
			char* uf = argv[5];
			char* nome_esc = argv[6];
			char* muni = argv[7];
			char* prest = argv[8];

			atualizar_registro(rrn, cod, data, uf, nome_esc, muni, prest);

			break;
		}
		case(INSERIR_ARQ_INDICE):{
			int tam;    //Tamanho do arquivo
			int i;
			char c;

			//Criando o arquivo de Dados
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

			reg = recuperar_registros(f,qtdRegs);
			transfere_arquivo(reg, qtdRegs);
			//Fim da criação do arquivo de dados

			//Criando a Árvore B
			b = criar_indice(reg, qtdRegs, bp);

			fclose(f);

			break;
		}
		case(INSERIR_INDICE):{
			int cod = atoi(argv[2]);
			char* data = argv[3];
			char* uf = argv[4];
			char* nome_esc = argv[5];
			char* muni = argv[6];
			char* prest = argv[7];

			Registro reg;
			reg.codINEP = cod;
			strcpy(reg.dataAtiv, data);
			strcpy(reg.uf, uf);
			strcpy(reg.nomEscola, nome_esc);
			strcpy(reg.municipio, muni);
			strcpy(reg.prestadora, prest);

			//Insere no arquivo de dados
			int pos = inserir_registro(cod, data, uf, nome_esc, muni, prest);

			b = fopen("arvoreB.bin", "w+b");

			//Insere no arquivo de indice
			inserir_B(b, reg, pos, bp);
			break;
		}
		case(BUSCA_INDICE):{
			bPool *bp;
			FILE *b;

			//Inicializando buffer-pool
			bp = (bPool *) calloc(1, sizeof(bPool));
			for(int i = 0;i < TAM_BUFFER;i++){
				bp->RRN[i] = -1;
				bp->freq[i] = 0;
			}

			//Abrindo o arquivo de índices
			b = fopen("arvoreB.bin", "r+b");
			if(b == NULL)	return -1;

			break;
		}
	}

	return 0;
}
