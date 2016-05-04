#include "fornecedores.h"
/* 
 * File:   fornecedores.c
 * Author: junior(Diôgo)
 *
 * Created on 16 de Abril de 2016, 18:11
 */		
void inicializarFornecedor(Fornecedores **fornecedor)
{
	*fornecedor = NULL;
}
	
int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[])
{
	Fornecedores *f = *fornecedor;
	Fornecedores *novo_fornecedor, *anterior;
	//criacao do novo nó
	novo_fornecedor = (Fornecedores*) malloc(sizeof(Fornecedores));
	Produtos *produto = (Produtos*) malloc(sizeof(Produtos));
	//caso nao tenha mais espaco para alocar 
	if(novo_fornecedor == NULL || produto == NULL) return 0;
	//atribui o nome do fornecedor
	strcpy(novo_fornecedor->nome, nomeFornecedor);
	novo_fornecedor->produto = produto;
	//guardando informacao do produto
	strcpy(produto->nome, nomeProduto);
	produto->prox = NULL;
	//caso não exista nenhum fornecedor cadastrado
	if(f == NULL)
	{
		*fornecedor = novo_fornecedor;
		return 1;
	}
	//caso ja exista fornecedores cadastrados
	while(f != NULL)
	{
		//Caso já exista o fornecedor
		if (strcmp(f->nome, nomeFornecedor) == 0)
		{
			printf("Este fornecedor já existe!\n");
			return 0;
		}
		anterior = f;
		f = f->prox;
	}
	
	anterior->prox = novo_fornecedor;
	novo_fornecedor->prox = NULL;
	novo_fornecedor->produto = produto;

	return 1;
}
/*Remove um fornecedor especifico cadastrado*/
int removerFornecedor(Fornecedores **fornecedor, char nomeFornecedor[])
{
	Fornecedores *f = *fornecedor;
	Fornecedores *trash;
	Fornecedores *anterior = f;
	//caso nao haja fornecedores cadastrados
	if(*fornecedor == NULL)
	{
		printf("Não há fornecedores cadastrados.");
		return 0;
	}
	
	while(f != NULL)
	{
		if(strcmp(f->nome, nomeFornecedor) == 0)
		{
			if(f == *fornecedor)
			{
				trash = f;
				(*fornecedor) = f->prox;
				free(trash);
			}else
			{
				trash = f;
				anterior->prox = f->prox;
				free(trash);
			}
			return 1;
		}
		anterior = f;
		f = f->prox;
	}
	printf("Esse fornecedor não existe em nosso cadastro!\n");
	return 0;
}

/*exibe todos os fornecedores pertencentes a empresa*/
int listarFornecedor(Fornecedores *fornecedor)
{
	Fornecedores *f;
	f = fornecedor;
	if (f == NULL) {
		printf("Não ha fornecedores cadastrados!\n");
		return 0;
	}
	while (f != NULL){
		printf("%s\n", f->nome);
		f = f->prox;
	}
	
	return 1;
}
/*liberar produtos de um fornecedor especifico*/
int liberarProdutos(Fornecedores **fornecedor, char nomeFornecedor[])
{
	Fornecedores *f = *fornecedor;
	Produtos *p, *produtosFree;
	//se nao houver fornecedores cadastrados
	if(f == NULL) return 0;
	
	while(f != NULL)
	{
		if(strcmp(f->nome, nomeFornecedor) == 0)
		{
			p = f->produto;
			while(p != NULL)
			{
				produtosFree = p;
				p = p->prox;
				free(produtosFree);
			}
			return 1;
		}
	}
	return 0;	
}

/*atualizar nome do fornecedor - CORRIGIR*/
int atualizarFornecedor(Fornecedores **fornecedor, char nomeAtual[], char nomeNovo[])
{
	Fornecedores *f = *fornecedor;
	if(f == NULL) return 0;
	
	while(f != NULL)
	{
		if(strcmp(f->nome, nomeAtual) == 0)
		{
			strcpy(f->nome, nomeNovo);
			return 1;
		}
		f = f->prox;
	}
	
	return 0;
}

/*libera todas as alocacoes para fornecedores*/
int liberarFornecedor(Fornecedores **fornecedor)
{ 
	Fornecedores *f = *fornecedor;
	Fornecedores *aux = f;
	
	if(f == NULL) return 0;
	
	while(f != NULL)
	{
		liberarProdutos(fornecedor,f->nome);
		aux = f;
		f = f->prox;
		free(aux);
	}
	*fornecedor = NULL;
	return 1;
}

/*cadastra um novo produto em um fornecedor*/
int cadastrarProduto(Fornecedores **fornecedor, char nome_fornecedor[], char nomeProduto[])
{
	Fornecedores *F = *fornecedor;
	Produtos *novo_produto;
	Produtos *p,*produto_anterior;
	
	while (F != NULL)
	{
		//Se encontrar o fornecedor
		if (strcmp(F->nome, nome_fornecedor) == 0)
		{
			//Cria novo produto
			novo_produto = (Produtos*) malloc(sizeof(Produtos));
			if(novo_produto == NULL) return 0;
			strcpy(novo_produto->nome, nomeProduto);
			novo_produto->prox = NULL;
			
			//atribui o ponteiro do produto para p e adiciona ao final da lista
			p = F->produto;
			//percorre ate o final da lista e insere o novo produto
			while(p != NULL){
				//se o produto ja estiver cadastrado
				if(strcmp(p->nome, nomeProduto) == 0)
				{
					printf("O fornecedor %s ja possui esse produto.\n", F->nome);
					return 0;
				}
				produto_anterior = p;
				p = p->prox;
			} 
			produto_anterior->prox = novo_produto;
			return 1;
		}
		F = F->prox;
	}
	return 0;
}

/*lista todos os produtos com seus respectivos fornecedores*/
int listarTodosProdutos(Fornecedores *fornecedor)
{	
	/*Listando Produtos*/
	Fornecedores *F = fornecedor;
	Produtos *P;
	while (F != NULL)
	{
		P = F->produto;
		printf ("Fabricante: %s\n", F->nome);
		while(P != NULL)
		{
			printf ("   Produto: %s\n", P->nome);
			P = P->prox;
		}
		printf("\n");
		F = F->prox;
	}
	return 1;
}


