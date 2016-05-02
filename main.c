#include "fornecedores/fornecedores.c"
#include "categoria/categoria.c"
#include "produtos/produtos.c"

int main(int argc, char *argv[])
{
	Fornecedores *fornecedores;
	inicializarFornecedor(&fornecedores);
	
	cadastrarFornecedor(&fornecedores,"Itambe","leite condensado");
	cadastrarProduto(&fornecedores,"Itambe","arroz");
	cadastrarProduto(&fornecedores,"Itambe","leite condensado");
	removerFornecedor(&fornecedores, "Itambe");
	atualizarFornecedor(&fornecedores,"Itambe","Ninho");
	listarTodosProdutos(fornecedores);
	liberarFornecedor(&fornecedores);
	
	return 0;
}
