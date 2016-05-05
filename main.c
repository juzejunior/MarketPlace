#include "fornecedores.c"
#include "categoria.c"
#include "produtos.c"

int main(int argc, char *argv[])
{
	Fornecedores *fornecedores;
	inicializarFornecedor(&fornecedores);
	
	/*teste cadastro*/
	cadastrarFornecedor(&fornecedores,"Avianca","leite em pó");
    cadastrarFornecedor(&fornecedores,"Itambé","leite liquído");
    cadastrarFornecedor(&fornecedores,"Ypê","detergente");
    
    /*teste atualizacao*/
    atualizarFornecedor(&fornecedores,"Avianca","Avianca Lite");
	
	/*read*/
	//listarFornecedor(fornecedores);
	
	/*adicionar produto*/
	cadastrarProduto(&fornecedores,"Avianca Lite","maçã");
	/*atualizar produto*/
	atualizarProduto(&fornecedores,"Avianca Lite","maçã","maçã verde");
	atualizarProduto(&fornecedores,"Ypê","detergente","sabão");
	removerProdutos(&fornecedores,"Avianca Lite","maçã verde");
	removerProdutos(&fornecedores,"Ypê","sabão");
	
	cadastrarProduto(&fornecedores,"Ypê","água sanitária");
    cadastrarProduto(&fornecedores,"Ypê","sabão em pedra");
    
    cadastrarProduto(&fornecedores,"Itambé","chocolate amargo");
	removerProdutos(&fornecedores,"Itambé","chocolate amargo");
	
	listarTodosProdutos(fornecedores);

	liberarFornecedor(&fornecedores);
	
	return 0;
}
