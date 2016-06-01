#include "../include/categoria.h"
#include "../include/config.h"
#include "config.c"

int inserirCategoria(){
	FILE *file_categoria;
	Categoria categoria;
	char opcao;

	file_categoria = fopen("../DB/categoria.bin","ab");	
	
	do{
	   limparTela();	
	   printf("        Cadastro de Categorias\n\n");
	   printf("Nome da Categoria: ");
	   scanf(" %[^\n]s", categoria.nomeCategoria);
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

void menuCategoria(){
	 int opcao;		
	 printf(" 1 - cadastrar | 2 - excluir | 3 - Listar Categorias\n\n");
	 printf(" Opção: ");
	 scanf("%d", &opcao);
	 
	 switch(opcao)
	 {
		case 1:inserirCategoria();
			   break;
		case 2:deletarCategoria();
			   break;
		case 3:exibirCategoria();
			   break;
		case 4:break;	
	 }
}

int exibirCategoria(){
	
	Categoria categoria;
	FILE *file_categoria = fopen("../DB/categoria.bin","rb");
	
	while(fread(&categoria,sizeof(Categoria),1,file_categoria) == 1)
	{
		printf(" Nome da Categoria: %s\n", categoria.nomeCategoria);
	}
	fclose(file_categoria);			
	return 0;
}

int deletarCategoria(){
	char nomeCategoria[30];
	Categoria categoria;
	FILE *file_categoria = fopen("../DB/categoria.bin","rb");
	FILE *auxCategoria = fopen("../DB/auxCategoria.bin","wb");
	char opcao;
	int encontrou = 0;
	
	do{
	   limparTela();	
	   printf("        Deletar Categoria\n\n");
	   printf(" Qual Categoria deseja remover: ");
	   scanf(" %[^\n]s", nomeCategoria);
	   
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
