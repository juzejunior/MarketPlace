#ifndef FORNECEDOR_H
#define FORNECEDOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"


typedef struct Fornecedor{
	char nome[30];
	char email[30];
	char telefone[30];
	char cnpj[17];
	struct Fornecedor *prox;
} Fornecedor;

/*cadastrar um novo fornecedor*/
void cadastrarFornecedor(Fornecedor **fornecedor);
/*carrega os fornecedores do DB*/
int carregaFornecedor(Fornecedor **f);
/*verifica se o fornecedor já está cadastrado*/
int existeFornecedor(Fornecedor *fornecedor, char nomeFornecedor[]);
/*inicializa um header de fornecedor*/
void inicializarFornecedor(Fornecedor **fornecedor);

#endif
