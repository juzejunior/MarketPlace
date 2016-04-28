#ifndef FORNECEDORES_H
#define FORNECEDORES_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../produtos/produtos.h"

typedef struct Fornecedores{
	char nome[20];
	Produtos *produto;
	struct Fornecedores *prox;
}Fornecedores;

/*novo pedido*/
int pedidoProduto(Fornecedores **fornecedor,char nome_produto[],int quantidade);
/*cadastrar novo fornecedor*/
int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[]);
/*listar fornecedores*/
int listarFornecedor(Fornecedores **fornecedor);
int cadastrarProduto(Fornecedores **fornecedor, char nome_fornecedor[], char nomeProduto[], int quantidade);
#endif
