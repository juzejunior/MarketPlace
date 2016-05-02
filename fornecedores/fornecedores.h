#ifndef FORNECEDORES_H
#define FORNECEDORES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../config/config.c"
#include "../produtos/produtos.h"


typedef struct Fornecedores{
	char nome[20];
	Produtos *produto;
	struct Fornecedores *prox;
} Fornecedores;

/*faz novo pedido ao fornecedor*/
int pedidoProduto(Fornecedores **fornecedor,char nome_produto[],int quantidade);
/*cadastrar novo fornecedor*/
int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[]);
/*listar fornecedores*/
int listarFornecedor(Fornecedores *fornecedor);
/*remover fornecedores*/
int removerFornecedor(Fornecedores **fornecedor, char nomeFornecedor[]);
/*libera fornecedores*/
int liberaFornecedor(Fornecedores **fornecedor);
/*insere um novo produto que um fornecedor ofereça*/
int cadastrarProduto(Fornecedores **fornecedor, char nome_fornecedor[], char nomeProduto[]);
/*listar aleatoriamente os produtos*/
int listarTodosProdutos(Fornecedores *fornecedores);
#endif
