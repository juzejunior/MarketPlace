#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct Data{
	int dia;
	int mes;
	int ano;
} Data;
 
 
typedef struct Produtos{
	char nome[20];
	int quantidade;
	Data vencimento;
	struct Produtos *prox;
}Produtos; 

int checarVencimento(Produtos **produto);

int checarQuantidade(Produtos **produto);

#endif
