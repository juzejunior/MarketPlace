#include "fornecedores.c"
#include "categoria.c"
#include "produtos.c"

int main(int argc, char *argv[])
{
	Fornecedores *fornecedores;
	inicializarFornecedor(&fornecedores);
	
	cadastrarFornecedor(&fornecedores,"Itambe","leite condensado");
	cadastrarProduto(&fornecedores,"Itambe","biscoito");
	atualizarFornecedor(&fornecedores,"Itambe","Ninho");
	removerProdutos(&fornecedores,"Ninho","leite condensado");
	listarTodosProdutos(fornecedores);
	liberarFornecedor(&fornecedores);
	
	return 0;
}
