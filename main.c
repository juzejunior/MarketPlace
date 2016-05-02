#include "fornecedores/fornecedores.c"
#include "categoria/categoria.c"
#include "produtos/produtos.c"

int main(int argc, char *argv[])
{
	Fornecedores *fornecedores;
	fornecedores = NULL;
	cadastrarFornecedor(&fornecedores,"Nestlé","leite");
	cadastrarFornecedor(&fornecedores,"Coca Cola","agua");
	cadastrarFornecedor(&fornecedores,"Saraiva","livro");
	cadastrarFornecedor(&fornecedores,"Nestlé","chocolate");
	cadastrarFornecedor(&fornecedores,"Longa Vida","leite");
	cadastrarFornecedor(&fornecedores,"Nestlé","barra");
	cadastrarFornecedor(&fornecedores,"Idaia","agua");
	cadastrarFornecedor(&fornecedores,"Nestlé","leite");
	cadastrarProduto(&fornecedores, "Longa Vida", "barra de chocolate");
	cadastrarProduto(&fornecedores, "Nestlé", "bombom");
	listarTodosProdutos(fornecedores);
	return 0;
}
