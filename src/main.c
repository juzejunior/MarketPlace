#include "fornecedor.c"
#include "categoria.c"
#include "manager.c"
#include "produto.c"
#include "config.c"

int main()
{
	Produto *p_fornecedor;
	Fornecedor *f;
	Categoria *c;
	Produto *p;
	inicializarProdutoFornecedor(&p_fornecedor);
	carregaProdutoFornecedor(&p_fornecedor);
	inicializarFornecedor(&f);
	carregaFornecedor(&f);
	inicializarCategoria(&c);
	carregaCategoria(&c);
	inicializarEstoque(&p);
	carregaEstoque(&p);
	loginScreen(&p, &c, &f, &p_fornecedor);
	return 0;
}

