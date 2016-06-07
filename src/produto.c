#include "../include/config.h"

void inicializarEstoque(Produto **produto)
{
	*produto = NULL;
}

int carregaEstoque(Produto **p)
{
	FILE *file_estoque = fopen("../DB/estoque.bin","rb");
	Produto aux, *estoque, *novo, *anterior;
	*p = NULL;
	/*se o arquivo existir*/
	if(file_estoque != NULL)
	{
		while(fread(&aux, sizeof(Produto),1,file_estoque) == 1)//lendo as structs no arquivo
		{
			estoque = *p;//taking the node root
			anterior = estoque;//iniciando o anterior
			
			 novo = (Produto*) malloc(sizeof(Produto));//alocando novo espaço
			*novo = aux; //atribuindo os valores
			novo->prox = NULL;
			if(estoque == NULL)//caso nao exista fornecedores carregados ainda
			{
				*p = novo;//atribui ao nó root
			}
			else
			{
				while(estoque != NULL)//percorre toda a lista de fornecedores
				{
					anterior = estoque;//guardando o ultimo elemento
					estoque = estoque->prox;//andando pela lista
				}
				anterior->prox = novo;//atribui o novo elemento
			}
		}
		fclose(file_estoque);//encerrando o arquivo
	}else{
		inicializarEstoque(p);
	}
	return 0;
}

void menuExibir(Produto **produto, Categoria **categoria, Fornecedor **fornecedor)
{
	int opcao;		
	limparTela();
	printf("                                        %s",now());
	marca();
	printf("\n       1-Listar Aleatoriamente           4-Listar por Quantidade");
	printf("\n       2-Listar por Categorias           5-Listar por Busca");
	printf("\n       3-Listar por Fornecedor           0-Voltar");
	printf("\n\n       Opção: ");
	scanf("%d", &opcao);
	limparBuffer();
	switch(opcao)
	{
		case 1: exibirAleatoriamente(produto);
			break;
		case 2: exibirPorCategoria(produto, categoria);
			break;
		case 3: exibirPorFornecedor(produto, fornecedor);
			break;
		case 4: exibirPorQuantidade(produto);
			break;	
		case 5: exibirPorBusca(produto);
			break;
		case 0: return;
		default: printf(" Opcao Invalida, voltando ao menu de estoque! \n");
			pause();
			return;
	}
}

int exibirAleatoriamente(Produto **produto)
{
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Listar o Estoque\n\n");
	Produto *p = *produto;
	if(p == NULL)
	{
		return 0;
	}else{
		while(p != NULL)
		{
			printf(" Nome: %s\n", p->nome);
			printf(" Nome do Fornecedor: %s\n", p->nomeFornecedor);
			printf(" Nome da Categoria: %s\n", p->nomeCategoria);
			printf(" Quantidade: %d\n", p->quantidade);
			printf(" Data de Entrada: %d/%d/%d\n", p->eDia, p->eMes, p->eAno);
			printf(" Vencimento: %d/%d/%d\n", p->dia, p->mes, p->ano);
			printf(" Preco: %.2f\n\n", p->preco);
			printf(" __________________________\n\n");
			p = p->prox;
		}
	}
		
	pause();	
	return 1;
}

int exibirPorCategoria(Produto **produto, Categoria **categoria)
{
	char nomeCategoria[30];
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       	  Listar Produtos por Categoria\n\n");
	Produto *p = *produto;
	Categoria *c = *categoria;
	if(p == NULL || c == NULL)
	{
		return 0;
	}else{
		while(c != NULL)
		{
			printf(" %s: \n", c->nomeCategoria);
			strcpy(nomeCategoria, c->nomeCategoria);
			while(p != NULL && strcmp (nomeCategoria, p->nomeCategoria) == 0)
			{
				printf("     Nome: %s\n", p->nome);
				p = p->prox;
			}
			c = c->prox;
			p = *produto;
		}
	}
		
	pause();	
	return 1;
}

int exibirPorFornecedor(Produto **produto, Fornecedor **fornecedor)
{
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       	  Listar Produtos por Fornecedor\n\n");
	Produto *p = *produto;
	Fornecedor *f = *fornecedor;
	if(p == NULL || f == NULL)
	{
		return 0;
	}else{
		while(f != NULL)
		{
			printf(" %s: \n", f->nome);
			while(p != NULL)
			{
				printf("     Nome: %s\n\n", p->nome);
				p = p->prox;
			}
			f = f->prox;
			p = *produto;
		}
	}
		
	pause();	
	return 1;
}

int exibirPorQuantidade(Produto **produto)
{
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Listar Quantidades\n\n");
	Produto *p = *produto;
	if(p == NULL)
	{
		return 0;
	}else{
		while(p != NULL)
		{
			printf(" Nome: %s\n", p->nome);
			printf(" Quantidade: %d\n\n", p->quantidade);
			p = p->prox;
		}
	}
		
	pause();	
	return 1;
}

int exibirPorBusca(Produto **produto)
{
	char nomeProduto[30];
	char nomeFornecedor[30];
	limparTela();
	printf("                                     %s", now());
	marca();	
	printf("       		      Listar por Busca\n\n");
	printf(" Nome do Produto: ");
	scanf(" %[^\n]s", nomeProduto);
	stringMaiusculo(nomeProduto);
	printf(" Nome do Fornecedor: ");
	scanf(" %[^\n]s", nomeFornecedor);
	stringMaiusculo(nomeFornecedor);
	Produto *p = *produto;
	if(p == NULL)
	{
		return 0;
	}else{
		while(p != NULL)
		{
			if ((strcmp(nomeProduto, p->nome) == 0) && (strcmp(nomeFornecedor, p->nomeFornecedor) == 0))
			{
				printf(" Nome: %s\n", p->nome);
				printf(" Quantidade: %d\n", p->quantidade);
				printf(" Vencimento: %d/%d/%d\n", p->dia, p->mes, p->ano);
				printf(" Preco: %.2f\n\n", p->preco);
				p = p->prox;
			}
		}
	}
		
	pause();	
	return 1;
}

int inserirProduto(Produto **produto, Categoria **categoria, Fornecedor **fornecedor, Produto **p_fornecedor)
{
	int achouCategoria = 0;
	int achouFornecedor = 0;
	int achouProdutoFornecedor = 0;
	time_t t = time(NULL);
	struct tm tm;
	tm = *localtime(&t);
	FILE *file_estoque;
	Produto *p, *anterior, *novo;
	char opcao, opcao2;
	
	do{
		p = *produto;//taking the node root
		anterior = p;//iniciando o anterior
		novo = (Produto*) malloc(sizeof(Produto));//alocando
		file_estoque = fopen("../DB/estoque.bin","ab");
		limparTela();
		printf("                                     %s", now());
	    marca();	
	    printf("       		      Cadastro de Produtos\n\n");
	    printf(" 		Nome do Produto: ");
	    scanf(" %[^\n]s", novo->nome);	
	    stringMaiusculo(novo->nome);
	    printf(" 		Nome do Fornecedor: ");
	    scanf(" %[^\n]s", novo->nomeFornecedor);	
	    stringMaiusculo(novo->nomeFornecedor);
	    printf(" 		Nome da Categoria: ");
	    scanf(" %[^\n]s", novo->nomeCategoria);	
	    stringMaiusculo(novo->nomeCategoria);
	    achouFornecedor = existeFornecedor(*fornecedor, novo->nomeFornecedor);
		achouProdutoFornecedor = existeProdutoFornecedor(novo->nomeFornecedor, novo->nome, *p_fornecedor);
		achouCategoria = existeCategoria(*categoria, novo->nomeCategoria);
	    
	    if (achouFornecedor != 0 && achouProdutoFornecedor == 1 && achouCategoria == 1)
		{
			printf(" 		Quantidade: ");
			scanf(" %d", &novo->quantidade);
			printf(" 		Preço: ");
			scanf(" %f", &novo->preco);
			novo->prox = NULL;
			novo->eDia = tm.tm_mday;
			novo->eMes = (tm.tm_mon + 1);
			novo->eAno = (tm.tm_year + 1900);
			printf("\n 		Deseja adicionar validade(s/n)\n");
			printf(" 		Opcao: ");
			scanf(" %c", &opcao2);
			if(opcao2 == 's')
			{
				printf(" 		Validade: ");
				scanf("  %d/%d/%d", &novo->dia, &novo->mes, &novo->ano);
				while (valida_data(novo->dia, novo->mes, novo->ano)!=1)
				{
					printf(" 		Data Inválida!\n ");
					printf(" 		Validade: ");
					scanf(" %d/%d/%d", &novo->dia, &novo->mes, &novo->ano);
				}
			}else{
				novo->dia = NODATA;
				novo->mes = NODATA;
				novo->ano = NODATA;
			}
		}else if (!achouFornecedor){
		    limparBuffer();
			printf(" Fornecedor não encontrado!\n");
			printf(" Deseja inserir um novofornecedor?  (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				cadastrarFornecedor(fornecedor, p_fornecedor);
				return 0;
			}else{
				return 0;
			}
	   }else if (!achouProdutoFornecedor){
		    limparBuffer();
		    printf(" Produto nao encontrado no fornecedor!\n");
			printf(" Deseja inserir um novo produto no fornecedor? (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				adicionarProdutosFornecedor(fornecedor, p_fornecedor);
				return 0;
			}else{
				return 0;
			}
	   }else if (!achouCategoria){
		    limparBuffer();
		    printf(" Categoria nao encontrada!\n");
			printf(" Deseja inserir uma nova Categoria? (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				cadastrarCategoria(categoria);
				return 0;
			}else{
				return 0;
			}
	   }
		//se nao houver fornecedores cadastrados
		if(p == NULL)
		{
			*produto = novo;
		}else{
			while(p != NULL)//percorre toda a lista de fornecedores
			{
				anterior = p;//guardando o ultimo elemento
				p = p->prox;//andando pela lista
			}
			anterior->prox = novo;//atribui o novo elemento
		}
		if(fwrite(novo,sizeof(Produto),1,file_estoque) != 0) printf(" 		Cadastrado com sucesso :)\n\n");
		else printf(" 		Problema ao cadastrar produto :(\n\n");
	    fclose(file_estoque);
	    printf(" 		Novo cadastro(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao != 'n');
	pause();
	return 1;	
}

int retirarDoEstoque(Produto **produtos)
{
	char opcao;
	char nomeProduto[30];
	char nomeFornecedor[30];
	int quantidade;
	
	FILE *file_produto;
	Produto produto;
	FILE *aux;
	
	do{
		limparTela();
		printf("                                        %s",now());
		marca();
		printf (" Produto que você deseja colocar a venda: ");
		scanf (" %[^\n]s", nomeProduto);
		stringMaiusculo(nomeProduto);
		printf (" Fornecedor deste produto: ");
		scanf (" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		printf (" Quantidade para colocar a venda: ");
		scanf (" %d", &quantidade);
		file_produto = fopen("../DB/estoque.bin","ab+");
		aux = fopen("../DB/aux.bin","ab+");
		while(fread(&produto,sizeof(Produto),1,file_produto) == 1)
		{
			if(strcmp(produto.nome, nomeProduto) == 0 &&
			   strcmp(produto.nomeFornecedor, nomeFornecedor) == 0)
			{
				if (produto.quantidade >= quantidade)
				{
					produto.quantidade = produto.quantidade - quantidade;
					printf(" Produto adicionado a venda!\n");
				}else{
					printf(" Não foi possivel colocar a venda!\n");
				}
			}
			fwrite(&produto, sizeof(Produto), 1, aux);
		}
	
		fclose(file_produto);
		fclose(aux);
	
		remove("../DB/estoque.bin");
		rename("../DB/aux.bin", "../DB/estoque.bin");
		
		printf(" Deseja adicionar mais algum pedigo a venda(s/n): ");
	    scanf(" %c", &opcao);	
	}while(opcao!='n');
	carregaEstoque(produtos);
	return 1;
}

int deletarEstoque(Produto **produto)
{
	char opcao, nomeProduto[30], nomeFornecedor[30];
	Produto p;
	FILE *file_estoque;
	FILE *file_aux;
	do{
		file_estoque = fopen("../DB/estoque.bin","rb");
		file_aux = fopen("../DB/aux.bin","wb");
		limparTela();
		printf("                                     %s", now());
		marca();	
		printf("       		      Deletar Estoque\n\n");
		printf(" 		Produto: ");
		scanf(" %[^\n]s", nomeProduto);	
		printf(" 		Fornecedor do Produto: ");
		scanf(" %[^\n]s", nomeFornecedor);	
	    stringMaiusculo(nomeProduto);
	    *produto = NULL;
	    while(fread(&p, sizeof(Produto),1,file_estoque) == 1)//lendo as structs no arquivo
		{
			if(strcmp(nomeProduto, p.nome) != 0 && strcmp(nomeFornecedor, p.nomeFornecedor) != 0)
			{
				fwrite(&p,sizeof(Produto),1,file_aux);
			}
		}
		fclose(file_estoque);
		fclose(file_aux);
		remove("../DB/estoque.bin");
		rename("../DB/aux.bin", "../DB/estoque.bin");
		printf(" 		Deletar mais um produto(s/n): ");
	    scanf(" %c", &opcao);
	}while(opcao!='n');
	carregaEstoque(produto);
	//menuCategoria(categoria);
	return 1;
}

void menuEstoque(Produto **produto, Categoria **categoria, Fornecedor **fornecedor, Produto **p_fornecedor)
{
	int opcao;		
	limparTela();
	carregaEstoque(produto);
	deletarProdutosZerados(produto);
	printf("                                        %s",now());
	marca();	
	printf("\t\t\t      Estoque\n\n");
	printf("\t      1-Fazer Novo Pedido    4-Excluir Produtos\n\t      2-Listar Produtos      0-Voltar\n\t      3-Colocar para Venda");
	checarQuantidade(produto);
	checarValidade(produto);
	printf("\n\n\t      Opção: ");
	scanf("%d", &opcao);
	switch(opcao)
	{
		case 1: inserirProduto(produto, categoria, fornecedor, p_fornecedor);
			break;
		case 2: menuExibir(produto, categoria, fornecedor);
			break;
		case 3: retirarDoEstoque(produto);
			break;
		case 4: deletarEstoque(produto);
			break;
		case 0: return;
		default: printf(" Opcao Invalida, voltando ao menu principal! \n");
			pause();
			break;
	}
	menuEstoque(produto, categoria, fornecedor, p_fornecedor);
}

int deletarProdutosZerados(Produto **produtos)
{
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin","ab");
	FILE *aux = fopen("../DB/aux.bin","ab");
	
	fclose(file_estoque);
	fclose(aux);
	
	file_estoque = fopen("../DB/estoque.bin","rb");
	aux = fopen("../DB/aux.bin","wb");
	
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		if(produto.quantidade != 0)
			fwrite(&produto, sizeof(Produto), 1, aux);
	}
	fclose(file_estoque);
	fclose(aux);
	remove("../DB/estoque.bin");
	rename("../DB/aux.bin", "../DB/estoque.bin");
	carregaEstoque(produtos);
	return 1;
}

int checarQuantidade(Produto **produto)
{
	int achouProduto = 0;
	Produto *p = *produto;
	while(p!=NULL)
	{
		if (p->quantidade < 5)
		{
			if(achouProduto == 0) printf("\n\tExistem produtos com menos de 5 unidades: ");
			printf("\n\t   Nome: %s", p->nome);
			printf("\n\t   Quantidade: %d\n", p->quantidade);
			achouProduto = 1;
		}
		p = p->prox;
	}
	
	if(achouProduto == 0) return 0;
	return 1;
}

int checarValidade(Produto **produto)
{
	int achouProduto = 0;
	time_t t = time(NULL);
	struct tm tm;
	tm = *localtime(&t);
	Produto *p = *produto;
	
	while(p!=NULL)
	{
		if(p->dia == tm.tm_mday &&
		   p->mes == (tm.tm_mon + 1) &&
		   p->ano == (tm.tm_year + 1900))
		{
			if(achouProduto == 0) printf("\n\n    Os seguintes produtos devem ser retirados do estoque pois estão vencidos: ");
			printf("\n\tNome: %s", p->nome);
			achouProduto = 1;
		}
		p = p->prox;
	}
	return 1;
}
