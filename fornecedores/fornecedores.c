#include "fornecedores.h"

int cadastrarFornecedor(Fornecedores **fornecedor, char nomeFornecedor[], char nomeProduto[])
{
	printf("OI");
	Fornecedores *f;
	f = (Fornecedores*) malloc(sizeof(Fornecedores));
	f = *fornecedor;
	Fornecedores *novo_fornecedor;
	novo_fornecedor = (Fornecedores*) malloc(sizeof(Fornecedores));
	Produtos *produto = (Produtos*) malloc(sizeof(Produtos));
	printf("OI");
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
		f = novo_fornecedor;
		return 1;
	}
	//caso ja exista fornecedores cadastrados
	while(f->prox != NULL) f = f->prox;
	f->prox = novo_fornecedor;

	return 1;
}

int listarFornecedor(Fornecedores **fornecedor){
	Fornecedores *f;
	f = *fornecedor;
	if (f==NULL) return 0;
	while (f != NULL){
		printf("%s\n", f->nome);
		f = f->prox;
	}
	return 1;
}
