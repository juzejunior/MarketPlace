#include "../include/config.h"

void menuEstoque()
{
	int opcao;		
	limparTela();
	deletarProdutosZerados();
	printf(" 1-Fazer Novo Pedido | 2-Listar Produtos | 3-Colocar para Venda | 4-Excluir Produtos | 5-Voltar");
	printf("\n\n Opção: ");
	scanf("%d", &opcao);
	limparBuffer();
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
		case 5: 
			break;
	}
}

void menuExibir()
{
	int opcao;		
	limparTela();
	printf("\n 1-Listar Aleatoriamente");
	printf("\n 2-Listar por Categorias");
	printf("\n 3-Listar por Data de Validade");
	printf("\n 4-Listar por Fornecedor");
	printf("\n 5-Listar por Busca");
	printf("\n\n Opção: ");
	scanf("%d", &opcao);
	limparBuffer();
	switch(opcao)
	{
		case 1: exibirAleatoriamente();
			break;
		case 2: exibirPorCategoria();
			break;
		case 3:
			break;
		case 4: exibirPorFornecedor();
			break;
		case 5: exibirPorBusca();
			break;
	}
}

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
				printf("\tQuantidade: %d\n\n", produto.quantidade);
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

void exibirPorBusca()
{
	int achouProduto = 0;
	char nomeProduto[30];
	
	Produto produto;
	FILE *file_estoque = fopen("../DB/estoque.bin", "rb");
	
	limparTela();+
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

int inserirProduto()
{
	char opcao;
	char opcao2;
	int achouProduto;
	int achouFornecedor;
	
	FILE *file_produto;
	Produto produto;
	FILE *file_estoque;
	Produto estoque;
	FILE *file_deleta;
	FILE *file_fornecedor;
	Fornecedor fornecedor;
	do
	{
	   achouProduto = 0;
	   achouFornecedor = 0;
	   limparTela();	
	   printf("\t\tPedido de Produtos\n\n");
	   printf(" Nome: ");
	   scanf(" %[^\n]s", produto.nome);
	   printf(" Nome do Fornecedor: ");
	   scanf(" %[^\n]s", produto.nomeFornecedor);
	   stringMaiusculo(produto.nome);
	   stringMaiusculo(produto.nomeFornecedor);
	   file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	   while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
	   {
		   if(strcmp(fornecedor.nome, produto.nomeFornecedor) == 0)
		   {
			   achouFornecedor = 1;
		   }
	   }
	   fclose(file_fornecedor);
	   if (achouFornecedor==1)
	   {
			printf(" Nome da Categoria: ");
			scanf(" %[^\n]s", produto.nomeCategoria);
			stringMaiusculo(produto.nomeCategoria);
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
		}else{
			printf(" Fornecedor não encontrado!\n");
			printf(" Deseja um novo fornecedor? ");
			scanf(" %c", &opcao);	
			if (opcao == 's'){
				inserirFornecedor();
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
	
	FILE *file_produto = fopen("../DB/estoque.bin","rb");
	Produto produto;
	FILE *aux = fopen("../DB/aux.bin","wb");
	
	//organizarEstoque();
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

int organizarEstoque()
{
	FILE *file_produto = fopen("../DB/estoque.bin","rb");
	Produto produto;
	Organizar *organizar, *no_organizar, *p_organizar;
	organizar = NULL;
	
	while(fread(&produto,sizeof(Produto),1,file_produto) == 1)
	{
		if (organizar == NULL){
			organizar = (Organizar *)malloc (sizeof(Organizar));
			organizar->produto = produto;
			organizar->prox = NULL;
			p_organizar = organizar;
		}else{
			no_organizar = (Organizar *)malloc (sizeof(Organizar));
			if (no_organizar == NULL) return 0;
			no_organizar->produto = produto;
			no_organizar->prox = NULL;
			p_organizar->prox = no_organizar;
			p_organizar = p_organizar->prox;
		}
	}
	fclose(file_produto);
	
	return 1;
}
