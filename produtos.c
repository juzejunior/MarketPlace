#include "include/produtos.h"
/* 
 * File:   produtos.c
 * Author: Mateus Nascimento
 *
 * Created on 04 de Maio de 2016, 21:51
 */		
 
 void inicializarProduto(Produtos **produto)
 {
	 *produto = NULL;
 }
 
 int novoPedido(Produtos **produto, Fornecedores *fornecedor, char nomeCategoria[], char nomeProduto[], char nomeFornecedor[], int quantidade)
 {
	 Fornecedores *F;
	 Produtos *P, *pAnt;
	 Produtos *novo_produto;
	 Produtos *pAux;

	 F = fornecedor;
	 P = *produto;
	 pAnt = P;
	 
	 while (F != NULL)
	 {
		 if (strcmp(nomeFornecedor, F->nome) == 0)
		 {
			 pAux = F->produto;
			 while (pAux != NULL)
			 {
				 if (strcmp(pAux->nome, nomeProduto) == 0)
				 {
					 novo_produto = (Produtos*)malloc(sizeof(Produtos));
					 if(novo_produto == NULL) 
					 {
						printf("Erro na Alocacao");
						return 0; 
					 }
					 strcpy(novo_produto->nome, nomeProduto);
					 strcpy(novo_produto->categoria, nomeCategoria);
					 novo_produto->quantidade = quantidade;
					 novo_produto->prox = NULL;
					 if (*produto==NULL){
						 *produto = novo_produto;
						 novo_produto->prox = NULL;
						 return 1;
					 }
					 while (P != NULL)
					 {
						 pAnt = P;
						 P = P->prox;
					 }
					 pAnt->prox = novo_produto;
					 return 1;
				 }
				 pAux = pAux->prox;
			 }
		 }
		 F = F->prox;
	 }
	 return 0;
 }
 
 int listarEstoque(Produtos *produto){
	 Produtos *P = produto;
	 if (P==NULL)
	 {
		 printf("Não há nenhum produto cadastrado!");
		 return 0;
	 }
	 while (P != NULL)
	 {
		 printf("%s\n", P->nome);
		 printf("%d\n", P->quantidade);
		 P = P->prox;
	 }
	 return 1;
 }
 
 int menuEstoque()

