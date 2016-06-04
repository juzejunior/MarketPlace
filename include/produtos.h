#ifndef PRODUTOS_H
#define PRODUTOS_H
#include "fornecedores.h"

typedef struct Data{
	int dia;
	int mes;
	int ano;
} Data;
 
typedef struct Produtos{
	char nome[20];
	char categoria[20];
	int quantidade;
	Data vencimento;
	struct Produtos *prox;
}Produtos; 

typedef struct Fornecedores Fornecedores;

void inicializarProduto(Produtos **produto);

int novoPedido(Produtos **produto, Fornecedores *fornecedor, char nomeCategoria[], 
			   char nomeProduto[], char nomeFornecedor[], int quantidade);

int listarEstoque(Produtos *produto);

int checarQuantidade(Produtos **produto);

int checarVencimento(Produtos **produto);

#endif
