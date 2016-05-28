#include "../include/config.h"

int inserirFornecedor()
{
	FILE *file_fornecedor;
	Fornecedor fornecedor;
	char opcao;

	file_fornecedor = fopen("../DB/fornecedores.bin","ab");	
	
	do{
	   limparTela();	
	   printf("        Cadastro de Fornecedores\n\n");
	   printf(" Nome: ");
	   scanf(" %[^\n]s", fornecedor.nome);
	   stringMaiusculo(fornecedor.nome);
	   printf(" E-mail: ");
	   scanf(" %[^\n]s", fornecedor.email);
	   printf(" Telefone: ");
	   scanf(" %[^\n]s", fornecedor.telefone);
	   printf(" CNPJ: ");
	   scanf(" %[^\n]s", fornecedor.cnpj);
	   //caso cadastre com sucesso
	   if(fwrite(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) != 0)
	   {
			printf("\n Fornecedor cadastrado com sucesso!\n\n");
	   }else{
		    printf("\n Cadastrodo fornecedor não realizado!\n\n");
	   } 	
	   printf(" Novo cadastro(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	fclose(file_fornecedor);
	limparTela();
	menuFornecedor();
	return 0;
}

int deletarFornecedor()
{
	char nomeFornecedor[30];
	Fornecedor fornecedor;
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	FILE *aux = fopen("../DB/aux.bin","wb");
	char opcao;
	int encontrou = 0;
	
	do{
	   limparTela();	
	   printf("        Deletar Fornecedor\n\n");
	   printf(" Qual fornecedor deseja remover: ");
	   scanf(" %[^\n]s", nomeFornecedor);
	   stringMaiusculo(nomeFornecedor);
	   
	   while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
	   {
			if(strcmp(fornecedor.nome, nomeFornecedor) == 0)
			{
				encontrou = 1;
			}else{
				fwrite(&fornecedor, sizeof(Fornecedor), 1, aux);
			}
	   }
	   //caso tenha encontrado o fornecedor
	   if(!encontrou) printf(" Fornecedor não encontrado!\n\n");
	   else printf(" Removido com sucesso!\n\n"); 
	   
	   fclose(file_fornecedor);
	   fclose(aux);
	   
	   remove("../DB/fornecedores.bin");
	   rename("../DB/aux.bin", "../DB/fornecedores.bin");
	   
	   printf(" Nova exclusão(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	limparTela();
	menuFornecedor();
	return 0;
}

int exibirFornecedor()
{
	Fornecedor fornecedor;
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	
	while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
	{
		printf(" Nome: %s\n", fornecedor.nome);
		printf(" CNPJ: %s\n", fornecedor.cnpj);
		printf(" E-mail: %s\n", fornecedor.email);
		printf(" Telefone: %s\n\n", fornecedor.telefone);
	}
	
	fclose(file_fornecedor);			
	return 0;
}

void atualizarFornecedor()
{
	//int opcao;		
	/*
	do{
		limparTela();
		printf(" 1-nome | 2-email | 3-telefone\n\n");
		scanf("%d", &opcao);	
    }*/
}

void menuFornecedor()
{
	 int opcao;		
	 printf(" 1-cadastrar | 2-excluir | 3-informações | 4-Atualizar\n\n");
	 printf(" Opção: ");
	 scanf("%d", &opcao);
	 
	 switch(opcao)
	 {
		case 1:
			inserirFornecedor();
		break;
		case 2:
			deletarFornecedor();
		break;
		case 3:
			exibirFornecedor();
		break;
		case 4:
		break;	
	 }
}


