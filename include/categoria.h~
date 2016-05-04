#ifndef CATEGORIAS_H
#define CATEGORIAS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../produtos/produtos.h"

typedef struct Categoria{
	char nomeCategoria[50];
	Produtos produto;
	struct Categoria *prox;
}Categoria;

int listarProdutos(Categoria **categoria);

void inserirCategorias(Categoria **categorias, char nomeCategoria[]);

void listarCategorias(Categoria *categorias);

void deletarCategorias(Categoria **categorias, char nomeCategoria[]);

#endif
