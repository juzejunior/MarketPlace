#include "../include/config.h"

void inicializarCategoria(Categoria **categoria)
{
	*categoria = NULL;
}

int carregaCategoria(Categoria **c)
{
	FILE *file_categoria = fopen("../DB/categoria.bin","rb");
	Categoria aux, *categoria, *novo, *anterior;
	*c = NULL;
	/*se o arquivo existir*/
	if(file_categoria != NULL)
	{
		while(fread(&aux, sizeof(Categoria),1,file_categoria) == 1)//lendo as structs no arquivo
		{
			categoria = *c;//taking the node root
			anterior = categoria;//iniciando o anterior
			
			 novo = (Categoria*) malloc(sizeof(Categoria));//alocando novo espaço
			*novo = aux; //atribuindo os valores
			novo->prox = NULL;
			if(categoria == NULL)//caso nao exista fornecedores carregados ainda
			{
				*c = novo;//atribui ao nó root
			}
			else
			{
				while(categoria != NULL)//percorre toda a lista de fornecedores
				{
					anterior = categoria;//guardando o ultimo elemento
					categoria = categoria->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
			}
		}
		fclose(file_categoria);//encerrando o arquivo
	}else{
		inicializarCategoria(c);
	}
	return 0;
}

void cadastrarCategoria(Categoria **categoria)
{
	FILE *file_categoria;
	Categoria *c, *anterior, *novo;
	char opcao;
	
	do{
		c = *categoria;//taking the node root
		anterior = c;//iniciando o anterior
		novo = (Categoria*) malloc(sizeof(Categoria));//alocando
		file_categoria = fopen("../DB/categoria.bin","ab");
		limparTela();
		printf("                                     %s", now());
	    marca();	
	    printf("       		      Cadastro de Categorias\n\n");
	    printf(" 		Categoria: ");
	    scanf(" %[^\n]s", novo->nomeCategoria);	
	    stringMaiusculo(novo->nomeCategoria);
		//se nao houver fornecedores cadastrados
		if(c == NULL)
		{
			*categoria = novo;
		}else{
			while(c != NULL)//percorre toda a lista de fornecedores
			{
				anterior = c;//guardando o ultimo elemento
				c = c->prox;//andando pela lista
			}
			anterior->prox = novo;//atribui o novo elemento
		}
		if(fwrite(novo,sizeof(Categoria),1,file_categoria) != 0) printf(" 		Cadastrado com sucesso :)\n\n");
		else printf(" 		Problema ao cadastrar categoria :(\n\n");
	    fclose(file_categoria);
	    printf(" 		Novo cadastro(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao != 'n');
	pause();	
	menuCategoria(&c);
}

int exibirCategoria(Categoria **categoria)
{
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Listar as Categorias\n\n");
	Categoria *c = *categoria;
	if(c == NULL)
	{
		return 0;
	}else{
		while(c != NULL)
		{
			printf("%s\n", c->nomeCategoria);
			c = c->prox;
		}
	}
		
	pause();	
	menuCategoria(categoria);
	return 1;
}

int deletarCategoria(Categoria **categoria)
{
	char opcao, nomeCategoria[30];
	Categoria cat;
	FILE *file_categoria;
	FILE *file_aux;
	do{
		file_categoria = fopen("../DB/categoria.bin","rb");
		file_aux = fopen("../DB/aux.bin","wb");
		limparTela();
		printf("                                     %s", now());
		marca();	
		printf("       		      Deletar Categorias\n\n");
		printf(" 		Categoria: ");
		scanf(" %[^\n]s", nomeCategoria);	
	    stringMaiusculo(nomeCategoria);
	    *categoria = NULL;
	    while(fread(&cat, sizeof(Categoria),1,file_categoria) == 1)//lendo as structs no arquivo
		{
			if(strcmp(nomeCategoria, cat.nomeCategoria) != 0)
			{
				fwrite(&cat,sizeof(Categoria),1,file_aux);
			}
		}
		fclose(file_categoria);
		fclose(file_aux);
		remove("../DB/categoria.bin");
		rename("../DB/aux.bin", "../DB/categoria.bin");
		printf(" 		Deletar mais uma categoria(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao!='n');
	menuCategoria(categoria);
	return 1;
}

void atualizarArquivoCategoria(Categoria **categoria)
{
	FILE *file_categoria = fopen("../DB/categoria.bin","ab+");
	Categoria *c = *categoria;
	
	if(file_categoria != NULL)
	{
		while(c != NULL)
		{
			fwrite(c->nomeCategoria,sizeof(Fornecedor),1,file_categoria);
			c = c->prox;
		}
		fclose(file_categoria);
	}
}

void menuCategoria(Categoria **categoria)
{
	 int opcao;	
	 limparTela();
	 printf("                                        %s",now());
	 marca();	
	 carregaCategoria(categoria);
	 printf("\n\t\t\t      Categorias\n\n");
	 printf("\t      1-Cadastrar Categoria    3-Excluir Categoria\n\t      2-Listar Categorias      0-Voltar\n");	
	 printf("\n\t      Opção: ");
	 scanf("%d", &opcao);
	 
	 switch(opcao)
	 {
		case 1:cadastrarCategoria(categoria);
			   break;
		case 2:exibirCategoria(categoria);
			   break;
		case 3:deletarCategoria(categoria);
			   break;
		case 0: return;
		default: printf(" Opcao Invalida, voltando ao menu principal! \n");
			pause();
			return;
	 }
}

int existeCategoria(Categoria *categoria, char nomeCategoria[])
{
	Categoria *c = categoria;
	
	while(c != NULL)
	{
		if(strcmp(c->nomeCategoria, nomeCategoria) == 0) return 1;
		c = c->prox;
	}
	return 0;
}
