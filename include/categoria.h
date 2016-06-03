#ifndef CATEGORIA_H
#define CATEGORIA_H
#include "config.h"

typedef struct Categoria{
	char nomeCategoria[50];
}Categoria;

int existeNomeCategoria(char nomeCategoria[]);
int inserirCategoria();
int deletarCategoria();
int exibirCategoria();
void menuCategoria();

#endif
