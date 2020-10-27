#ifndef PRODUTO_H_INCLUDED
#define PRODUTO_H_INCLUDED

void adicionaProduto(int &menu) {
char descricao[250];
int id,quantidade;
float preco;
setbuf(stdin, NULL);
char continuar;
int pass = 0 ;
system("cls");
    do{
        setbuf(stdin, NULL);
        pass = 0;
        int i = 0;
        int k = 0;
        do{
            setbuf(stdin, NULL);
            title("NERDZ\n");
            title("ADICIONAR PRODUTO\n\n");
            if(i > 0){
            printf("\tComando ou nome inválido, tente novamente!\n");
            }
            printf("Digite o nome do produto! (C - Cancelar | M - Voltar ao menu)\n");
            scanf("%[^\n]", &descricao);
            if(strcmp(descricao, "m") == 0 || strcmp(descricao, "M") == 0){
                menu = 1;
                char descricao[250];
                return;
            }
            if (strcmp(descricao, "c") == 0 || strcmp(descricao, "C") == 0){
                char descricao[250];
                system("cls");
                return;
            }
            printf("Digite o nome do produto!\n");
            scanf("%[^\n]", &nome_produto);
            setbuf(stdin, NULL);
            printf("Digite a quantidade!\n");
            scanf("%d",&quantidade);
            setbuf(stdin, NULL);
            printf("Digite o valor de tal produto!\n");
            scanf("%f",&preco);
            setbuf(stdin, NULL);
            system("cls");
            i++;
        }while(verificaNome(descricao) == 0 || strlen(descricao) == 1 && !((strcmp(descricao, "c") == 0 || strcmp(descricao, "C") == 0) || (strcmp(descricao, "m") == 0 || strcmp(descricao, "M") == 0)));    
    FILE* estoque;
    FILE* estoque_2;
    int id_busca,id=0;
    estoque = fopen("produtos.sq", "a");
    estoque_2 = fopen("produtos.sq", "r");
	while (true) {
        int ret = fscanf(estoque_2, "%*s %d", &id_busca);
        if(ret == 1){
             id = id_busca;
        }
        else{
            rewind(estoque);
            break;
        }
    }
    fprintf(estoque, "produto_id %d descricao %s qtd_estoque %d valor(R$) %2f \n",id+1, descricao, qtd, preco);
	system("cls");
	printf("\nProduto adicionado com sucesso!\n\n");
	fclose (estoque_2);
    fclose (estoque);
    printf("Deseja adicionar outro cliente? S - Sim; N - Não.");
    do{
        if(k > 0){
            system("cls");
            printf("\nComando inválido! Tente novamente!");
            printf("\n\nDeseja adicionar outro cliente? S - Sim; N - Não.");
        }
        setbuf(stdin, NULL);
        scanf("%c", &continuar);
        k++;
    }while((continuar != 's' && continuar != 'S') && (continuar != 'n' && continuar != 'N'));
    if(continuar == 's' || continuar == 'S'){
        pass = 1;
    }
    system("cls");
    }while(pass == 1);
}

void editaProduto(int& menu) {
    int reset = 0;
    do{
    reset = 0;
	FILE* estoque;
	FILE* estoque_temp;
	int id,qtd,qtd_busca;
    float preco,preco_busca;
	char busca[500],id_busca[250];
	char descricao_busca[250];
	char descricao[250];
	estoque = fopen("produtos.sq", "r");
	int i = 0;
	system("cls");
	// Título da página - Só mudar a string
	title("EDITOR DE PRODUTO\n");
	int ret;
	while (true) {
        ret = fscanf(estoque, "%*s %d %*s %s %*s %d %*s %f", &id, &descricao,&qtd, &preco);
        // Verifica se existe registros no banco de dados
        if(ret == -1 && i == 0){
           printf("Não há produtos para serem editados!\n\n");
           ret = -1;
           break;
        }
        if(ret == 4){
            if(i == 0){
                printf("\nSelecione um dos produtos abaixo, digitando o seu ID:\n\n");
            }
            printf("Produto => ID: %d  -  descricao: %s - quantidade: %d - valor: %2f \n", id, descricao,qtd,preco);
        }
        else{
            rewind(estoque);
            ret = 0;
            break;
        }
        i++;
    }
    if(ret != -1){
        printf("\nDigite o ID de um dos produtos acima! (C - Cancelar | M - Voltar ao menu): ");
        setbuf(stdin, NULL);
        scanf("%[^\n]", &busca);
        if(strcmp(busca, "m") == 0 || strcmp(busca, "M") == 0){
            menu = 1;
            char busca[500];
            fclose(estoque);
            return;
        }
        if (strcmp(busca, "c") == 0 || strcmp(busca, "C") == 0){
            char busca[500];
            fclose(estoque);
            system("cls");
            return;
        }
        while(true){
            setbuf(stdin, NULL);
            ret = fscanf(estoque, "%*s %s %*s %s %*s %d %*s %f", &id_busca, &descricao_busca,&qtd_busca,&preco_busca);
            if(ret == -1){
                break;
            }
            if(ret == 2){
                if(strcmp(id_busca, busca) == 0){
                    printf("\n\tProduto selecionado: ID = %d", id_busca);
                    printf("\n\tdescricao atual do produto: %s", descricao_busca);
                    printf("\n\tquantidade do produto: %d",qtd_busca);
                    printf("\n\tvalor do produto: %2f",preco_busca);
                    printf("\n\n(T - Selecionar outro produto; C - Voltar; M - Voltar para o menu)\nNovo descricao do produto:");
                    int t = 0;
                    do{
                        if(t++ > 0){
                        title("EDITOR DE produto\n");
                        printf("\n\tProduto selecionado: ID = %d", id_busca);
                        printf("\n\tDescricao atual do produto: %s", descricao_busca);
                        printf("\n\nNovo descricao do produto:");
                        }
                        setbuf(stdin, NULL);
                        scanf("%[^\n]", &descricao);
                        printf("\n\tQuantidade atual do produto: %d",qtd_busca);
                        printf("\n\nNova quantidade do produto:");
                        setbuf(stdin, NULL);
                        scanf("%d", &qtd);
                        printf("\n\tValor atual do produto: %2f",preco_busca);
                        printf("\n\nNovo valor do produto:")
                        setbuf(stdin, NULL);
                        scanf("%f", &preco);
                        system("cls");
                    }while(verificaNome(descricao) == 0);
                    if(strcmp(descricao, "c") == 0 || strcmp(descricao, "C") == 0){
                        return;
                    }
                    if(strcmp(descricao, "m") == 0 || strcmp(descricao, "M") == 0){
                        menu = 1;
                        return;
                    }
                    if(strcmp(descricao, "t") == 0 || strcmp(descricao, "T") == 0){
                        reset = 1;
                        fclose(estoque);
                        break;
                    }
                    estoque_temp = fopen("produtos_temp.sq", "a");
                    rewind(estoque);
                    int id_2,qtd_2;
                    float preco_2
                    char descricao_2[250];
                    while(true){
                        int req = fscanf(estoque, "%*s %d %*s %s %*s %d %*s %f", &id_2, &descricao_2,&qtd_2, &preco_2);
                        if(req == -1){
                            break;
                        }
                        if(req == 2){
                            if(strcmp(id_2, id_busca) == 0){
                                fprintf(estoque_temp, "produto_id %d descricao %s qtd_estoque %d valor(R$) %2f \n", id_2, descricao,qtd,preco);
                            }
                            else{
                                fprintf(estoque_temp, "produto_id %d descricao %s qtd_estoque %d valor(R$) %2f \n", id_2, descricao_2, qtd_2, preco_2);
                            }
                        }

                    }
                    fclose(estoque_temp);
                }
            }
        }
        printf("\nProduto editado com sucesso!\n\n");
        fclose(estoque);
        remove("produtos.sq");
        rename("produtos_temp.sq", "produtos.sq");
    }
    else{
        printf("\nC - Voltar; M - Voltar ao menu\n");
        setbuf(stdin, NULL);
        scanf("%[^\n]", &busca);
        if(strcmp(busca, "m") == 0 || strcmp(busca, "M") == 0){
            menu = 1;
            char busca[500];
            fclose(estoque);
            return;
        }
        if (strcmp(busca, "c") == 0 || strcmp(busca, "C") == 0){
            char busca[500];
            fclose(estoque);
            return;
        }
    }
    }while(reset == 1);
}



void produtos(int& menu) {
    while(true){
        if(menu == 1){
            return;
        }
        title("PRODUTO");
        int ui;
        printf("\n1 - Adicionar Produto;\n2 - Editar Produto;\n3 - Lista Produto;\n4 - Remover Produto;\n5 - Voltar para o menu inicial.\n\n");
        setbuf(stdin, NULL);
        scanf("%d", &ui);
        if (ui == 1) {            
            adicionaProduto(descricao_Produto,id,quantidade,preco);
        }
        if (ui == 2){
            editaProduto(menu);
        }
        if (ui == 5){
            system("cls");
            return;
        }
    }
}



#endif




