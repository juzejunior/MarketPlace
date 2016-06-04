#include "../include/config.h"

void menuEstoque()
{
	int opcao;		
	limparTela();
	organizarEstoque();//chamada para organização do estoque por data de validade
	deletarProdutosZerados();//deleta os produtos que esgotaram
	printf("                                        %s",now());
	marca();	
	printf("\t\t\t    Estoque\n\n");
	printf("\t      1-Fazer Novo Pedido    4-Excluir Produtos\n\t      2-Listar Produtos      0-Voltar\n\t      3-Colocar para Venda");
	checarQuantidade();//verificacao da quantidade de cada produto para sugestão de reposição
	printf("\n\t      Opção: ");
	scanf("%d", &opcao);
	switch(opcao)
	{
		case 1: inserirProduto();
			break;
		case 2: menuExibir();
			break;
		case 3: retirarDoEstoque();
			break;
		case 4: deletarProduto();
			break;
		case 0: 
			break;
		default: printf(" Opcao Invalida, voltando ao menu principal! \n");
			pause();
			break;
	}
}
/*opções de busca do estoque*/
void menuExibir()
{
	int opcao;		
	limparTela();
	marca();
	printf("\n       1-Listar por Categorias           4-Listar por Quantidade");
	printf("\n       2-Listar por Data de Validade     5-Listar por Busca");
	printf("\n       3-Listar por Fornecedor");
	printf("\n\n       Opção: ");
	scanf("%d", &opcao);
	limparBuffer();
	switch(opcao)
	{
		case 1: exibirPorCategoria();
			break;
		case 2: exibirAleatoriamente();
			break;
		case 3: exibirPorFornecedor();
			break;
		case 4: exibirPorQuantidade();
			break;	
		case 5: exibirPorBusca();
			break;
	}
}
/*exibe todos os produtos pertecentes a uma categoria*/
void exibirPorCategoria()
{
	int encontrou;
	char opcao;
	char nomeCategoria[30];
	Produto produto;
	FILE *file_estoque;
	
	do
	{
		limparTela();
		encontrou = 0;
		printf("\n Digite o nome da categoria: ");
		scanf (" %[^\n]s", nomeCategoria);
		stringMaiusculo(nomeCategoria);
		limparBuffer();
		printf("\n\n Categoria: %s\n", nomeCategoria);
		file_estoque = fopen("../DB/estoque.bin", "rb");
		while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
		{
			if (strcmp(produto.nomeCategoria, nomeCategoria) == 0)
			{
				encontrou = 1;
				printf("\tNome: %s\n", produto.nome);
			}
		}
		fclose(file_estoque);
		if (!encontrou) printf(" Produto nao encontrado!");
		printf(" Nova pesquisa(s/n): ");
		scanf(" %c", &opcao);
		limparBuffer();	
	}while(opcao != 'n');
	pause();
	menuEstoque();
}
/*Exibe todos os produtos de forma aleatorio*/
void exibirAleatoriamente()
{
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin","rb");
	
	limparTela();
	
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		printf(" Nome: %s\n", produto.nome);
		printf(" Nome do Fornecedor: %s\n", produto.nomeFornecedor);
		printf(" Nome da Categoria: %s\n", produto.nomeCategoria);
		printf(" Quantidade: %d\n", produto.quantidade);
		printf(" Vencimento: %d/%d/%d\n", produto.dia, produto.mes, produto.ano);
		printf(" Preco: %.2f\n\n", produto.preco);
	}
	
	fclose(file_estoque);
	pause();
	menuEstoque();			
}
/*exibe todos os produtos com seus respectivos fornecedores ou todos os produtos de um forne-
 * cedor especifico.
 * */
void exibirPorFornecedor()
{
	int opcao;
	char nomeFornecedor[30];
	Fornecedor fornecedor;
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	Produto produto;
	FILE *file_estoque;
	limparTela();
	printf(" 1-Exibir Todos os Produtos\n");
	printf(" 2-Exibir de um Fornecedor Especifico\n");
	printf(" Opcao: ");
	scanf ("%d", &opcao);
	limparBuffer();	
	if (opcao == 1){
		while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
		{
			printf(" Nome do Fornecedor: %s\n", fornecedor.nome);
			file_estoque = fopen("../DB/estoque.bin","rb"); 
			while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
			{
				if(strcmp(fornecedor.nome, produto.nomeFornecedor) == 0){
					printf("\tNome do Produto: %s\n", produto.nome);
				}
			}
			fclose(file_estoque);
		}
	}else{
		printf(" Digite o nome do Fornecedor: ");
		scanf (" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		limparBuffer();
		while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
		{
			if(strcmp(fornecedor.nome, nomeFornecedor) == 0){
				printf(" Nome do Fornecedor: %s\n", fornecedor.nome);
				file_estoque = fopen("../DB/estoque.bin","rb"); 
				while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
				{
					if(strcmp(fornecedor.nome, produto.nomeFornecedor) == 0){
						printf("\tNome do Produto: %s\n", produto.nome);
					}
				}
				fclose(file_estoque);
			}
		}
	}
	fclose(file_fornecedor);
	pause();
	menuEstoque();
}
/*exibe os produtos mostrando sua quantidade dentro do estoque*/
void exibirPorQuantidade(){
	int encontrou;
	Produto produto;
	FILE *file_estoque;
	limparTela();
	encontrou = 0;
	file_estoque = fopen("../DB/estoque.bin", "rb");
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		encontrou = 1;
		printf("\tNome: %s\n", produto.nome);
		printf("\tQuantidade: %d\n\n", produto.quantidade);
	}
	fclose(file_estoque);
	if (!encontrou) printf(" Produto nao encontrado!");
	pause();
	menuEstoque();
}
/*busca especifica por nome do produto*/
void exibirPorBusca()
{
	int achouProduto = 0;
	char nomeProduto[30];
	
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin", "rb");
	
	limparTela();
	printf(" Digite o produto que deseja saber mais informacoes: ");
	scanf (" %[^\n]s", nomeProduto);
	stringMaiusculo(nomeProduto);
	limparBuffer();	
	
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		if (strcmp(nomeProduto, produto.nome) == 0)
		{
			printf(" Nome: %s\n", produto.nome);
			printf(" Nome do Fornecedor: %s\n", produto.nomeFornecedor);
			printf(" Nome da Categoria: %s\n", produto.nomeCategoria);
			printf(" Quantidade: %d\n", produto.quantidade);
			printf(" Vencimento: %d/%d/%d\n", produto.dia, produto.mes, produto.ano);
			printf(" Preco: %.2f\n\n", produto.preco);
			achouProduto = 1;
		}
	}
	
	if(achouProduto == 0) printf(" Produto nao encontrado");
	
	fclose(file_estoque);
	pause();
	menuEstoque();
}
/*adiciona um produto ao estoque ou imncrementa um existente*/
int inserirProduto()
{
	char opcao;
	char opcao2;
	int achouProduto;
	int achouCategoria;
	int achouFornecedor;
	int achouProdutoFornecedor;
	
	FILE *file_produto;
	Produto produto;
	FILE *file_estoque;
	Produto estoque;
	FILE *file_deleta;
	do
	{
	   achouProduto = 0;
	   achouFornecedor = 0;
	   achouProdutoFornecedor = 0;
	   limparTela();	
	   printf("\t\tPedido de Produtos\n\n");
	   printf(" Nome: ");
	   scanf(" %[^\n]s", produto.nome);
	   printf(" Nome do Fornecedor: ");
	   scanf(" %[^\n]s", produto.nomeFornecedor);
	   printf(" Nome da Categoria: ");
	   scanf(" %[^\n]s", produto.nomeCategoria);
	   stringMaiusculo(produto.nome);
	   stringMaiusculo(produto.nomeCategoria);
	   stringMaiusculo(produto.nomeFornecedor);
	   achouFornecedor = existeFornecedor(produto.nomeFornecedor);
	   achouProdutoFornecedor = existeProdutoFornecedor(produto.nomeFornecedor, produto.nome);
	   achouCategoria = existeNomeCategoria(produto.nomeCategoria);
	   if (achouFornecedor != 0 && achouProdutoFornecedor == 1 && achouCategoria == 1)
	   {
			printf(" Quantidade: ");
			scanf(" %d", &produto.quantidade);
			printf(" Preço: ");
			scanf(" %f", &produto.preco);
			printf("\n Deseja adicionar validade(s/n)\n");
			printf(" Opcao: ");
			scanf(" %c", &opcao2);
			if(opcao2 == 's')
			{
				printf(" Validade: ");
				scanf("  %d/%d/%d", &produto.dia, &produto.mes, &produto.ano);
				while (valida_data(produto.dia, produto.mes, produto.ano)!=1)
				{
					printf(" Data Inválida!\n ");
					printf(" Validade: ");
					scanf(" %d/%d/%d", &produto.dia, &produto.mes, &produto.ano);
				}
			}else{
				produto.dia = NODATA;
				produto.mes = NODATA;
				produto.ano = NODATA;
			}
			file_produto = fopen("../DB/estoque.bin","ab");
			fclose(file_produto);
	   
			file_estoque = fopen("../DB/estoque.bin","rb");
			file_deleta = fopen("../DB/aux.bin","wb"); 
	   
			while(fread(&estoque,sizeof(Produto),1,file_estoque) == 1 && achouProduto == 0)
			{
				if (strcmp(estoque.nome, produto.nome) == 0 &&
					strcmp(estoque.nomeFornecedor, produto.nomeFornecedor) == 0 &&
					estoque.dia == produto.dia &&
					estoque.mes == produto.mes &&
					estoque.ano == produto.ano)
				{
					if (strcmp(estoque.nomeCategoria, produto.nomeCategoria) != 0)
					{
						printf("\n Produto com categoria diferente do estoque! \n");
						printf(" Digite o nome definitivo da categoria: ");
						scanf(" %[^\n]s", produto.nomeCategoria);
						stringMaiusculo(produto.nomeCategoria);
					}
					if (estoque.preco != produto.preco)
					{
						printf("\n Produto com preco diferente! \n");
						printf(" Digite o valor para o produto: ");
						scanf(" %f", &produto.preco);
					}
					produto.quantidade += estoque.quantidade;
					if(fwrite(&produto, sizeof(Produto), 1, file_deleta) != 0)
					{
						printf("\n Cadastrado com sucesso!\n\n");
					}else{
						printf("\n Cadastro não realizado!\n\n");
					}
					achouProduto = 1;
				}else{
					fwrite(&estoque, sizeof(Produto), 1, file_deleta);
				}   
			}
			fclose(file_estoque);
			fclose(file_deleta);
	   
			remove("../DB/estoque.bin");
			rename("../DB/aux.bin", "../DB/estoque.bin");
	   
			if(!achouProduto)
			{
				file_produto = fopen("../DB/estoque.bin","ab");
				if(fwrite(&produto,sizeof(Produto),1,file_produto) != 0)
				{
					printf("\n Cadastrado com sucesso!\n\n");
				}else{
					printf("\n Cadastro não realizado!\n\n");
				}
				fclose(file_produto);
			}
	   }else if (!achouFornecedor){
			printf(" Fornecedor não encontrado!\n");
			printf(" Deseja inserir um novofornecedor?  (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				inserirFornecedor();
			}else{
				return 0;
			}
	   }else if (!achouProdutoFornecedor){
		    printf(" Produto no Fonecedor nao encontrado!\n");
			printf(" Deseja inserir um novo produto no fornecedor? (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				adicionarProdutosFornecedor();
			}else{
				return 0;
			}
	   }else if (!achouCategoria){
		    printf(" Categoria nao encontrada!\n");
			printf(" Deseja inserir uma nova Categoria? (S/N) ");
			scanf(" %c", &opcao);	
			opcao = toupper(opcao);
			if (opcao == 'S'){
				inserirCategoria();
			}else{
				return 0;
			}
	   }
		printf(" Novo cadastro(s/n): ");
		scanf(" %c", &opcao);	
	}while(opcao != 'n');
	limparTela();
	menuEstoque();
	return 1;
}

int retirarDoEstoque()
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
	menuEstoque();
	return 1;
}

int deletarProduto()
{
	char opcao;
	char nomeProduto[30];
	char nomeFornecedor[30];
	int encontrou;
	
	FILE *file_produto;
	Produto produto;
	FILE *aux;
	
	do{
		encontrou = 0;
		limparTela();
		printf (" Produto que você deseja retirar do estoque: ");
		scanf (" %[^\n]s", nomeProduto);
		stringMaiusculo(nomeProduto);
		printf (" Fornecedor deste produto: ");
		scanf (" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);
		file_produto = fopen("../DB/estoque.bin","rb");
		aux = fopen("../DB/aux.bin","wb");
		while(fread(&produto,sizeof(Produto),1,file_produto) == 1)
		{
			if(strcmp(produto.nome, nomeProduto) == 0 &&
			   strcmp(produto.nomeFornecedor, nomeFornecedor) == 0)
			{
				encontrou = 1;
			}else{
				fwrite(&produto, sizeof(Produto), 1, aux);
			}
		}
	
		fclose(file_produto);
		fclose(aux);
	
		remove("../DB/estoque.bin");
		rename("../DB/aux.bin", "../DB/estoque.bin");
		
		if(!encontrou) printf(" Produto nao encontrado!\n");
		else printf(" Excluido com sucesso\n");
		
		printf(" Deseja excluir algum produto(s/n): ");
	    scanf(" %c", &opcao);	
	}while(opcao!='n');
	menuEstoque();
	return 1;
}

int deletarProdutosZerados()
{
	int encontrou = 0;
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin","ab");
	FILE *aux = fopen("../DB/aux.bin","ab");
	
	fclose(file_estoque);
	fclose(aux);
	
	file_estoque = fopen("../DB/estoque.bin","rb");
	aux = fopen("../DB/aux.bin","wb");
	
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		if(produto.quantidade == 0)
		{
			encontrou = 1;
		}else{
			fwrite(&produto, sizeof(Produto), 1, aux);
		}
	}
	fclose(file_estoque);
	fclose(aux);
	if(encontrou)printf(" Removido com sucesso");
	remove("../DB/estoque.bin");
	rename("../DB/aux.bin", "../DB/estoque.bin");
	return 1;
}

/*realiza a leitura de todos os elementos do estoque para organizar por data de validade*/
int organizarEstoque()
{
	int count = 0, i = 5;
	FILE *file_produto = fopen("../DB/estoque.bin","rb");
	Produto *produto, estoque;
	
	produto = (Produto *) malloc (sizeof(Produto) * i);
	while(fread(&estoque,sizeof(Produto),1,file_produto) == 1)
	{
		if (count == i)
			produto = (Produto *) realloc(produto, sizeof(Produto) * i + 5);
		produto[count] = estoque;
		count++;
	}
	fclose(file_produto);
	
	organizarPorData(produto, count);
	return 1;
}
/*Ordena o vetor de produtos por data de validade*/
void organizarPorData(Produto produto[], int n)
{
	int i, j;
	Produto aux;
	
	for(i = 1; i < n; i++)
	{
		aux = produto[i];
		for(j=i; (j>0) && (aux.ano < produto[j-1].ano); j--)
			produto[j] = produto[j-1];
		produto[j] = aux;
	}
	
	for(i = 1; i < n; i++)
	{
		aux = produto[i];
		for(j=i; (j>0) && (aux.mes < produto[j-1].mes); j--)
			produto[j] = produto[j-1];
		produto[j] = aux;
	}
	
	for(i = 1; i < n; i++)
	{
		aux = produto[i];
		for(j=i; (j>0) && (aux.dia < produto[j-1].dia); j--)
			produto[j] = produto[j-1];
		produto[j] = aux;
	}
	
	FILE *file_produto = fopen("../DB/estoque.bin","ab+");
	FILE *auxiliar = fopen("../DB/auxiliar.bin","ab+");
	for(i=0;i<n;i++) fwrite(&produto[i],sizeof(Produto),1,auxiliar);
	fclose(file_produto);
	fclose(auxiliar);
	
	remove("../DB/estoque.bin");
	rename("../DB/auxiliar.bin", "../DB/estoque.bin");
}

int checarQuantidade(){
	int achouProduto = 0;
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin", "rb+");
	while(fread(&produto,sizeof(Produto),1,file_estoque) == 1)
	{
		if (produto.quantidade < 5)
		{
			if(achouProduto == 0) printf("\n\tExistem produtos com menos de 5 unidades: ");
			printf("\t   Nome: %s\n", produto.nome);
			printf("\t   Quantidade: %d\n\n", produto.quantidade);
			achouProduto = 1;
		}
	}
	
	if(achouProduto == 0) return 0;
	fclose(file_estoque);
	return 1;
}
