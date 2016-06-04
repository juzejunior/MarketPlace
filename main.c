#include "fornecedores.c"
#include "categoria.c"
#include "produtos.c"
#include "config.c"

Fornecedores *fornecedores;
Categoria *categoria;
Produtos *produto;

int main(int argc, char *argv[])
{
	fullscreen();
	loginScreen();
	
	/*
	fullscreen();
	Fornecedores *fornecedores;
	Categoria *categoria;
	Produtos *produto;
	inicializarFornecedor(&fornecedores);
	inicializarCategoria(&categoria);
	inicializarProduto(&produto);
	inserirCategorias(&categoria,"fruta");
	inserirCategorias(&categoria,"movel");
	listarCategorias(categoria);
	cadastrarFornecedor(&fornecedores, "Itambe", "banana");
	cadastrarFornecedor(&fornecedores, "Nestle", "maca");
	novoPedido(&produto, fornecedores, "fruta", "maca", "Nestle", 10);
	novoPedido(&produto, fornecedores, "fruta", "banana", "Itambe", 10);
	listarProdutosCategoria(&categoria, produto);
	listarTodosProdutos(fornecedores);
	listarEstoque(produto);*/
	return 0;
}
