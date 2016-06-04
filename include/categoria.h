#ifndef CATEGORIAS_H
#define CATEGORIAS_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "produtos.h"

typedef struct Categoria{
	char nome[20];
	Produtos produto;
	struct Categoria *prox;
}Categoria;

typedef struct Produtos Produtos;

void inicializarCategoria(Categoria **categoria);

int inserirCategorias(Categoria **categorias, char nomeCategoria[]);

int listarCategorias(Categoria *categorias);

int deletarCategorias(Categoria **categorias, char nomeCategoria[]);

int listarProdutosCategoria(Categoria **categoria, Produtos *produto);

#endif
