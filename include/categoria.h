#ifndef CATEGORIA_H
#define CATEGORIA_H
#include "config.h"

typedef struct Categoria{
	char nomeCategoria[50];
	struct Categoria *prox;
}Categoria;

void inicializarCategoria(Categoria **categoria);
int carregaCategoria(Categoria **c);
void cadastrarCategoria(Categoria **categoria);
int exibirCategoria(Categoria **categoria);
int deletarCategoria(Categoria **categoria);
void atualizarArquivoCategoria(Categoria **categoria);
void menuCategoria(Categoria **categoria);
int existeCategoria(Categoria *categoria, char nomeCategoria[]);
#endif
