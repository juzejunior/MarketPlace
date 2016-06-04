#include "../include/config.h"
#include "../include/manager.h"


void criarManager()
{
	FILE *file = fopen("../DB/manager.bin","wb");
	Manager usuario;
	
	if(file != NULL)
	{
		strcpy(usuario.usuario,"gerente");
		strcpy(usuario.senha, "minhasenha");
		encrypt(usuario.senha);
		fwrite(&usuario,sizeof(Manager),1,file);
	}else{
		printf(" Não foi possivel abrir o arquivo :(\n\n");
	}	
	fclose(file);
}

void perfil()
{
	int opcao;
	
	do{
	  	limparTela();
		printf("                                     %s", now());
		marca();
		printf("     Configuração de Usuário\n\n");
		printf(" 1 - Inicio | 2 - atualizar usuário | 3 - atualizar senha\n\n Opção: ");	
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1: return;
			case 2: atualizarUsuario();
			break;
			case 3: atualizarSenha();
			break;
		}
	}while(opcao < 1 || opcao > 3);

	limparTela();
}

void atualizarUsuario()
{
	FILE *file = fopen("../DB/manager.bin","rb+");
	Manager m;
	char user[30]; 
	
	if(file != NULL)
	{
		limparTela();
		printf("                                     %s", now());
		marca();
		fread(&m,sizeof(Manager), 1, file);
		printf(" Informe um novo nome de usuário: ");
		scanf(" %[^\n]s", user);
		strcpy(m.usuario, user);
		fseek(file,sizeof(Manager)*0, SEEK_SET);
		fwrite(&m,sizeof(Manager), 1, file);
	 }
	 perfil();
}

void atualizarSenha()
{
	FILE *file = fopen("../DB/manager.bin","rb+");
	Manager m;
	char senha[30];
	char nova_senha[30];
	int opcao;
	
	if(file != NULL)
	{
		fread(&m,sizeof(Manager),1,file);
		encrypt(m.senha);
		limparTela();
		printf("                                     %s", now());
		marca();
		printf(" Informe a senha atual: ");
		scanf(" %[^\n]s", senha);
		if(strcmp(m.senha,senha) == 0)
		{
			printf(" Informe a nova senha: ");
			scanf(" %[^\n]s", nova_senha);
			encrypt(nova_senha);
			strcpy(m.senha,nova_senha);
			fseek(file,sizeof(Manager)*0, SEEK_SET);
			fwrite(&m,sizeof(Manager), 1, file);
			printf(" Senha alterada com sucesso :)\n\n");
		}else{
			printf(" Senha incorreta!\n\n");
		}
	}
	printf(" 1-Voltar\n\n Opção: ");
	scanf("%d", &opcao);	
	fclose(file);
	perfil();
}


