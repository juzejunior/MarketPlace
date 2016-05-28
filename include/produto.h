#ifndef PRODUTO_H
#define PRODUTO_H
#include "config.h"

typedef
struct Produto{
	char nome[30];
	int quantidade;
	char nomeFornecedor[30];
	char nomeCategoria[30];
	float preco;
	int dia, mes, ano;
}Produto;

typedef
struct Organizar{
	Produto produto;
	struct Organizar *prox;
}Organizar;

void menuEstoque();
void menuExibir();
void exibirAleatoriamente();
void exibirPorCategoria();
void exibirPorFornecedor();
void exibirPorBusca();
int inserirProduto();
int retirarDoEstoque();
int deletarProduto();
int deletarProdutosZerados();
int organizarEstoque();
int checarQuantidade();
int checarValidade();
#endif
