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
	printf("\n Precione <ENTER> para continuar");
	limparBuffer();
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
	printf(" 1-Inicio | 2-Perfil | 3-Fornecedores | 4-Estoque | 0-Sair\n");
}
/*verifica a opcao do usuario referente ao menu principal*/
void opcao(int escolha, Fornecedores **f)
{
	limparTela();
	
	switch(escolha)
	{
		case 1:
			  printf("  pagina inicial\n");
		break;
		case 2:
			 printf(" perfil\n");
	    break;
	    case 3:
			menuFornecedor(f);
		break;
		case 4: 
			printf("  Estoque\n");
		break;
		case 0:
			printf("  Até mais!\n");
		break;
		default:
			printf("Essa opção não consta no menu. Tente novamente!\n");
		break;
	}
}
/*Menu principal*/
void menuPrincipal(char usuario[], Fornecedores **f)
{
	int escolha = 1;
	
	while(escolha != 0)
	{
		printf("                                        Olá, %s  %s", usuario, now());
		marca();
		navbar();
		printf("\n Opção: ");
		scanf("%d", &escolha);
		opcao(escolha, f);
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
	printf("       ____________________\n\n");
	printf("            MarketPlace\n");
	printf("       ____________________\n\n");
}

/*tela inicial de autenticação*/
void loginScreen(Fornecedores **f)
{
	char usuario[10], senha[10];
	int cont = 0;
	
	do{
		marca();
		/*apenas para printar uma mensagem caso erre o usuario ou senha*/
		if(cont > 0) printf("  Usuário ou senha incorretos. Tente novamente!\n\n");
		printf("  Usuário: ");
		scanf("%10s", usuario);
		printf("  Senha: ");
		scanf("%10s", senha);
		cont++;
		limparTela();
	}while(autenticar(usuario, senha) != 1);
	
	menuPrincipal(usuario, f);
}

/*autentica o usuario em sua sessao*/
int autenticar(char login[], char senha[])
{
	char usuario[20];
	int cont = 0;
	FILE *gerente;
	gerente = fopen("login/manager.txt","r");
	
	if(gerente == NULL){
		printf(" Não foi possível abrir o arquivo.\n");
		return 0;
	} 
	
	while((fscanf(gerente,"%s\n", usuario)) != EOF)
	{
		if(strcmp(usuario, login) == 0 || strcmp(usuario, senha) == 0) cont++;
	}
	/*se o usuario e senha estiverem corretos*/
	if(cont == 2) return 1;
	
	return 0;
}
