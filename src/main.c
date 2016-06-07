#include "fornecedor.c"
#include "produto.c"


int main(int argc, char *argv[])
{
	Fornecedor *f;
	Produto *p_fornecedor;

	inicializarFornecedor(&f);
	carregaFornecedor(&f);	

	inicializarProdutoFornecedor(&p_fornecedor);
	carregaProdutoFornecedor(&p_fornecedor);
	
	//listaProduto(p_fornecedor);
	
	menuFornecedor(&f, &p_fornecedor);
	liberarFornecedor(&f);
	liberarProduto(&p_fornecedor);
	
	return 0;
}
