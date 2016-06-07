#include "../include/fornecedor.h"
#include "../include/produto.h"
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
		
void inicializarProdutoFornecedor(Produto **produto)
{
	*produto = NULL;
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

void menuAtualizarFornecedor(Fornecedor **fornecedor)
{
	int opcao;		
	do{
		limparTela();
		printf("                                     %s", now());
		marca();	
		printf("       		      Atualização Fornecedor\n\n");
		printf("	1- Nome | 2- E-mail | 3- Telefone | 4- Voltar\n\n	Opção: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				atualizaNomeFornecedor(fornecedor);
			break;
			case 2:
				atualizaEmailFornecedor(fornecedor);
			break;
			case 3:
				atualizaContatoFornecedor(fornecedor);
			break;
			case 4:
				return;
				//menuFornecedor(fornecedor);
			break;
		}
	}while(opcao < 1 || opcao > 4);	
}

void atualizaNomeFornecedor(Fornecedor **fornecedor)
{
	char nomeFornecedor[30];
	Fornecedor *f;
	char opcao;
	
	do{
		f = *fornecedor;
		limparTela();
		printf("                                     %s", now());
		marca();
		printf("       		      Atualizar Nome\n\n");
		printf("	Informe o nome atual do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		if(f != NULL)
		{
			if(existeFornecedor(f,nomeFornecedor))
			{
				while(f != NULL)
				{
					if(strcmp(f->nome, nomeFornecedor) == 0)//se encontrou o fornecedor
					{
						printf("	Informe o novo nome: ");
						scanf(" %[^\n]s", nomeFornecedor);
						while(existeFornecedor(f, nomeFornecedor))
						{
							printf("	Este nome já está em uso por outro fornecedor :( \n");
							printf("	Tente um novo: ");
							scanf(" %[^\n]s", nomeFornecedor);
							stringMaiusculo(nomeFornecedor);
						}
						strcpy(f->nome, nomeFornecedor);
						printf("	Atualizado com sucesso :)\n\n");
						atualizarArquivoFornecedor(fornecedor);
						break;
					}
					f = f->prox;
				}
			}else
			{
				printf("	Fornecedor não encontrado :(\n\n");
			}
		}else
		{
			printf("	Não há fornecedores cadastrados :(\n\n");
		}
		printf("	Nova alteração(s/n): ");
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	menuAtualizarFornecedor(fornecedor);
}

void atualizaEmailFornecedor(Fornecedor **fornecedor)
{
	char nomeFornecedor[30];
	Fornecedor *f;
	char opcao;
	
	do{
		f = *fornecedor;
		limparTela();
		printf("                                     %s", now());
		marca();
		printf("       		      Atualizar E-mail\n\n");
		printf("	Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		if(f != NULL)
		{
			if(existeFornecedor(f,nomeFornecedor))
			{
				while(f != NULL)
				{
					if(strcmp(f->nome, nomeFornecedor) == 0)//se encontrou o fornecedor
					{
						printf("	E-mail atual : %s\n", f->email);
						printf("	Novo e-mail : ");
						scanf(" %[^\n]s", f->email);
						printf("	Atualizado com sucesso :)\n\n");
						atualizarArquivoFornecedor(fornecedor);
						break;
					}
					f = f->prox;
				}
			}else
			{
				printf("	Fornecedor não encontrado :(\n\n");
			}
		}else
		{
			printf("	Não há fornecedores cadastrados :(\n\n");
		}
		printf("	Nova alteração(s/n): ");
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	menuAtualizarFornecedor(fornecedor);
}

void atualizaContatoFornecedor(Fornecedor **fornecedor)
{
	char nomeFornecedor[30];
	Fornecedor *f;
	char opcao;
	
	do{
		f = *fornecedor;
		limparTela();
		printf("                                     %s", now());
		marca();
		printf("       		      Atualizar Contato\n\n");
		printf("	Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		
		if(f != NULL)
		{
			if(existeFornecedor(f,nomeFornecedor))
			{
				while(f != NULL)
				{
					if(strcmp(f->nome, nomeFornecedor) == 0)//se encontrou o fornecedor
					{
						printf("	Telefone atual : %s\n", f->telefone);
						printf("	Novo telefone : ");
						scanf(" %[^\n]s", f->telefone);
						printf("	Atualizado com sucesso :)\n\n");
						atualizarArquivoFornecedor(fornecedor);
						break;
					}
					f = f->prox;
				}
			}else
			{
				printf("	Fornecedor não encontrado :(\n\n");
			}
		}else
		{
			printf("	Não há fornecedores cadastrados :(\n\n");
		}
		printf("	Nova alteração(s/n): ");
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	menuAtualizarFornecedor(fornecedor);
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
	}
	return 0;
}

int carregaProdutoFornecedor(Produto **produto)
{
	FILE *file_produto = fopen("../DB/produto.bin","rb");
	Produto aux, *p, *novo, *anterior;

	/*se o arquivo existir*/
	if(file_produto != NULL)
	{
		while(fread(&aux, sizeof(Produto),1,file_produto) == 1)//lendo as structs no arquivo
		{
			p = *produto;//taking the node root
			anterior = p;//iniciando o anterior
			
			 novo = (Produto*) malloc(sizeof(Produto));//alocando novo espaço
			*novo = aux; //atribuindo os valores
			novo->prox = NULL;
			if(p == NULL)//caso nao exista fornecedores carregados ainda
			{
				*produto = novo;//atribui ao nó root
			}
			else
			{
				while(p != NULL)//percorre toda a lista de fornecedores
				{
					anterior = p;//guardando o ultimo elemento
					p = p->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
			}
		}
		fclose(file_produto);//encerrando o arquivo
	}
	return 0;
}
/*exibir fornecedores em lista*/
void exibirTodosFornecedores(Fornecedor **fornecedor)
{
	Fornecedor *f = *fornecedor;
	int total = 0;
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Exibindo todos os fornecedores\n\n");

	if(f == NULL)
	{
		printf("	Não há fornecedores cadastrados :(\n\n");
	}else{
		while(f != NULL)
		{
			printf("	Fornecedor: %s\n", f->nome);
			printf("	CNPJ: %s\n", f->cnpj);
			printf("	E-mail: %s\n", f->email);
			printf("	Telefone: %s\n", f->telefone);
			printf("	------------------\n\n");
			f = f->prox;
			total++;
		}
	}
	printf("	%d Resultado(s) encontrado(s).\n\n", total);
	pause();
	//menuFornecedor(fornecedor);
	return;
}

void cadastrarFornecedor(Fornecedor **fornecedor, Produto **produto)
{
	FILE *file_fornecedor, *file_produto;
	Fornecedor *f, *anterior, *novo;
	Produto *p, *p_anterior, *p_novo;
	char opcao;
	
	do{
		f = *fornecedor;//taking the node root
		p = *produto;//taking the product node
		anterior = f;//iniciando o anterior
		p_anterior = p;
		novo = (Fornecedor*) malloc(sizeof(Fornecedor));//alocando
		p_novo = (Produto*) malloc(sizeof(Produto));//alocando
		file_fornecedor = fopen("../DB/fornecedores.bin","ab");
		file_produto = fopen("../DB/produto.bin","ab");
		limparTela();
		printf("                                     %s", now());
	    marca();	
	    printf("       		      Cadastro de Fornecedores\n\n");
	    printf(" 		Empresa: ");
	    scanf(" %[^\n]s", novo->nome);
	    stringMaiusculo(novo->nome);
	    
	    //caso o fornecedor não esteja cadastrado continue o cadastro
	    if(!existeFornecedor(f, novo->nome))
	    {
			printf(" 		E-mail: ");
			scanf(" %[^\n]s", novo->email);
			printf(" 		Telefone: ");
			scanf(" %[^\n]s", novo->telefone);
			printf(" 		CNPJ: ");
			scanf(" %[^\n]s", novo->cnpj);
			printf(" 		Produto oferecido: ");
			scanf(" %[^\n]s", p_novo->nome);
			stringMaiusculo(p_novo->nome);
			p_novo->prox = NULL;
			novo->prox = NULL;
			strcpy(p_novo->nomeFornecedor, novo->nome);
			//se nao houver fornecedores cadastrados
			if(f == NULL)
			{
				*fornecedor = novo;
				*produto = p_novo;
			}else
			{
				while(f != NULL)//percorre toda a lista de fornecedores
				{
					anterior = f;//guardando o ultimo elemento
					f = f->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
				while(p != NULL)//percorre toda a lista de produtos do fornecedor
				{
					p_anterior = p;//guardando o ultimo elemento
					p = p->prox;//andando pela lista
				}
				p_anterior->prox = p_novo;
			}
			if(fwrite(novo,sizeof(Fornecedor),1,file_fornecedor) != 0 && fwrite(p_novo,sizeof(Produto),1,file_produto) != 0) printf(" 		Cadastrado com sucesso :)\n\n");
			else printf(" 		Problema ao cadastrar fornecedor :(\n\n");
		}else
		{
			printf(" 		Fornecedor já cadastrado!\n\n");
		}
	    fclose(file_fornecedor);
	    printf(" 		Novo cadastro(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao != 'n');
	return;
}

void deletarFornecedor(Fornecedor **fornecedor)
{
	Fornecedor *f = *fornecedor;
	Fornecedor *anterior = f;
	Fornecedor *trash;
	char opcao;
	char nomeFornecedor[30];
	
	do{
	  f = *fornecedor;
	  anterior = f;
	  limparTela();
	  printf("                                        %s",now());
	  marca();	
	  printf("\t\t\t    Excluir Fornecedor\n\n"); 	
	 
	  if(f != NULL)
	  {
		printf("	Nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		if(existeFornecedor(f, nomeFornecedor))//caso exista o fornecedor informado
		{
			while(f != NULL)//percorrendo a lista
			{
				if(strcmp(f->nome, nomeFornecedor) == 0)//se encontrou
				{
					if(f == *fornecedor)//caso seja o primeiro elemento
					{
						*fornecedor = f->prox;
					}else{
						anterior->prox = f->prox;
					}
					trash = f;
					free(trash);
				}
				anterior = f;
				f = f->prox;
			}
			//atualiza o arquivo com a lista	
			atualizarArquivoFornecedor(fornecedor);
			printf("	Excluído com sucesso!\n\n");
		}else
		{
			printf("	Esse fornecedor não está cadastrado :(\n\n");
		}
	  }else
	  {
		printf("	Não há fornecedores cadastrados :(\n\n");
	  }
	  printf("	Nova remoção(s/n): ");
	  scanf(" %c", &opcao);
	}while(opcao != 'n');
	return;
	//menuFornecedor(fornecedor);
}
/*atualiza o arquivo de fornecedores caso haja alguma alteração*/
void atualizarArquivoFornecedor(Fornecedor **fornecedor)
{
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","wb");
	Fornecedor *f = *fornecedor;
	
	if(file_fornecedor != NULL)
	{
		while(f != NULL)
		{
			fwrite(f,sizeof(Fornecedor),1,file_fornecedor);
			f = f->prox;
		}
		fclose(file_fornecedor);
	}
}
/*atualizar o arquivo de produtos de fornecedor caso haja alguma alteracao*/
void atualizarArquivoProduto(Produto **produto)
{
	FILE *file_produto = fopen("../DB/produto.bin","wb");
	
	Produto *p = *produto;
	
	if(file_produto != NULL)
	{
		while(p != NULL)
		{
			fwrite(p,sizeof(Produto),1,file_produto);
			p = p->prox;
		}
		fclose(file_produto);
	}
}

/*menu do fornecedor*/
void menuFornecedor(Fornecedor **fornecedor, Produto **produto)
{
	 int opcao;	
	 do{
	    limparTela();
	    printf("                                        %s",now());
		marca();	
	    printf("\t\t\t    Fornecedores\n\n");
	    printf("\t   1-Cadastrar    6-Buscar produtos de um fornecedor\n\t   2-Excluir      7-Cadastrar novo produto\n\t   3-Informações  8-Excluir um produto\n\t   4-Procurar     9-Consultar fornecedores de um produto\n\t   5-Atualizar    0-Voltar\n\n");
		printf("\t   Opção: ");
		scanf("%d", &opcao);
	 
		switch(opcao)
		{
			case 1:
				cadastrarFornecedor(fornecedor,produto);
				menuFornecedor(fornecedor, produto);
			break;
			case 2:
				deletarFornecedor(fornecedor);
				menuFornecedor(fornecedor, produto);
			break;
			case 3:
				exibirTodosFornecedores(fornecedor);
				menuFornecedor(fornecedor, produto);
			break;
			case 4:
				procurarFornecedor(fornecedor);
				menuFornecedor(fornecedor, produto);
			break;
			case 5:
				menuAtualizarFornecedor(fornecedor);
				menuFornecedor(fornecedor, produto);
			break;
			case 6:
				exibirProdutosFornecedores(fornecedor, produto);
			break;
			case 7:
				adicionarProdutosFornecedor(fornecedor, produto);
				menuFornecedor(fornecedor, produto);
			break;
			case 8:
				//excluirProdutoFornecedor();
			break;
			case 9:
				//buscaProdutosFornecedor();
			break;
			case 0:
				return;
			break;
		}	 
	 }while(opcao > 9 || opcao < 0);	
}

void procurarFornecedor(Fornecedor **fornecedor)
{
	char escolha;
	char nomeFornecedor[30];
	Fornecedor *f = *fornecedor;
	
	do{
		limparTela();
		f = *fornecedor;
		printf("                                        %s",now());
		marca();	
	    printf("\t\tExibir um fornecedor específico\n\n");
		   
		printf("	Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//tranformao nome do fornecedor em maiusculo
		if(fornecedor != NULL)
	    {
		   if(existeFornecedor(f, nomeFornecedor))
		   {
				while(f != NULL)
				{
					if(strcmp(f->nome, nomeFornecedor) == 0)
					{
						printf("\n	Fornecedor: %s\n", f->nome);
						printf("	CNPJ: %s\n", f->cnpj);
						printf("	E-mail: %s\n", f->email);
						printf("	Telefone: %s\n", f->telefone);
						printf("	------------------\n\n");	
					}	
					f = f->prox;	
				}
		   }else
		   {
				printf("	Esse fornecedor não está cadastrado :(\n\n");
		   }
		  }else
		  {
			printf("	Não há fornecedores cadastrados :(\n\n");
		  }
		  printf("	Nova busca(s/n): ");
		  scanf(" %c", &escolha);	
	}while(escolha != 'n');
	limparTela();
	return;
}

/*#PEndente*/
void adicionarProdutosFornecedor(Fornecedor **fornecedor,Produto **produto)
{
	char escolha;	
	char nomeFornecedor[30];
	Produto *p;
	Fornecedor *f;
	Produto *novo_produto, *anterior;
	
	do{
			p = *produto;
			f = *fornecedor;
			anterior = p;
			novo_produto = (Produto*) malloc(sizeof(Produto));
			novo_produto->prox = NULL;
			limparTela();
			printf("                                        %s",now());
			marca();	
			printf("\t\tAdicionar produtos\n\n");
			
			printf(" Informe o nome do fornecedor: ");
			scanf(" %[^\n]s", nomeFornecedor);
			stringMaiusculo(nomeFornecedor);//transforma o nome do fornecedor em maiusculo
		
			//se existe o fornecedor
			if(existeFornecedor(f, nomeFornecedor))
			{	
				printf("	Informe o nome do produto: ");
				scanf(" %[^\n]s", novo_produto->nome);
				stringMaiusculo(novo_produto->nome);
				
				//verificar se o fornecedor ja possui esse produto, caso nao
				if(existeProdutoFornecedor(nomeFornecedor,novo_produto->nome, p) == 0)
				{
					strcpy(novo_produto->nomeFornecedor, nomeFornecedor);
					while(p != NULL)
					{
						anterior = p;
						p = p->prox;
					}
					anterior->prox = novo_produto;
					printf("	Atualizado com sucesso :)\n\n");
					atualizarArquivoProduto(produto);
				}else
				{
					printf("	Esse produto ja está cadastrado com esse fornecedor :(\n\n");	
				}
			}
			else
			{
				printf("	Não há fornecedor cadastrado :(\n\n");	
			}
			
		  printf("	Nova inserção(s/n): ");
		  scanf(" %c", &escolha);
	}while(escolha != 'n');
}

int existeProdutoFornecedor(char nomeFornecedor[], char nomeProduto[], Produto *produto)
{
	while(produto != NULL)
	{
		if(strcmp(produto->nome, nomeProduto) == 0 && strcmp(produto->nomeFornecedor, nomeFornecedor) == 0)
		{
			return 1;
		}
	 	produto = produto->prox;
	}
	return 0;
}

int liberarFornecedor(Fornecedor **fornecedor)
{
	if(*(fornecedor) == NULL) return 0;
	
	Fornecedor *p = *(fornecedor);
	Fornecedor *trash = p;
	
	while(p != NULL)
	{
		trash = p;
		p = p->prox;
		free(trash);
	}
	return 1;
}

int liberarProduto(Produto **produto)
{
	if(*(produto) == NULL) return 0;
	
	Produto *p = *(produto);
	Produto *trash = p;
	
	while(p != NULL)
	{
		trash = p;
		p = p->prox;
		free(trash);
	}
	return 1;
}

void listaProduto(Produto *p)
{
	while(p != NULL)
	{
		printf("Produto: %s  Fornecedor %s\n", p->nome, p->nomeFornecedor);
		p = p->prox;
	}

}

void exibirProdutosFornecedores(Fornecedor **f ,Produto **p)
{
	Produto *produto = *p;
	Fornecedor *fornecedor = *f;
	char nomeFornecedor[30];
	int total = 0;
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Exibindo todos os produtos de um fornecedor\n\n");

	if(p == NULL)
	{
		printf("	Não há produtos cadastrados :(\n\n");
	}else{
		printf(" Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//transforma o nome do fornecedor em maiusculo
		
		if(existeFornecedor(fornecedor, nomeFornecedor) == 0)
		{
			while(produto != NULL)
			{
				if(strcmp(produto->nomeFornecedor, nomeFornecedor) == 0)
				{
					printf("	Produto: %s\n", produto->nome);
					produto = produto->prox;
					total++;
				}
			}
		}
	}
	printf("	%d Resultado(s) encontrado(s).\n\n", total);
	pause();
	return;
}
