#ifndef MANAGER_H
#define MANAGER_H
#include "config.h"


typedef struct Manager{
	char usuario[30];
	char senha[30];
} Manager;

void criarManager();
void perfil();
void atualizarUsuario();
void atualizarSenha();

#endif
