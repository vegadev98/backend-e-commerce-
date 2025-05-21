#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
    int codigo;
    char descricao[50];
    int qtd_estoque;
    float preco;
} Produto,*PProduto,**PPProduto;

typedef struct item{
	int codigo_produto;
	char descricao_produto[50];
	int quantidade;
	float valor_total;
}Item, *PItem, **PPItem;

typedef struct carrinho {
    PItem itens;
    int n_itens;
} Carrinho, *PCarrinho;

void gravar_produtos_em_arquivo(PProduto produtos, int n_produtos) {
    FILE *arquivo;
    arquivo = fopen("produtos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }	
	int i;
    for (i = 0; i < n_produtos; i++) {
        Produto *produto = &produtos[i];
        fprintf(arquivo, "Codigo: %d\n", produto->codigo);
        fprintf(arquivo, "Descricao: %s\n", produto->descricao);
        fprintf(arquivo, "Quantidade em estoque: %d\n", produto->qtd_estoque);
        fprintf(arquivo, "Preco: %.2f\n\n", produto->preco);
    }
    fclose(arquivo);
}

void incluir_produto(PPProduto produtos, int *n_produtos) {
    int qtd_registra, i;
    printf("Digite a quantidade de produto(s) a ser(em) registrada(s): ");
    scanf("%d", &qtd_registra);

    *produtos = realloc(*produtos, (*n_produtos + qtd_registra) * sizeof(Produto));

    for (i = 0; i < qtd_registra; i++) {
        Produto *produto = &(*produtos)[*n_produtos + i];
        printf("\nDigite o codigo do produto [%i]: ", *n_produtos + i + 1);
        scanf("%d", &produto->codigo);
        printf("Digite a descricao do produto [%i]: ", *n_produtos + i + 1);
        scanf("%s", produto->descricao);
        printf("Digite a quantidade em estoque [%i]: ", *n_produtos + i + 1);
        scanf("%d", &produto->qtd_estoque);
        printf("Digite o preco do produto [%i]: ", *n_produtos + i + 1);
        scanf("%f", &produto->preco);
    }

    *n_produtos += qtd_registra; 
	gravar_produtos_em_arquivo(*produtos, *n_produtos); 
}

void listar_produtos(PProduto produtos, int n_produtos) {
    printf("\nProdutos cadastrados:\n");
    int i;
    for (i = 0; i < n_produtos; i++) {
        printf("\nCodigo: %d", produtos[i].codigo);
        printf("\nDescricao: %s", produtos[i].descricao);
        printf("\nQuantidade em estoque: %d", produtos[i].qtd_estoque);
        printf("\nPreco: %.2f", produtos[i].preco);
        printf("\n");
    }
}

void alterar_produto(PProduto produtos, int n_produtos) {
    int codigo, i;
    printf("\nDigite o codigo do produto que deseja alterar: ");
    scanf("%d", &codigo);

    int posicao = -1;
    for (i = 0; i < n_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
    	system("cls");
        printf("Produto nao encontrado!\nPressione ENTER para voltar ao MENU anterior");
        getch();
        return;
    }

    printf("Digite a nova descricao do produto: ");
    scanf("%s", produtos[posicao].descricao);
    printf("Digite a nova quantidade em estoque: ");
    scanf("%d", &produtos[posicao].qtd_estoque);
    printf("Digite o novo preco do produto: ");
    scanf("%f", &produtos[posicao].preco);
	printf("\n\n#############################");
    printf("\nProduto alterado com sucesso!\n");
    printf("#############################\n");
    gravar_produtos_em_arquivo(produtos, n_produtos); 
    getch();
}

void excluir_produto(PProduto produtos, int *n_produtos) {
    int codigo, i;
    printf("\nDigite o codigo do produto que deseja excluir: ");
    scanf("%d", &codigo);

    int posicao = -1;
    for (i = 0; i < *n_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
    	printf("\n#######################");
        printf("\nProduto nao encontrado.");
        printf("\n#######################");
        return;
    }

    for (i = posicao; i < *n_produtos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }

    (*n_produtos)--;
    produtos = realloc(produtos, (*n_produtos) * sizeof(Produto));
    
    gravar_produtos_em_arquivo(produtos, *n_produtos);
	
	printf("\n#############################");
    printf("\nProduto excluido com sucesso.");
    printf("\n#############################\n");
    getch();
}

void consultar_produto(PProduto produtos, int n_produtos) {
    int codigo, i;
    printf("\nDigite o codigo do produto que deseja consultar: ");
    scanf("%d", &codigo);
    
    int posicao = -1;
    for (i = 0; i < n_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
    	printf("\n#######################");
        printf("\nProduto nao encontrado.");
        printf("\n#######################");
        return;
    }

    printf("\nCodigo: %d", produtos[posicao].codigo);
    printf("\nDescricao: %s", produtos[posicao].descricao);
    printf("\nQuantidade em estoque: %d", produtos[posicao].qtd_estoque);
    printf("\nPreco: %.2f", produtos[posicao].preco);
}

void adicionar_ao_carrinho(PCarrinho *carrinho_ptr, PProduto produtos, int n_produtos) {
    int codigo, quantidade;
    printf("Digite o codigo do produto que deseja adicionar ao carrinho: ");
    scanf("%d", &codigo);
    
    if (*carrinho_ptr == NULL) {
        *carrinho_ptr = malloc(sizeof(Carrinho));

        if (*carrinho_ptr == NULL) {
            printf("Erro ao alocar memoria para o carrinho.\n");
            exit(1);
        }

        (*carrinho_ptr)->itens = NULL;
        (*carrinho_ptr)->n_itens = 0;
    }
    
    PCarrinho carrinho = *carrinho_ptr;
    
    int posicao_produto = -1;
    int i;
    for (i = 0; i < n_produtos; i++) {
        if (produtos[i].codigo == codigo) {
            posicao_produto = i;
            break;
        }
    }
    if (posicao_produto == -1) {
        printf("\nProduto nao encontrado.");
        return;
    }
    
    for (i = 0; i < carrinho->n_itens; i++) {
        if (carrinho->itens[i].codigo_produto == codigo) {
            printf("O produto ja esta no carrinho.\nAltere a quantidade, se desejar.\n");
            return;
        }
    }

    printf("Digite a quantidade que deseja adicionar ao carrinho: ");
    scanf("%d", &quantidade);

    if (quantidade <= 0) {
        printf("\nQuantidade invalida.");
        return;
    }

    if (quantidade > produtos[posicao_produto].qtd_estoque) {
        printf("\nQuantidade indisponivel em estoque.");
        return;
    }

    carrinho->itens = realloc(carrinho->itens, (carrinho->n_itens + 1) * sizeof(Item));
    if (carrinho->itens == NULL) {
        printf("Erro ao alocar memoria.");
        return;
    }

    PItem novo_item = &(carrinho->itens[carrinho->n_itens]);
    novo_item->codigo_produto = codigo;
    novo_item->quantidade = quantidade;
    carrinho->n_itens++;
	
	printf("\n###########################################");
    printf("\nProduto adicionado ao carrinho com sucesso.");
    printf("\n###########################################");
}

void consultar_carrinho(PCarrinho carrinho, PProduto produtos, int n_produtos) {
    printf("Carrinho de compras:\n");   
    
    if (carrinho == NULL || carrinho->itens == NULL) {
        printf("Carrinho vazio.\n");
        return;
    }    
    int i;
    for (i = 0; i < carrinho->n_itens; i++) {
        PItem item = &(carrinho->itens[i]);
        printf("Codigo: %d\n", item->codigo_produto);
        printf("Quantidade: %d\n", item->quantidade);

        int posicao_produto = -1;
        int j;
        for (j = 0; j < n_produtos; j++) {
            if (produtos[j].codigo == item->codigo_produto) {
                posicao_produto = j;
                break;
            }
        }
        if (posicao_produto != -1) {
            float valor_total = item->quantidade * produtos[posicao_produto].preco;
            printf("Valor Total: %.2f\n", valor_total);
        }
        printf("\n");
        
    }
    return;
}

void excluir_produto_carrinho(PCarrinho carrinho) {
    int codigo, i;
    printf("Digite o codigo do produto que deseja excluir do carrinho: ");
    scanf("%d", &codigo);

    int posicao_produto = -1;
    for (i = 0; i < carrinho->n_itens; i++) {
        if (carrinho->itens[i].codigo_produto == codigo) {
            posicao_produto = i;
            break;
        }
    }

    if (posicao_produto == -1) {
        printf("\nProduto nao encontrado no carrinho.");
        return;
    }

    for (i = posicao_produto; i < carrinho->n_itens - 1; i++) {
        carrinho->itens[i] = carrinho->itens[i + 1];
    }

    carrinho->itens = realloc(carrinho->itens, carrinho->n_itens * sizeof(Item));
    carrinho->n_itens--;
	
	printf("\n#########################################");
    printf("\nProduto removido do carrinho com sucesso!");
    printf("\n#########################################");
    getch();
}

void alterar_quantidade_produto_carrinho(PCarrinho carrinho) {
	int codigo, nova_quantidade, i;
	printf("\nDigite o codigo do produto que deseja alterar a quantidade: ");
    scanf("%d", &codigo);
    
    int posicao_produto = -1;
    for (i = 0; i < carrinho->n_itens; i++) {
        if (carrinho->itens[i].codigo_produto == codigo) {
            posicao_produto = i;
            break;
        }
    }
    
    if (posicao_produto == -1) {
    	printf("\n###################################");
        printf("\nProduto nao encontrado no carrinho.");
        printf("\n###################################");
        return;
	}
	
    printf("Digite a nova quantidade: ");
    scanf("%d", &nova_quantidade);

    if (nova_quantidade <= 0) {
    	printf("\n####################");
        printf("\nQuantidade invalida.");
        printf("\n####################");
        return;
    }

    carrinho->itens[posicao_produto].quantidade = nova_quantidade;
    
    printf("\n###########################################");
    printf("\nQuantidade do produto alterada com sucesso.");
    printf("\n###########################################");
    getch();
}

void finalizar_compra(PCarrinho carrinho, PProduto produtos, int n_produtos) {
    printf("Finalizando a compra...\n\n");

    if (carrinho == NULL || carrinho->itens == NULL || carrinho->n_itens == 0) {
        printf("\nCarrinho estah vazio.");
        return;
    }
	printf("#######################");
    printf("\nDetalhes da compra:");
	printf("\n#######################");
	
    float valor_total = 0.0;
    int i;
    for (i = 0; i < carrinho->n_itens; i++) {
        PItem item = &(carrinho->itens[i]);

        int posicao_produto = -1;
        int j;
        for (j = 0; j < n_produtos; j++) {
            if (produtos[j].codigo == item->codigo_produto) {
                posicao_produto = j;
                break;
            }
        }
        if (posicao_produto != -1) {
            float valor_item = item->quantidade * produtos[posicao_produto].preco;
            printf("\nCodigo: %d\n", item->codigo_produto);
            printf("Descricao: %s\n", produtos[posicao_produto].descricao);
            printf("Quantidade: %d\n", item->quantidade);
            printf("Valor Unitario: %.2f\n", produtos[posicao_produto].preco);
            printf("Valor Total: %.2f\n", valor_item);
            valor_total += valor_item;

            
            produtos[posicao_produto].qtd_estoque -= item->quantidade;
        }
    }
	
	FILE* arquivo = fopen("produtos.txt", "w");
    if (arquivo != NULL) {
        int i;
        for (i = 0; i < n_produtos; i++) {
            Produto *produto = &produtos[i];
	        fprintf(arquivo, "Codigo: %d\n", produto->codigo);
	        fprintf(arquivo, "Descricao: %s\n", produto->descricao);
	        fprintf(arquivo, "Quantidade em estoque: %d\n", produto->qtd_estoque);
	        fprintf(arquivo, "Preco: %.2f\n\n", produto->preco);
        }
        fclose(arquivo);
	}
    printf("\nValor Total da Compra: %.2f\n", valor_total);
    
    free(carrinho->itens);
    carrinho->itens = NULL;
    carrinho->n_itens = 0;

    printf("\nCompra finalizada com sucesso!\n");
}

void esvaziar_carrinho(PCarrinho carrinho) {
    if (carrinho == NULL || carrinho->itens == NULL) {
        printf("\nCarrinho vazio.");
        return;
    }

    free(carrinho->itens);
    carrinho->itens = NULL;
    carrinho->n_itens = 0;
	
	printf("\n###############################");
    printf("\nCarrinho esvaziado com sucesso.");
    printf("\n###############################");
    getch();
}  

void destruir_loja(PPProduto produtos, PCarrinho *carrinho_ptr, int *n_produtos) {
    if (*carrinho_ptr != NULL) {
        free((*carrinho_ptr)->itens);
        free(*carrinho_ptr);
        *carrinho_ptr = NULL;
    }

    free(*produtos);
    *produtos = NULL;

    *n_produtos = 0;
    
    FILE* arquivo = fopen("produtos.txt", "w");
    if (arquivo != NULL) {
        fclose(arquivo);
    }

    printf("\nLoja destruida com sucesso.\n");
}

int main() {
    int opcao, opcao_submenu;
    Produto *produtos = NULL;
    Carrinho *carrinho = NULL;
    int n_produtos = 0;
    
    while (1) {
        system("cls");
        printf("##############");
        printf("\nMENU PRINCIPAL\n");
        printf("##############");
        printf("\n\n1. Gerenciar Produtos");
        printf("\n2. Registrar Pedido de Compra");
        printf("\n3. Excluir Tudo (produtos cadastrados & produtos no carrinho)");
        printf("\n4. Sair");
        printf("\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                while (1) {
                    system("cls");
                    printf("##################");
                    printf("\nGERENCIAR PRODUTOS");
                    printf("\n##################\n");
                    printf("\n1. Incluir produto");
                    printf("\n2. Alterar produto");
                    printf("\n3. Listar produtos");
                    printf("\n4. Consultar produto");
                    printf("\n5. Excluir produto");
                    printf("\n6. Voltar ao menu principal");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &opcao_submenu);

                    switch (opcao_submenu) {
                        case 1:
                        	system("cls");
                            incluir_produto(&produtos, &n_produtos);
                            break;
                        case 2:
                        	system("cls");
                            listar_produtos(produtos, n_produtos);
                            printf("\n#############################\n");
                            alterar_produto(produtos, n_produtos);
                            break;
                        case 3:
                            system("cls");
                            listar_produtos(produtos, n_produtos);
                            getch();
                            break;
                        case 4:
                        	system("cls");
                            consultar_produto(produtos, n_produtos);
                            getch();
                            break;
                        case 5:
                        	system("cls");
                            listar_produtos(produtos, n_produtos);
                            printf("\n####################\n");
                            excluir_produto(produtos, &n_produtos);
                            break;
                        case 6:
                            goto main_menu;
                        default:
                            printf("Opcao invalida.\n");
                    }
                }
            case 2:
                while (1) {
                    system("cls");
                    printf("##########################");
                    printf("\nREGISTRAR PEDIDO DE COMPRA");
                    printf("\n##########################\n");
                    printf("\n1. Adicionar produto no carrinho");
                    printf("\n2. Consultar carrinho de compras");
                    printf("\n3. Excluir produto do carrinho");
                    printf("\n4. Alterar quantidade do produto do carrinho");
                    printf("\n5. Finalizar Pedido");
                    printf("\n6. Esvaziar carrinho de compras");
                    printf("\n7. Voltar ao menu principal");
                    printf("\nEscolha uma opcao: ");
                    scanf("%d", &opcao_submenu);

                    switch (opcao_submenu) {
                        case 1:
                        	system("cls");
                            printf("Adicionar produto no carrinho\n");
                            listar_produtos(produtos, n_produtos);
    						printf("\n##################################\n");
    						adicionar_ao_carrinho(&carrinho, produtos, n_produtos);
                            getch();
                            break;           
                        case 2:
                        	system("cls");
                            printf("Consultar carrinho de compras");
                            consultar_carrinho(carrinho, produtos, n_produtos);
                            getch();
                            break;                         
                        case 3:
                        	system("cls");
						    printf("Excluir produto do carrinho\n");
						    consultar_carrinho(carrinho, produtos, n_produtos);
						    printf("\n#######################################\n");
						    excluir_produto_carrinho(carrinho);
						    break;
                        case 4:
                        	system("cls");
                            printf("Alterar quantidade do produto do carrinho");
                            alterar_quantidade_produto_carrinho(carrinho);
                            getch();
                            break;
                        case 5:
                        	system("cls");
                            printf("Finalizar Pedido\n\n");
                            finalizar_compra(carrinho, produtos, n_produtos);
                            getch();
                            break;
                        case 6:
                        	system("cls");
                            printf("Esvaziar carrinho de compras\n");
                            esvaziar_carrinho(carrinho);
                            getch();
                            break;
                        case 7:
                            goto main_menu;
                        default:
                            printf("Opcao invalida.\n");
                    }
                }
            case 3:
				destruir_loja(&produtos, &carrinho, &n_produtos);
                getch();
                break;
            case 4:
                free(produtos);
				free(carrinho);
                return 0;    
            default:
                system("cls");
                printf("Opcao invalida.\n");
                getch();
                break;
        }
        main_menu:;
    }

    return 0;
}
