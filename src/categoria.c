#include "../include/config.h"

int inserirCategoria()
{
	FILE *file_categoria;
	Categoria categoria;
	char opcao;

	file_categoria = fopen("../DB/categoria.bin","ab");	
	
	do
	{
	   limparTela();
	   printf("                                        %s",now());
	   marca();	
	   printf("\n\t\t       Cadastro de Categorias\n\n");
	   printf("Nome da Categoria: ");
	   scanf(" %[^\n]s", categoria.nomeCategoria);
	   stringMaiusculo(categoria.nomeCategoria);
	   //caso cadastre com sucesso
	   if(fwrite(&categoria,sizeof(Categoria),1,file_categoria) != 0)
	   {
			printf("\n Cadastrado com sucesso!\n\n");
	   }else{
		    printf("\n Cadastro não realizado!\n\n");
	   } 	
	   printf(" Novo cadastro(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	fclose(file_categoria);
	limparTela();
	menuCategoria();
	
	return 0;
}

void menuCategoria()
{
	 int opcao;	
	 limparTela();
	 printf("                                        %s",now());
	 marca();	
	 printf("\n\t\t\t      Categorias\n\n");
	 printf("\t      1-Cadastrar Categoria    3-Excluir Categoria\n\t      2-Listar Categorias      0-Voltar\n");	
	 printf("\n\t      Opção: ");
	 scanf("%d", &opcao);
	 
	 switch(opcao)
	 {
		case 1:inserirCategoria();
			   break;
		case 2:exibirCategoria();
			   break;
		case 3:deletarCategoria();
			   break;
		case 0: return;
		default: printf(" Opcao Invalida, voltando ao menu principal! \n");
			pause();
			return;
	 }
}

void exibirCategoria()
{
	Categoria categoria;
	FILE *file_categoria = fopen("../DB/categoria.bin","rb");
	limparTela();
	printf("                                        %s",now());
	marca();
	printf("\n\t\t\t Exibir Categorias\n\n");
	while(fread(&categoria,sizeof(Categoria),1,file_categoria) == 1)
	{
		printf(" Nome da Categoria: %s\n", categoria.nomeCategoria);
	}
	fclose(file_categoria);		
	pause();	
	menuCategoria();
}

int deletarCategoria()
{
	char nomeCategoria[30];
	Categoria categoria;
	FILE *file_categoria = fopen("../DB/categoria.bin","rb");
	FILE *auxCategoria = fopen("../DB/auxCategoria.bin","wb");
	char opcao;
	int encontrou = 0;
	
	do
	{
	   limparTela();
	   printf("                                        %s",now());
	   marca();	
	   printf("\n\t\t\t Deletar Categoria\n\n");
	   printf(" Qual Categoria deseja remover: ");
	   scanf(" %[^\n]s", nomeCategoria);
	   stringMaiusculo(nomeCategoria);
	   
	   while(fread(&categoria,sizeof(Categoria),1,file_categoria) == 1)
	   {
			if(strcmp(categoria.nomeCategoria, nomeCategoria) == 0)
			{
				encontrou = 1;
			}else{
				fwrite(&categoria, sizeof(Categoria), 1, auxCategoria);
			}
	   }
	   //caso tenha encontrado a categoria
	   if(!encontrou) printf(" Categoria não encontrada!\n\n");
	   else printf(" Removido com sucesso!\n\n"); 
	   
	   fclose(file_categoria);
	   fclose(auxCategoria);
	   
	   remove("../DB/categoria.bin");
	   rename("../DB/auxCategoria.bin", "../DB/categoria.bin");
	   
	   printf(" Nova exclusão(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	limparTela();
	menuCategoria();
	return 0;
}

int existeNomeCategoria(char nomeCategoria[])
{
	FILE *file_categoria = fopen("../DB/categoria.bin","rb+");
	Categoria categoria;
	while(fread(&categoria,sizeof(Categoria),1, file_categoria) == 1)
	{
		if(strcmp(categoria.nomeCategoria, nomeCategoria) == 0)
		{
			fclose(file_categoria);
			return 1;	
		} 
	}
	fclose(file_categoria);
	menuCategoria();
	return 0;
}
