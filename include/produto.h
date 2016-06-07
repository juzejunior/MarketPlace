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
	int eDia, eMes, eAno;
	int dia, mes, ano;
	struct Produto *prox;
}Produto;

typedef struct Categoria Categoria;
typedef struct Fornecedor Fornecedor;

void inicializarEstoque(Produto **produto);
int carregaEstoque(Produto **p);
void menuExibir(Produto **produto, Categoria **categoria, Fornecedor **fornecedor);
int exibirAleatoriamente(Produto **produto);
int exibirPorCategoria(Produto **produto, Categoria **categoria);
int exibirPorFornecedor(Produto **produto, Fornecedor **fornecedor);
int exibirPorQuantidade(Produto **produto);
int exibirPorBusca(Produto **produto);
int inserirProduto(Produto **produto, Categoria **categoria, Fornecedor **fornecedor, Produto **p_fornecedor);
int retirarDoEstoque(Produto **produto);
int deletarProduto(Produto **produto);
int deletarProdutosZerados(Produto **produtos);
int checarQuantidade(Produto **produto);
int checarValidade(Produto **produto);
void menuEstoque(Produto **produto, Categoria **categoria, Fornecedor **fornecedor, Produto **p_fornecedor);

#endif
