#include "fornecedores.h"
	
int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[])
{
	Fornecedores *f = *fornecedor;
	Fornecedores *novo_fornecedor;
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
	while(f->prox != NULL)
	{
		//Caso já exista o fornecedor
		if (strcmp(f->nome, nomeFornecedor) == 0)
		{
			printf("Não foi possivel cadastrar este fornecedor\n");
			return 0;
		}
		f = f->prox;
	}
	f->prox = novo_fornecedor;
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
//libera todas as alocacoes para fornecedores
int liberarFornecedor(Fornecedores **fornecedor)
{ 
	Fornecedores *f = *fornecedor;
	Fornecedores *aux = f;
	
	if(f == NULL) return 0;
	
	while(f != NULL)
	{
		aux = f;
		f = f->prox;
		free(aux);
	}
	*fornecedor = NULL;
	return 1;
}

int cadastrarProduto(Fornecedores **fornecedor, char nome_fornecedor[], char nomeProduto[])
{
	Fornecedores *F = *fornecedor;
	Produtos *novo_produto;
	while (F != NULL)
	{
		//Se encontrar o fornecedor
		if (strcmp(F->nome, nome_fornecedor) == 0)
		{
			//P = F->produto;
			/*while (P != NULL)
			{
				P = P->prox;
			}	*/
			//Cria novo produto
			novo_produto = (Produtos*)malloc(sizeof(Produtos));
			if(novo_produto==NULL) return 0;
			strcpy(novo_produto->nome, nomeProduto);
			novo_produto->prox = F->produto;
			F->produto = novo_produto;
			//novo_produto->prox=NULL;
			//P = novo_produto;
			return 1;
		}
		F = F->prox;
	}
	return 0;
}

int listarTodosProdutos(Fornecedores *fornecedor)
{
	/*Limpar Tela*/
	//limparTela();
	
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

