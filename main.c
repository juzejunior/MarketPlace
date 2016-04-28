#include "fornecedores/fornecedores.c"
#include<string.h>

int main(int argc, char *argv[])
{
	Fornecedores **fornecedores;
	 
	fornecedores = NULL;
	//printf("Nandinho da Bahia");
	cadastrarFornecedor(fornecedores,"Nestlé","leite");
	return 0;
}
