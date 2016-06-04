#include "include/config.h"
 
int checkSO()
{
	#ifdef __unix__
		return 0;
	#elif defined(_WIN32) || defined(WIN32)
		return 1;
	#endif
}

void fullscreen()
{
	#if defined (WIN32)
		keybd_event ( VK_MENU, 0x36, 0, 0 ); 
		keybd_event ( VK_RETURN, 0x1C, 0, 0 ); 
		keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 ); 
		keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	#endif
}

void limparTela()
{
	int SO;
	SO = checkSO();
	if (SO==0) system ("clear");
	else system ("cls");
}

void personalizar()
{
	limparTela();
	int SO;
	SO = checkSO();
	if (SO==1)system("COLOR F0");
	return;
}

/*Retorna data e hora atual*/
char* now()
{
	time_t t;
	time(&t);
	return asctime(localtime(&t));
}
/*barra de navegacao*/
void navbar()
{
	int i=0;
	char escolha;
	do{
		printf("   I - Inicio\n");
		printf("   P - Perfil\n");
		printf("   F - Fornecedores\n");
		printf("   E - Estoque\n");
		printf("   S - Sair\n");
		printf("   Comando: ");
		#if defined (WIN32)
			escolha = getch(escolha);
		#elif defined __unix__
			__fpurge(stdin);
			scanf("%c",&escolha);
		#endif
		escolha = toupper(escolha);
		switch (escolha)
		{
			case 'I': menuInicio();
				i = 1;
				break;
			case 'P': menuProfile();
				i = 1;
				break;
			case 'F': menuFornecedores();
				i = 1;
				break;
			case 'E': menuEstoque();
				i = 1;
				break;
			case 'S': printf("\n     Obrigado por usar nosso programa");
				sleep(2);
				exit(0);
				break;
			default: printf("\n    Comando Invalido...\n");
				sleep(2);
				limparTela();
				break;
		}
	}while(i==0);
	limparTela();
}
/*Menu principal*/
void menuPrincipal()
{
	personalizar();
	printf("                                          %s", now());
	marca();
	navbar();
}

/*Exibe o nome da empresa*/
void marca()
{
	printf("                 ____________________\n\n");
	printf("                      MarketPlace\n");
	printf("                 ____________________\n\n");
}

/*tela inicial de autenticao*/
void loginScreen()
{
	char usuario[10], senha[10];
	int cont = 0;
	
	do{
		marca();
		/*apenas para printar uma mensagem caso erre o usuario ou senha*/
		if(cont > 0) printf("  Usuario ou senha incorretos. Tente novamente!\n\n");
		printf("  Usuario: ");
		scanf("%10s", usuario);
		printf("  Senha: ");
		scanf("%10s", senha);
		cont++;
		limparTela();
	}while(autenticar(usuario, senha) != 1);
	
	menuPrincipal();
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

/*Criptografa senha do usuário*/
int criptografar (char senha[])
{
	int i;
	int senharesult = 0;
	encrypt(senha);
	for (i=0;i<10;i++){
		senharesult += ((int) senha[i]) * 523;
	}
	senharesult = ((senharesult * 412)+1024)*912;
	senharesult = abs(senharesult);
	return senharesult;
}

/*autentica o usuario em sua sessao*/
int autenticar(char login[], char senha[])
{
	char usuario[20];
	int cont = 0;
	int resultSenha;
	int minhaSenha;
	FILE *gerenteLogin, *gerenteSenha;
	gerenteLogin = fopen("login/managerLogin.txt","r");
	gerenteSenha = fopen("login/managerSenha.txt","r");
	
	if(gerenteLogin == NULL || gerenteSenha == NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		return 0;
	} 
	
	while((fscanf(gerenteLogin,"%s\n", usuario)) != EOF)
	{
		if(strcmp(usuario, login) == 0) cont++;
	}
	
	resultSenha = criptografar(senha);
	
    fscanf (gerenteSenha, "%d", &minhaSenha);  
    if (minhaSenha == resultSenha) cont++;
    /*se o usuario e senha estiverem corretos*/
    if(cont == 2) return 1;
    
	return 0;
}

void menuInicio()
{
	printf("                                          %s", now());
	marca();
}
void menuProfile()
{
	printf("                                          %s", now());
	marca();
}
void menuFornecedores()
{
	int i, choice;
	char escolha[3];
	limparTela();
	printf("                                          %s", now());
	marca();
	printf("   I - Inicio\n");
	printf("   CF - Cadastrar novo fornecedor\n");
	printf("   LF - Listar Fornecedores\n");
	printf("   AF - Atualizar fornecedor\n");
	printf("   RF - Remover fornecedor\n");
	printf("   TF - Remover todos fornecedores\n");
	printf("   CP - Cadastrar novo produto\n");
	printf("   LP - Listar Produtos\n");
	printf("   AP - Atualizar produto\n");
	printf("   RP - Remover produto\n");
	printf("   \nComando: ");
	#if defined (WIN32)
		escolha = getch(escolha);
	#elif defined __unix__
		__fpurge(stdin);
		scanf("%s", escolha);
	#endif
	for (i=0;i<2;i++)
	{
		escolha[i] = toupper(escolha[i]);
	}
		if (escolha[0]=='I') choice = 0;
		if (escolha[1]=='F')
		{
			if (escolha[0] == 'C') choice = 1;
			if (escolha[0] == 'L') choice = 2;
			if (escolha[0] == 'A') choice = 3;
			if (escolha[0] == 'R') choice = 4;
			if (escolha[0] == 'T') choice = 5;
		}
		if (escolha[1]=='P')
		{
			if (escolha[0] == 'C') choice = 6;
			if (escolha[0] == 'L') choice = 7;
			if (escolha[0] == 'A') choice = 8;
			if (escolha[0] == 'R') choice = 9;
		}
		switch(choice)
		{
			case 0: menuPrincipal();
				break;
			case 1: 
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
		}
}
void menuEstoque()
{
	char escolha;
	printf("                                          %s", now());
	marca();
	#if defined (WIN32)
		escolha = getch(escolha);
	#elif defined __unix__
		__fpurge(stdin);
		scanf("%c",&escolha);
	#endif
	escolha = toupper(escolha);
}


/*Fonte: Angelito M. Goulart
 *Setembro/2009
 * */
int valida_data(int dia, int mes, int ano)
{
    if ((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12) && (ano >= 1900 && ano <= 2100)) //verifica se os numeros sao validos
        {
            if ((dia == 29 && mes == 2) && ((ano % 4) == 0)) //verifica se o ano e bissexto
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
