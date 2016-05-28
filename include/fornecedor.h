#ifndef FORNECEDOR_H
#define FORNECEDOR_H
#include "config.h"


typedef struct Fornecedor{
	char nome[30];
	char email[30];
	char telefone[30];
	char cnpj[17];
}Fornecedor;

int inserirFornecedor();
int deletarFornecedor();
int exibirFornecedor();
void menuFornecedor();

#endif
