#ifndef PRODUTOS_H
#define PRODUTOS_H
/* 
 * File:   produtos.h
 * Author: junior(Diôgo)
 *
 * Created on 16 de Abril de 2016, 18:11
 */
typedef struct Data{
	int dia;
	int mes;
	int ano;
} Data;
 
 
typedef struct Produtos{
	char nome[20];
	int quantidade;
	Data vencimento;
	struct Produtos *prox;
}Produtos; 
/*
** Adiciona uma quantidade em um produto ou em todos os produtos no estoque.
*/
#endif
