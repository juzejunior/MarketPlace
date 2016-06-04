#include "include/categoria.h"

void inicializarCategoria(Categoria **categoria)
 {
	 *categoria = NULL;
 }

int inserirCategorias(Categoria **categorias, char nomeCategoria[])
{
	Categoria *C = *categorias;
	Categoria *cAnt;
	Categoria *nova_categoria;
	
	cAnt = C;
	
	if(C==NULL)
	{
		nova_categoria = (Categoria*) malloc(sizeof(Categoria));
		if(nova_categoria == NULL)
		{
			printf("Memória Indisponivel!");
			return 0;
		}
		strcpy(nova_categoria->nome,nomeCategoria);
		nova_categoria->prox = NULL;
		*categorias = nova_categoria;
		return 1;
	}
	
	while (C!=NULL)
	{
		cAnt = C;
		C = C->prox;
	}
	nova_categoria = (Categoria*) malloc(sizeof(Categoria));
	if(nova_categoria == NULL)
	{
		printf("Memória Indisponivel!");
		return 0;
	}
	strcpy(nova_categoria->nome,nomeCategoria);
	nova_categoria->prox = NULL;
	cAnt->prox = nova_categoria;
	return 1;
}

int listarCategorias(Categoria *categorias)
{
	Categoria *aux;
	if(categorias == NULL)
	{
		printf("Não Possui Categorias Cadastradas!");
		return 0;
	}

	for(aux = categorias; aux != NULL; aux = aux->prox)
	{
		printf("%s\n",aux->nome);
	}
	return 1;
}

int deletarCategorias(Categoria **categorias, char nomeCategoria[])
{
	Categoria *pAnt,*pAtual;
	
	if (categorias == NULL)
	{
		printf("Não Possui Categorias Cadastradas!");
		return 0;
	}
	
	for(pAtual = *(categorias); pAtual != NULL; pAtual = pAtual->prox)
	{
		if (strcmp(pAtual->nome,nomeCategoria)==0)
		{
			if((*categorias) == pAtual)
			{
				*categorias = pAtual->prox;
				free(pAtual);
				break;
			}
			else
			{
				pAnt->prox = pAtual->prox;
				free(pAtual);
				break;
			}
		}
		pAnt=pAtual;
	}
	return 1;
}

int listarProdutosCategoria(Categoria **categoria, Produtos *produto)
{
	Categoria *C = *categoria;
	Produtos *P = produto;
	int i=0;
	char nomeCat[50];
	char nomeProd[20];
	
	if (C == NULL)
	{
		printf("Não há categorias cadastradas");
		return 0;
	}
	
	if (P == NULL)
	{
		printf("Não há produtos cadastrados");
		return 0;
	}
	
	while (C!=NULL)
	{
		i++;
		strcpy(nomeCat, C->nome);
		printf("%d - %s\n", i, nomeCat);
		while (P!=NULL)
		{
			if (strcmp(C->nome, P->categoria) == 0)
			{
				strcpy(nomeProd, P->nome);
				printf("   %s", nomeProd);
			}
			P=P->prox;
		}
		printf("\n");
		P = produto;
		C = C->prox;
	}
	
	return 1;
}
