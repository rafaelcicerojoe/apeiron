#ifndef VENDAS_H_INCLUDED
#define VENDAS_H_INCLUDED

void catalogoVenda(int &menu){
    int reset = 0;
    do{
    reset = 0;
	FILE* estoque;
	int id,quantidade;
    int i = 0,k = 0;
    float preco;
	char busca[250];
    int ret;
	estoque = fopen("produtos.sq", "r");
	system("cls");
	// Título da página - Só mudar a string
	title("CATÁLOGO\n\n");
	while (true) {
        ret = fscanf(estoque, "%*s %d %*s %s %*s %d %*s %f", &id, &busca,&qtd, &preco);
        // Verifica se existe registros no banco de dados
        if(ret == -1 && i == 0){
           printf("Não há produtos!\n\n");
           ret = -1;
           break;
        }
        if(ret == 4){
            printf("Produto => ID: %d  -  busca: %s - quantidade: %d - valor: %2f \n", id, busca,qtd,preco);
        }
        else{
            rewind(estoque);
            ret = 0;
            break;
        }
     i++;
    }
    printf("\n\nDeseja rever os produtos? S - Sim; N - Não.");
    do{
        if(k > 0){
            system("cls");
            printf("\nComando inválido! Tente novamente!");
            printf("\n\nDeseja rever os produtos? S - Sim; N - Não.");
        }
        setbuf(stdin, NULL);
        scanf("%c", &continuar);
        k++;
    }while((continuar != 's' && continuar != 'S') && (continuar != 'n' && continuar != 'N'));
    if(continuar == 's' || continuar == 'S'){
        reset = 1;
    }
    system("cls");
    }while(reset == 1);


}

void descontoVenda(int &menu){

//fica mais interessante se os descontos forem variaveis multiplicadoras por floats

}
void venderProduto(FILE *estoque, int id_produto, int qtd_venda){
  FILE* estoque;
  estoque = fopen("produtos.sq", "r");
  int linhas = 0;
  char str[300];
  while (fgets(str,100,estoque) != NULL) {
    linhas++;
  }
  rewind(estoque);
  FILE* estoque_temporario;
  estoque_temporario = fopen("arq_temp.sq", "a");
  for(int i = 0; i < linhas; i++){
    int id;
    int qtd;
    char descricao[250];
    fscanf(estoque, "%*s %d %*s %s %*s %d", &id, &descricao, &qtd);
    if(id == id_produto){
      if(qtd == 0){
        printf("Processo não se sucedeu pois quantidade atual do produto é 0!");
        break;
      }
      int qtd_final = qtd-qtd_venda;
      if(qtd_final < 0){
        printf("Processo não se sucedeu pois a quantidade pedida em relaçao a existente é menor que 0!");
        break;
        }
      fprintf(estoque_temporario, "produto_id %d descricao %s qtd_estoque %d\n", id, descricao, qtd_final);
    }
    else{
    fprintf(estoque_temporario, "produto_id %d descricao %s qtd_estoque %d\n", id, descricao, qtd);
    }
  }
  remove(arq_estoque);
  rename("arq_temp.sql", "produtos.sq");
  fclose(estoque_temporario);
  fclose(estoque);
}


void processoVenda(int &menu){
FILE *vendas_dia,*nota_fiscal,*estoque,*leitura_cliente;
int id_prod,qtd_prod;
char busca_cliente[500],id_cliente[250],descriçao_prod[250],busca_prod;
vendas_dia=fopen("vendas_diarias","a");
estoque=fopen("produtos.sq","r");
nota_fiscal=fopen("nota_fiscal.sq","w");
leitura_cliente=fopen("clientes.sq","r");
fprintf(vendas_dia,"\tNERDZ\n\n");
  printf("Digite o codigo do produto:\n ");
  scanf("%d", &id_prod);
  printf("Digite a quantidade do produto:\n ");
  scanf("%d", &qtd_prod);
  printf("Digite a id do cliente:\n ");
  scanf("%s", &busca_cliente);
  venderProduto(estoque, id_prod, qtd_prod);
while(true){
    fscanf(leitura_cliente, "%*s %s", &id_cliente);
    if((strcmp(busca_cliente,)))
}

}

void balancoVenda(int &menu){

//FILE *vendas_dia=fopen(--vendas registradas e alocadas no final de um arquivo ficaria interesante
//(iniciando em modo de leitura{acho que tu já falou sobre isso}) e grava das outro com nome da loja --pre-- registrado,)



}

void vendas(int& menu){
    while(true){
        if(menu == 1){
            return;
        }
        title("VENDAS");
        int ui;
        printf("\n1 - Fazer venda;\n2 - Catálogo;\n3 - Descontos;\n4 - Balanço Diario;\n5 - Voltar para o menu inicial.\n\n");
        setbuf(stdin, NULL);
        scanf("%d", &ui);
        if (ui == 1) {
            processoVenda(menu);       
        }
        if (ui == 2){
            catalogoVenda(menu);
        }
        if (ui == 3){
            descontoVenda(menu);
        }
        if (ui == 4){
            balancoVenda(menu);
        }
        if (ui == 5){
            system("cls");
            return;
        }
    }
}














#endif