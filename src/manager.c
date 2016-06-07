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
	
 	limparTela();
	printf("                                     %s", now());
	marca();
	printf("\t\t      Configuração de Usuário\n\n");
	printf("\t\t  1-Atualizar Usuário    0-Volta\n\t\t  2-Atualizar Senha      ");
	printf("\n\t\t  Opcao: ");
	scanf("%d", &opcao);
	switch(opcao)
	{
		case 0: return;
		case 1: atualizarUsuario();
			break;
		case 2: atualizarSenha();
			break;
		default: printf(" Opcao Invalida, voltando ao menu principal! \n");
			pause();
			break;
	}

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
		printf(" Atualizado com sucesso!\n\n");
	 }
	 fclose(file);
	 pause();
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


