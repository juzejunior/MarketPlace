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
	struct Produto *prox;
}Produto;

void menuEstoque();
void menuExibir();
void exibirPorCategoria();
void exibirAleatoriamente();
void exibirPorFornecedor();
void exibirPorQuantidade();
void exibirPorBusca();
int inserirProduto();
int retirarDoEstoque();
int deletarProduto();
int deletarProdutosZerados();
/*faz a leitura de todos os produtos do arquivo e chama a funcao para ordenar
* por data
* */
int organizarEstoque();
int checarQuantidade();
int checarValidade();
void organizarPorData(Produto produto[], int n);
void exibirProdutosFornecedores();

#endif
