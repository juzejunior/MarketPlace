#ifndef CONFIG_H
#define CONFIG_H
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "categoria.h"
#include "fornecedor.h"
#define NODATA 0

typedef struct Fornecedores Fornecedores;
/*VERIFICA O SISTEMA OPERACIONAL EM QUE O PROGRAMA ESTA RODANDO*/
int checkSO();
/*Limpa a tela do programa*/
void limparTela();
/*Retorna data e hora atual*/
char* now();
/*Limpa o lixo do teclado*/
void limparBuffer();
/*Pausa o programa*/
void pause();
/*Retorna o caracter maiuscula*/
char charMaiusculo(char caracter);
/*Retorna a String Maiuscula*/
void stringMaiusculo(char *string);
/*Utilizada para validação de datas*/
int valida_data(int dia, int mes, int ano);




/*exibe o nome da empresa*/
void marca();
/*tela de autenticacao*/
void loginScreen(Fornecedores **f);
/*autenticacao de usuario*/
int autenticar(char login[], char senha[]);
#endif
