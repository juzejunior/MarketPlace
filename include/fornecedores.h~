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

/*inicializa um header de fornecedor*/
void inicializarFornecedor(Fornecedores **fornecedor);
/*cadastrar novo fornecedor*/
int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[]);
/*listar fornecedores*/
int listarFornecedor(Fornecedores *fornecedor);
/*remover fornecedores*/
int removerFornecedor(Fornecedores **fornecedor, char nomeFornecedor[]);
/*libera fornecedores*/
int liberarFornecedor(Fornecedores **fornecedor);
/*atualiza as informacoes do fornecedor*/
int atualizarFornecedor(Fornecedores **fornecedor, char nomeAtual[], char nomeNovo[]);
/*insere um novo produto que um fornecedor ofereça*/
int cadastrarProduto(Fornecedores **fornecedor, char nome_fornecedor[], char nomeProduto[]);
/*listar aleatoriamente os produtos*/
int listarTodosProdutos(Fornecedores *fornecedores);
#endif
