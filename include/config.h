#ifndef CONFIG_H
#define CONFIG_H
#if defined (WIN32)
	#include <windows.h>
#elif defined __unix__
	#include<stdio_ext.h>	
#endif
#include<stdio.h>
#include<string.h>
#include<time.h>
#include <ctype.h>
#include <unistd.h>

/*VERIFICA O SISTEMA OPERACIONAL EM QUE O PROGRAMA ESTA RODANDO*/
int checkSO();
/*limpa a tela do programa*/
void limparTela();
/*Deixa em tela cheia*/
void fullscreen();
/*utilizada para validacao de datas*/
int valida_data(int dia, int mes, int ano);
/*exibe o nome da empresa*/
void marca();
/*tela de autenticacao*/
void loginScreen();
/*autenticacao de usuario*/
int autenticar(char login[], char senha[]);
/*encriptar senha*/
char *encrypt(char *senha);
/*criptografia*/
int criptografar (char senha[]);
/*tela inicial*/
void menuPrincipal();
void navbar();
char* now();
void personalizar();

void menuInicio();
void menuProfile();
void menuFornecedores();
void menuEstoque();

#endif
