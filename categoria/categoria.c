/*Categorias*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Categoria{
	char nomeCategoria[50];
	struct Categoria *prox;
}cat;

void inserirCategorias(cat **categorias, char nomeCategoria[]);
void listarCategorias(cat *categorias);
void deletarCategorias(cat **categorias, char nomeCategoria[]);

/*int main(){
	cat *categorias;
	int insere=0;
	char nomeCategoria[50];
	categorias = NULL;
	
	do{
		printf("0 - (Sair)\n1 - (Inserir)\n2 - (Listar)\n3 - (Deletar)\n");
		printf("Informe a sua opcao: ");
		scanf("%d",&insere);
		switch(insere){
			case 1: printf("Informe uma categoria: ");
					scanf(" %s",nomeCategoria);
					inserirCategorias(&categorias,nomeCategoria);
					break;
			case 2: listarCategorias(categorias);
					break;
			case 3: printf("Informe a Categoria a ser Deletada: ");
					scanf("%s",nomeCategoria);
					deletarCategorias(&categorias,nomeCategoria);
					break;
		}
	}while(insere != 0);
	return 0;
}*/

void inserirCategorias(cat **categorias, char nomeCategoria[]){
	cat *aux;
	aux = (cat*) malloc(sizeof(cat));
	
	if(aux == NULL){
		printf("Memória Indisponivel!");
	}
	
	strcpy(aux->nomeCategoria,nomeCategoria);
	aux->prox = *categorias;
	*categorias = aux;
}

void listarCategorias(cat *categorias){
	cat *aux;
	if(categorias == NULL){
		printf("Não Possui Categorias Cadastradas!");
	}else{
		for(aux = categorias; aux!=NULL; aux= aux->prox){
			printf("%s\n",aux->nomeCategoria);
		}
	}
}
void deletarCategorias(cat **categorias, char nomeCategoria[]){
	cat *pAnt,*atual;
	
	for(atual = *(categorias); atual != NULL; atual = atual->prox){
		if (strcmp(atual->nomeCategoria,nomeCategoria)==0){
			if((*categorias) == atual){
				*categorias = atual->prox;
				free(atual);
				break;
			 }else{
				pAnt->prox=atual->prox;
				free(atual);
				break;
			}
		}
		pAnt=atual;
	}
}
