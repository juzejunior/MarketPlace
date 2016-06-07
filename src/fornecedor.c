#include "../include/config.h"

//Função faz a leitura do arquivo binário fornecedores.bin normalmente e imprime tudo que tiver á.
int existeFornecedor(char nomeFornecedor[])
{
	FILE *file_fornecedor;
	Fornecedor fornecedor;
	int cont = 1;
	
	file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	
	while(fread(&fornecedor, sizeof(Fornecedor),1, file_fornecedor) == 1)
	{
		if(strcmp(nomeFornecedor, fornecedor.nome) == 0) return cont;//caso já exista um fornecedor com esse nome
		cont++;
	} 
	return 0;
}

//Cadastra os fornecedores
int inserirFornecedor()
{
	FILE *file_fornecedor;
	FILE *file_produtos_forne;
	Fornecedor fornecedor;
	Produto produto;
	char opcao;

	file_fornecedor = fopen("../DB/fornecedores.bin","ab");	
	file_produtos_forne = fopen("../DB/produtos.bin","ab");
	
	do{
	   limparTela();
	   printf("                                     %s", now());//imprime na tela a dara e hora atual.
	   marca();	
	   printf("       Cadastro de Fornecedores\n\n");
	   printf(" Nome: ");
	   scanf(" %[^\n]s", fornecedor.nome);
	   stringMaiusculo(fornecedor.nome);//tranformao nome do fornecedor em maiusculo
	   
	   if(existeFornecedor(fornecedor.nome) == 0) //Verifica se existe o fornecedor cadastrado, caso não o cadastro prossegue
	   {
		    printf(" E-mail: ");
			scanf(" %[^\n]s", fornecedor.email);
			printf(" Telefone: ");
			scanf(" %[^\n]s", fornecedor.telefone);
			printf(" CNPJ: ");
			scanf(" %[^\n]s", fornecedor.cnpj);
			printf(" Produto oferecido: ");
			scanf(" %[^\n]s", produto.nome);// Já pergunta um produto que o fornecedor disponibiliza.
			stringMaiusculo(produto.nome);//tranformao nome do fornecedor em maiusculo
			strcpy(produto.nomeFornecedor, fornecedor.nome);
			//caso cadastre com sucesso
			if(fwrite(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) != 0 && fwrite(&produto, sizeof(Produto),1, file_produtos_forne) != 0)
			{
				printf("\n Fornecedor cadastrado com sucesso!\n\n");
			}else{
				printf("\n Cadastro não realizado. Contate o suporte :(\n\n");
			} 	
	   }else{
			printf(" Esse fornecedor já está cadastrado!\n\n");
	   }
	   printf(" Novo cadastro(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	fclose(file_fornecedor);
	fclose(file_produtos_forne);
	limparTela();
	menuFornecedor();
	return 0;
}

//Função que deleta o Fornecedor
int deletarFornecedor()
{
	char nomeFornecedor[30];
	Fornecedor fornecedor;
	Produto p;
	FILE *file_fornecedor;
	FILE *aux;
	FILE *file_produto;
	FILE *aux_produto;
	char opcao;
	int encontrou = 0;
	
	do{
	   limparTela();//Abre os arquivos auxiliares para não perde dados e o do fornecedor para ele ser deletado.
	   printf("                                     %s", now());//imprime na tela a dara e hora atual.
	   marca();
	   file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	   aux = fopen("../DB/aux.bin","wb");	
	   file_produto = fopen("../DB/produtos.bin","rb");
	   aux_produto = fopen("../DB/aux_produtos.bin", "wb");
	   printf("        Deletar Fornecedor\n\n");
	   printf(" Qual fornecedor deseja remover: ");//Qual fornecedor deseja deletar.
	   scanf(" %[^\n]s", nomeFornecedor);
	   stringMaiusculo(nomeFornecedor);
	   //caso o fornecedor exista, deleta o fornecedor e seus respectivos produtos
	   while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)
	   {
			if(strcmp(fornecedor.nome, nomeFornecedor) == 0)
			{
				encontrou = 1;
			}else{
				fwrite(&fornecedor, sizeof(Fornecedor), 1, aux);//Enquanto não encontra o fornecedor ele armazena em outro arquivo
																//temporario para não perder os dados.
			}
	   }
	   //caso não tenha encontrado o fornecedor
	   if(!encontrou){
		 printf(" Fornecedor não encontrado!\n\n");  
	   } else{
			 while(fread(&p, sizeof(Produto), 1, file_produto) == 1)
			 {	 
				 if(strcmp(fornecedor.nome, p.nomeFornecedor) == 0)
				 {
					encontrou = 1;
				 }else{
					fwrite(&p, sizeof(Produto),1, aux_produto);
				 }
			 } 
			 printf(" Removido com sucesso!\n\n"); 
	   } 
	  
	   
	   fclose(file_fornecedor);
	   fclose(aux);
	   
	   fclose(file_produto);
	   fclose(aux_produto);
	   
	   remove("../DB/fornecedores.bin");
	   rename("../DB/aux.bin", "../DB/fornecedores.bin");
	   
	   remove("../DB/produtos.bin");
	   rename("../DB/aux_produtos.bin", "../DB/produtos.bin");
	   
	   printf(" Nova exclusão(s/n): ");
	   scanf(" %c", &opcao);	
	}while(opcao != 'n');
	limparTela();
	menuFornecedor();
	return 0;
}
//Listagem dos produtos
int exibirFornecedor()
{
	Fornecedor fornecedor;
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");//Abre o arquivo
	int opcao;
	
	limparTela();
	printf("                                     %s", now());//imprime na tela a dara e hora atual.
	marca();
	while(fread(&fornecedor,sizeof(Fornecedor),1,file_fornecedor) == 1)//Enquanto houver dados, ele lista.
	{
		printf(" Nome: %s\n", fornecedor.nome);
		printf(" CNPJ: %s\n", fornecedor.cnpj);
		printf(" E-mail: %s\n", fornecedor.email);
		printf(" Telefone: %s\n\n", fornecedor.telefone);
		printf(" __________________________\n\n");
	}
	fclose(file_fornecedor);
	
	printf(" 1 - Retornar\n Opção: ");
	scanf("%d", &opcao);
	limparTela();
	if(opcao == 1) menuFornecedor();
	else printf(" Volte sempre ;)\n");			
	return 0;
}

void MenuatualizarFornecedor()
{
	int opcao;		

	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca();
		printf("\n Atualização Fornecedor\n\n");
		printf(" 1- Nome | 2- E-mail | 3- Telefone | 4- Voltar\n\n Opção: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				atualizaNomeFornecedor();
			break;
			case 2:
				atualizaEmailFornecedor();
			break;
			case 3:
				atualizaContatoFornecedor();
			break;
			case 4:
				limparTela();
				menuFornecedor();
			break;
		}
	}while(opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4);	
}

void atualizaNomeFornecedor()
{
	FILE *file = fopen("../DB/fornecedores.bin","rb+");
	int cont = 0;
	char nomeFornecedor[30];
	Fornecedor f;
	char opcao;
	
	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca();
		printf("\n Informe o nome atual do fornecedor: ");//Informa o nome do fornecedor que quer atualizar
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//tranformao nome do fornecedor em maiusculo
		//se o fornecedor procurando existir
		if(existeFornecedor(nomeFornecedor) != 0)
		{
			cont = existeFornecedor(nomeFornecedor);//posicao onde esta a estrutura
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fread(&f,sizeof(Fornecedor),1, file);
			printf("\n Nome atual: %s\n", f.nome);
			printf(" Informe o novo nome do fornecedor: ");
			scanf(" %[^\n]s", nomeFornecedor);
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			stringMaiusculo(nomeFornecedor);//tranformao nome do fornecedor em maiusculo
			strcpy(f.nome, nomeFornecedor);
			fwrite(&f,sizeof(Fornecedor),1, file);
			printf(" Atualizado com sucesso :)\n\n");
			printf(" Atualizar outro fornecedor? (s/n): ");
		}else{
			printf(" Fornecedor não encontrado :(\n\n");
			printf(" Tentar novamente? (s/n): ");
		}	
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	fclose(file);
	limparTela();
	MenuatualizarFornecedor();
}

void atualizaEmailFornecedor()
{
	FILE *file = fopen("../DB/fornecedores.bin","rb+");
	int cont = 0;
	char nomeFornecedor[30];
	Fornecedor f;
	char opcao;
	
	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca();
		printf("\n Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//tranforma o nome do fornecedor em maiusculo
		//se o fornecedor procurando existir
		if(existeFornecedor(nomeFornecedor) != 0)
		{
			cont = existeFornecedor(nomeFornecedor);//posicao onde esta a estrutura
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fread(&f,sizeof(Fornecedor),1, file);
			printf("\n E-mail atual: %s\n", f.email);
			printf(" Informe o novo e-mail do fornecedor: ");
			scanf(" %[^\n]s", f.email);
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fwrite(&f,sizeof(Fornecedor),1, file);
			printf(" Atualizado com sucesso :)\n\n");
			printf(" Atualizar outro fornecedor? (s/n): ");
		}else{
			printf(" Fornecedor não encontrado :(\n\n");
			printf(" Tentar novamente? (s/n): ");
		}	
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	fclose(file);
	limparTela();
	MenuatualizarFornecedor();
}

void atualizaContatoFornecedor()
{
	FILE *file = fopen("../DB/fornecedores.bin","rb+");
	int cont = 0;
	char nomeFornecedor[30];
	Fornecedor f;
	char opcao;
	
	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca(); 
		printf("\n Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//tranformao nome do fornecedor em maiusculo
		//se o fornecedor procurando existir
		if(existeFornecedor(nomeFornecedor) != 0)
		{
			cont = existeFornecedor(nomeFornecedor);//posicao onde esta a estrutura
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fread(&f,sizeof(Fornecedor),1, file);
			printf("\n Contato atual: %s\n", f.telefone);
			printf(" Informe o novo telefone do fornecedor: ");
			scanf(" %[^\n]s", f.telefone);
			fseek(file,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fwrite(&f,sizeof(Fornecedor),1, file);
			printf(" Atualizado com sucesso :)\n\n");
			printf(" Atualizar outro fornecedor? (s/n): ");
		}else{
			printf(" Fornecedor não encontrado :(\n\n");
			printf(" Tentar novamente? (s/n): ");
		}	
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	fclose(file);
	limparTela();
	MenuatualizarFornecedor();
}

void procurarFornecedor()
{
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");
	char escolha;
	char nomeFornecedor[30];
	int encontrou = 0;
	Fornecedor fornecedor;
	
	if(file_fornecedor != NULL)
	{
		do{
		   limparTela();
		   printf("                                     %s", now());//imprime na tela a dara e hora atual.
	       marca(); 
		   printf("\n Informe o nome do fornecedor: ");	
		   scanf(" %[^\n]s", nomeFornecedor);
		   stringMaiusculo(nomeFornecedor);//tranformao nome do fornecedor em maiusculo
		   
		   while(fread(&fornecedor,sizeof(Fornecedor),1, file_fornecedor) == 1)//Enquando tiver dado a ser lido, ele continua.
		   {
				if(strcmp(fornecedor.nome, nomeFornecedor) == 0) {	//Verifica se encontrou o fornecedor.
					printf("\n Empresa: %s\n", fornecedor.nome);
					printf(" CNPJ: %s\n", fornecedor.cnpj);
					printf(" E-mail: %s\n", fornecedor.email);
					printf(" Telefone: %s\n\n", fornecedor.telefone);
					encontrou = 1;
					break;
				}
		   }
		   if(encontrou != 1) printf(" Fornecedor não encontrado :(\n\n");
		   
		   printf(" Nova busca (s/n): ");
		   scanf(" %c", &escolha);	
		}while(escolha != 'n');
		limparTela();
		menuFornecedor();
	}
}

void menuFornecedor()
{
	 int opcao;		
	 do{
	    limparTela();
	    printf("                                        %s",now());
		marca();	
	    printf("\t\t\t    Fornecedores\n\n");
	    printf("\t   1-Cadastrar    6-Buscar produtos de um fornecedor\n\t   2-Excluir      7-Cadastrar novo produto\n\t   3-Informações  8-Excluir um produto\n\t   4-Procurar     9-Consultar fornecedores de um produto\n\t   5-Atualizar    0-Voltar\n\n");
		printf("\t   Opção: ");
		scanf("%d", &opcao);
	 
		switch(opcao)
		{
			case 1:
				inserirFornecedor();
			break;
			case 2:
				deletarFornecedor();
			break;
			case 3:
				limparTela();
				exibirFornecedor();
			break;
			case 4:
				procurarFornecedor();
			break;
			case 5:
				MenuatualizarFornecedor();
			break;
			case 6:
				exibirProdutosFornecedores();
			break;
			case 7:
				adicionarProdutosFornecedor();
			break;
			case 8:
				excluirProdutoFornecedor();
			break;
			case 9:
				buscaProdutosFornecedor();
			break;
			case 0:
				return;
			break;
		}	 
	 }while(opcao > 10 || opcao < 0);
}
/*products*/
void exibirProdutosFornecedores()
{
	char opcao;
	int i = 0;
	int cont = 0;
	char nomeFornecedor[30];
	Fornecedor f;
	Produto p;
	FILE *file_fornecedor = fopen("../DB/fornecedores.bin","rb");	
	FILE *file_produtos_forne = fopen("../DB/produtos.bin","rb");
	
	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca(); 
		printf("\n Informe o nome do fornecedor: ");
		scanf(" %[^\n]s", nomeFornecedor);
		stringMaiusculo(nomeFornecedor);//transforma o nome do fornecedor em maiusculo
	
		//se o fornecedor existe
		if(existeFornecedor(nomeFornecedor) != 0)
		{
			cont = existeFornecedor(nomeFornecedor);
			fseek(file_fornecedor,sizeof(Fornecedor)*(cont-1), SEEK_SET);
			fread(&f,sizeof(Fornecedor),1,file_fornecedor);
			printf("\n Fornecedor: %s\n\n", f.nome);
			printf("	Produtos: \n");
			while(fread(&p,sizeof(Produto),1, file_produtos_forne) == 1)//Enquanto esse fornecedor possuir produto ele será listado.
			{
				if(strcmp(f.nome, p.nomeFornecedor) == 0) {
					printf("	        %s\n", p.nome);
				}
				i++;
			}
			if(i == 0) printf(" Esse fornecedor não lhe oferece produtos :(\n\n");
			printf("\n\n");
		}else{
			printf(" Fornecedor não encontrado :(\n\n");
		}	
		printf(" Nova busca?(s/n): ");
		scanf(" %c", &opcao);
	}while(opcao != 'n');
	limparTela();
	menuFornecedor();
}

void adicionarProdutosFornecedor()
{
	Produto p;
	char opcao;	
	FILE *file_produto = fopen("../DB/produtos.bin","ab");
	char nomeFornecedor[30];
	
	
	if(file_produto != NULL)
	{
		do{
			limparTela();
			printf("                                     %s", now());//imprime na tela a dara e hora atual.
	        marca(); 
			printf("\n Informe o nome do fornecedor: ");
			scanf(" %[^\n]s", nomeFornecedor);
			stringMaiusculo(nomeFornecedor);//transforma o nome do fornecedor em maiusculo
		
			if(existeFornecedor(nomeFornecedor) != 0)
			{
				printf(" Nome do produto: ");
				scanf(" %[^\n]s", p.nome);
				stringMaiusculo(p.nome);
				//verificar se o produto ja n pertence ao fornecedor
				if(existeProdutoFornecedor(nomeFornecedor, p.nome) == 0)//caso nao
				{
					strcpy(p.nomeFornecedor, nomeFornecedor);
					fwrite(&p, sizeof(Produto), 1, file_produto);
					printf(" Adicionado com sucesso :) \n\n");
				}else{
					printf(" Este produto já está cadastrado para esse fornecedor!\n\n");
				}
			}else{
				printf(" Fornecedor inexistente :(\n\n");
			}
			printf(" Novo cadastro(s/n): ");
			scanf(" %c", &opcao);
		}while(opcao != 'n');
		fclose(file_produto); 
		limparTela();
		menuFornecedor();
	}else{
		printf(" Arquivo não encontrado. Entre em contato com o suporte :(\n\n");
	}
	fclose(file_produto); 
}

void excluirProdutoFornecedor()
{
	FILE *file_produto; 
	FILE *file_aux;
	int encontrou = 0;
	char opcao;
	Produto p, aux;
	
	do{
	  limparTela();
	  printf("                                     %s", now());//imprime na tela a dara e hora atual.
	  marca(); 
	  file_produto = fopen("../DB/produtos.bin","rb");
	  file_aux = fopen("../DB/aux.bin","wb");
	  printf(" Nome do produto: ");
	  scanf(" %[^\n]s", p.nome);
	  stringMaiusculo(p.nome);
	  printf(" Nome do fornecedor: ");
	  scanf(" %[^\n]s", p.nomeFornecedor);
	  stringMaiusculo(p.nomeFornecedor);
	  /*se o produto existir e pertencer ao fornecedor informado*/
	  if(existeProdutoFornecedor(p.nomeFornecedor, p.nome) != 0)
	  {
		  while(fread(&aux,sizeof(Produto),1, file_produto) == 1)//Enquanto houver dados vai armazenando na auxiliar
		  {
			 if(strcmp(aux.nome, p.nome) == 0 && strcmp(aux.nomeFornecedor, p.nomeFornecedor) == 0) //Ver se existe o produto no fornecedor
			 {
				 encontrou = 1;
			 }else{
				 fwrite(&aux, sizeof(Produto),1, file_aux);// se encontrou ele não vai armazenar na auxiliar;
			 }
		  }
		  if(encontrou == 1)  printf(" Removido com sucesso :)\n\n");
		  else printf(" Ocorreu erros\n\n");
		  fclose(file_produto);
		  fclose(file_aux);
		  remove("../DB/produtos.bin");
		  rename("../DB/aux.bin", "../DB/produtos.bin");
	  }else{
		 printf(" Produto ou fornecedor inválido :o\n\n");  
	  }
	  printf(" Nova remoção?(s/n): ");
	  scanf(" %c", &opcao);
	}while(opcao != 'n');
	limparTela();
	menuFornecedor();
}
//busca produtos
void buscaProdutosFornecedor()
{
	FILE *file_produto;
	Produto p;
	char opcao;
	char nomeProduto[30];
	int cont = 0;
	
	do{
		limparTela();
		printf("                                     %s", now());//imprime na tela a dara e hora atual.
	    marca(); 
		file_produto = fopen("../DB/produtos.bin","rb");
		printf(" Nome do produto: ");
		scanf(" %[^\n]s", nomeProduto);
		stringMaiusculo(nomeProduto);
		while(fread(&p, sizeof(Produto),1, file_produto) == 1)
		{
			if(strcmp(p.nome, nomeProduto) == 0)// Se encontrou o produto, ele imprime todos os fornecedores que possui esse produto.
			{
				 if(cont == 0) printf("\n Seus fornecedores: ");
				 printf("\n               %d. %s",cont+1,p.nomeFornecedor);
				 cont++;
			}
		}
		printf("\n\n");
		if(cont == 0) printf(" Produto não encontrado :(\n\n");
		printf(" Nova busca(s/n): ");
		scanf(" %c", &opcao);
		cont = 0;
		fclose(file_produto);
	}while(opcao != 'n');
	limparTela();
	menuFornecedor();
}
//verifica se o produto procurado já nao pertence a um fornecedor
int existeProdutoFornecedor(char NomeFornecedor[], char nomeProduto[])
{
	FILE *file_produto = fopen("../DB/produtos.bin","rb");
	Produto p;
	
	while(fread(&p,sizeof(Produto),1, file_produto) == 1)
	{
		if(strcmp(p.nome, nomeProduto) == 0 && strcmp(p.nomeFornecedor, NomeFornecedor) == 0)
		{
			fclose(file_produto);
			return 1;	
		} 
	}
	fclose(file_produto);
	return 0;
}
