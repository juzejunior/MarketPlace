#ifndef FORNECEDOR_H
#define FORNECEDOR_H
#include "config.h"


typedef struct Fornecedor{
	char nome[30];
	char email[30];
	char telefone[30];
	char cnpj[17];
	struct Fornecedor *prox;
} Fornecedor;

/*deleta um fornecedor e todos os seus produtos oferecidos*/
void deletarFornecedor(Fornecedor **fornecedor, Produto **produto);
/*cadastrar um novo fornecedor*/
void cadastrarFornecedor(Fornecedor **fornecedor, Produto **produto);
/*atualizar fornecedor*/
void atualizarFornecedor(Fornecedor **fornecedor);
/*carrega os fornecedores do DB*/
int carregaFornecedor(Fornecedor **f);
/*verifica se o fornecedor já está cadastrado*/
int existeFornecedor(Fornecedor *fornecedor, char nomeFornecedor[]);
/*inicializa um header de fornecedor*/
void inicializarFornecedor(Fornecedor **fornecedor);
/*exibe todos os fornecedores cadastrados*/
void exibirTodosFornecedores(Fornecedor **fornecedor);
/*menu para fornecedores*/
void menuFornecedor(Fornecedor **fornecedor, Produto **produto);
/*atualiza o arquivo de fornecedores caso haja alguma alteração*/
void atualizarArquivoFornecedor(Fornecedor **fornecedor);
/*liberar memória alocada para fornecedor*/
int liberarFornecedor(Fornecedor **fornecedor);
/*menu de atualização do fornecedor*/
void menuAtualizarFornecedor(Fornecedor **fornecedor, Produto **produto);
/*atualiza o nome de um fornecedor*/
void atualizaNomeFornecedor(Fornecedor **fornecedor, Produto **produto);
/*atualiza o email de um fornecedor*/
void atualizaEmailFornecedor(Fornecedor **fornecedor);
/*atualiza o contato de um fornecedor*/
void atualizaContatoFornecedor(Fornecedor **fornecedor);
/*buscar um fornecedor especifico*/
void procurarFornecedor(Fornecedor **fornecedor);
/*iniciando o root de produtos oferecidos pelo fornecedor*/
void inicializarProdutoFornecedor(Produto **produto);
/*carrega todos os produtos oferecidos pelo fornecedor no DB*/
int carregaProdutoFornecedor(Produto **produto);
/*adiciona novos produtos para um determinado fornecedor*/
void adicionarProdutosFornecedor(Fornecedor **fornecedor,Produto **produto);
/*libera todos os produtos*/
int liberarProduto(Produto **produto);
/*verifica se o produto ja esta cadastrado com o fornecedor especificado*/
int existeProdutoFornecedor(char nomeFornecedor[], char nomeProduto[], Produto *produto);
/*atualiza o arquivo de produto de um fornecedor*/
void atualizarArquivoProduto(Produto **produto);
/*excluir produto de um fornecedor*/
void excluirProdutoFornecedor(Fornecedor **fornecedor,Produto **produto);
/*exibir atoa*/
void listaProduto(Produto *p);
/*exibe todos os produtos pertencentes a um fornecedor*/
void exibirProdutosFornecedores(Fornecedor **f ,Produto **p);
/*exibe todos os fornecedores de um determinado produto*/
void buscaProdutosFornecedor(Produto **produto);
//verifica se o produto existe em fornecedor
int existeProdutoemFornecedor(Produto *p, char nomeProduto[]);

#endif
