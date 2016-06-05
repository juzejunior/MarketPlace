#include "../include/fornecedor.h"
#include "config.c"
/* 
 * File:   fornecedores.c
 * Author: junior(Diôgo)
 *
 * Created on 16 de Abril de 2016, 18:11
 */		
void inicializarFornecedor(Fornecedor **fornecedor)
{
	*fornecedor = NULL;
}

int existeFornecedor(Fornecedor *fornecedor, char nomeFornecedor[])
{
	Fornecedor *f = fornecedor;
	
	while(f != NULL)
	{
		if(strcmp(f->nome, nomeFornecedor) == 0) return 1;
		f = f->prox;
	}
	return 0;
}

int carregaFornecedor(Fornecedor **f)
{
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	Fornecedor aux, *fornecedor, *novo, *anterior;

	/*se o arquivo existir*/
	if(file_fornecedor != NULL)
	{
		while(fread(&aux, sizeof(Fornecedor),1,file_fornecedor) == 1)//lendo as structs no arquivo
		{
			fornecedor = *f;//taking the node root
			anterior = fornecedor;//iniciando o anterior
			
			 novo = (Fornecedor*) malloc(sizeof(Fornecedor));//alocando novo espaço
			*novo = aux; //atribuindo os valores
			novo->prox = NULL;
			if(fornecedor == NULL)//caso nao exista fornecedores carregados ainda
			{
				*f = novo;//atribui ao nó root
			}
			else
			{
				while(fornecedor != NULL)//percorre toda a lista de fornecedores
				{
					anterior = fornecedor;//guardando o ultimo elemento
					fornecedor = fornecedor->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
			}
		}
		fclose(file_fornecedor);//encerrando o arquivo
	}else{
		inicializarFornecedor(f);
	}
	return 0;
}

/*exibir fornecedores em lista*/
int  exibir(Fornecedor **fornecedor)
{
	Fornecedor *f = *fornecedor;
	if(f == NULL)
	{
		return 0;
	}else{
		while(f != NULL)
		{
			printf("%s\n", f->nome);
			f = f->prox;
		}
	}
	return 1;
}

void cadastrarFornecedor(Fornecedor **fornecedor)
{
	FILE *file_fornecedor;
	Fornecedor *f, *anterior, *novo;
	char opcao;
	
	do{
		f = *fornecedor;//taking the node root
		anterior = f;//iniciando o anterior
		novo = (Fornecedor*) malloc(sizeof(Fornecedor));//alocando
		file_fornecedor = fopen("../DB/fornecedores.bin","ab");
		limparTela();
		printf("                                     %s", now());
	    marca();	
	    printf("       		      Cadastro de Fornecedores\n\n");
	    printf(" 		Empresa: ");
	    scanf(" %[^\n]s", novo->nome);
	    
	    //caso o fornecedor não esteja cadastrado continue o cadastro
	    if(!existeFornecedor(f, novo->nome))
	    {
			printf(" 		E-mail: ");
			scanf(" %[^\n]s", novo->email);
			printf(" 		Telefone: ");
			scanf(" %[^\n]s", novo->telefone);
			printf(" 		CNPJ: ");
			scanf(" %[^\n]s", novo->cnpj);
			
			//se nao houver fornecedores cadastrados
			if(f == NULL)
			{
				*fornecedor = novo;
			}else
			{
				while(f != NULL)//percorre toda a lista de fornecedores
				{
					anterior = f;//guardando o ultimo elemento
					f = f->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
			}
			if(fwrite(novo,sizeof(Fornecedor),1,file_fornecedor) != 0) printf(" 		Cadastrado com sucesso :)\n\n");
			else printf(" 		Problema ao cadastrar fornecedor :(\n\n");
		}else
		{
			printf(" 		Fornecedor já cadastrado!\n\n");
		}
	    fclose(file_fornecedor);
	    printf(" 		Novo cadastro(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao != 'n');
	
}
