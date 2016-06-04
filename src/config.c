#include "../include/config.h"

int checkSO()
{
	#ifdef __unix__
		return 0;
	#elif defined(_WIN32) || defined(WIN32)
		return 1;
	#endif
}

void limparTela()
{
	int SO;
	SO = checkSO();
	if(SO==0) system("clear");
	else system("cls");
	return;
}

/*Retorna data e hora atual*/
char* now()
{
	time_t t;
	time(&t);
	return asctime(localtime(&t));
}

void limparBuffer()
{
	if (checkSO())
	{
		fflush(stdin);
	}else{
		getchar();
	}
}

void pause()
{
	if(checkSO())
		system("pause");
	else
		system("read -p \" Precione <ENTER> para continua\" saindo");
}

char charMaiusculo(char caracter)
{
	return toupper(caracter);
}

void stringMaiusculo(char *string) 
{ 
	while(*string) 
	{ 
		*string=toupper(*string); 
		string++; 
	} 
} 

/*Fonte: Angelito M. Goulart
 *Setembro/2009
 * */
int valida_data(int dia, int mes, int ano)
{
    if(dia == NODATA && mes == NODATA && ano == NODATA) return 1;
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)) //verifica se os numeros sao validos
        {
            if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) return 1; //verifica se o ano e bissexto
            {
                return 1;
            }
            if (dia <= 28 && mes == 2) //verifica o mes de feveireiro
            {
                return 1;
            }
            if ((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) //verifica os meses de 30 dias
            {
                return 1;
            }
            if ((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) //verifica os meses de 31 dias
            {
                return 1;
            }
            else
            {
                return 0;
            }
      }
       else
           {
                return 0;
           }
}

/*barra de navegacao*/
void navbar()
{
	printf(" 1-Perfil | 2-Fornecedores | 3-Estoque | 4-Categorias | 0-Sair\n");
}
/*verifica a opcao do usuario referente ao menu principal*/
void opcao(int escolha)
{
	limparTela();
	switch(escolha)
	{
		case 0: limparTela();
			marca();
			printf("\n\t\tObrigado por usar nosso programa!");
			exit(0);
		case 1: perfil();
			break;
	    case 2: menuFornecedor();
			break;
		case 3: menuEstoque();
			break;
		case 4: menuCategoria();
	}
}
/*Menu principal*/
void menuPrincipal(char usuario[])
{
	int escolha = 1;
	limparTela();
	while(escolha != 0)
	{
		printf("                                     Olá, %s  %s", usuario, now());
		marca();
		navbar();
		printf("\n Opção: ");
		scanf("%d", &escolha);
		opcao(escolha);
		limparTela();
	}
}
/*utilizada para encriptar a senha do usuario*/
char *encrypt(char *senha)
{
	while(*senha)
	{
		*senha = *senha ^ 31;
		senha++;
	}
	
	return senha;
}
/*Exibe o nome da empresa*/
void marca()
{
	printf("\t\t\t____________________\n\n");
	printf("\t\t\t    Market Place\n");
	printf("\t\t\t____________________\n\n");
}

/*tela inicial de autenticação*/
void loginScreen()
{
	char usuario[30], senha[30];
	int cont = 0;
	
	do{
		if(cont > 3)
		{
			printf(" Excedido o número de tentativas!\n\n");
			return;
		}
		marca();
		/*apenas para printar uma mensagem caso erre o usuario ou senha*/
		if(cont > 0) printf("  Usuário ou senha incorretos. Tente novamente!\n\n");
		printf("  Usuário: ");
		scanf(" %[^\n]s", usuario);
		printf("  Senha: ");
		scanf(" %[^\n]s", senha);
		limparTela();
		cont++;
	}while(autenticar(usuario, senha) != 1);
	
	menuPrincipal(usuario);
}

/*autentica o usuario em sua sessao*/
int autenticar(char login[], char senha[])
{
	
	FILE *file = fopen("../DB/manager.bin","rb");
	Manager user;
	
	if(file != NULL)
	{ 
		fread(&user,sizeof(Manager),1,file);
		encrypt(user.senha);
		if(strcmp(user.usuario,login) == 0 && strcmp(user.senha, senha) == 0)
		{
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}

