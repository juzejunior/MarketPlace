#include "categoria.h"

void inserirCategorias(Categoria **categorias, char nomeCategoria[])
{
	Categoria *aux;
	aux = (Categoria*) malloc(sizeof(Categoria));
	
	if(aux == NULL)
	{
		printf("Memória Indisponivel!");
		return;
	}
	
	strcpy(aux->nomeCategoria,nomeCategoria);
	aux->prox = *categorias;
	*categorias = aux;
}

void listarCategorias(Categoria *categorias){
	Categoria *aux;
	if(categorias == NULL)
	{
		printf("Não Possui Categorias Cadastradas!");
		return;
	}

	for(aux = categorias; aux != NULL; aux = aux->prox)
	{
		printf("%s\n",aux->nomeCategoria);
	}
}

void deletarCategorias(Categoria **categorias, char nomeCategoria[]){
	Categoria *pAnt,*pAtual;
	
	for(pAtual = *(categorias); pAtual != NULL; pAtual = pAtual->prox)
	{
		if (strcmp(pAtual->nomeCategoria,nomeCategoria)==0)
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
}
