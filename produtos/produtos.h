#ifndef PRODUTOS_H
#define PRODUTOS_H

/* 
 * File:   produtos.h
 * Author: junior(Diôgo)
 *
 * Created on 16 de Abril de 2016, 18:11
 */
typedef struct Produtos{
	char nome[20];		
	double preco;
	int pratilheira, estoque;
	struct Produtos *prox;
}Produtos; 

/*
** Adiciona uma quantidade em um produto ou em todos os produtos no estoque.
*/
int reporEstoque(Produtos **produtos,char nome[], int quant);
/*
** Vende um produto
*/
int vender(Produtos **produtos, char nome[],int quant);
/*
**Lista a situação de um produtos ou de todos os produtos
*/
int listar(Produtos *produtos, char nome[]);
/*
** Cadastra um novo produto, caso o mesmo já esteja cadastrado retorna 1,
** caso contrário retorna 0 e cadastra o novo produto
*/
int cadastrarProduto(Produtos **produtos,char nome[]);

#endif
