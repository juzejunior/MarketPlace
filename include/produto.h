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

void menuEstoque();
void menuExibir();
void exibirAleatoriamente();
void exibirPorCategoria();
void exibirPorFornecedor();
void exibirPorQuantidade();
void exibirPorBusca();
int inserirProduto();
int retirarDoEstoque();
int deletarProduto();
int deletarProdutosZerados();
int checarQuantidade();
int checarValidade();

#endif
