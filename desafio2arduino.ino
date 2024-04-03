#include <stdio.h>

char jogo[3][30];
char produtora[3][20];

void escrever(FILE*arquivo);
void ler(FILE*arquivo);
int pesquisarJogo(FILE* arquivo);
void pesquisarProdutora(FILE*arquivo);
void alterarDados(FILE*arquivo);
void excluirDados(FILE*arquivo);


int main()
{
    FILE* arquivo;
    arquivo = fopen("Dados.txt","r");
    int op,continuar;

    do
    {
        do
        {
            printf("\n\nMenu de opcoes\n");
            printf("1- Entrada de dados\n");
            printf("2- Todos os dados\n");
            printf("3- Pesquisa o jogo pelo nome completo\n");
            printf("4- Pesquisa a produtora pela 1 letra\n");
            printf("5- Altera os dados\n");
            printf("6- Exclui os dados\n");
            printf("7- Sair\n\n");
            scanf("%d", &op);

        }
        while (op <= 0 || op > 7);

        system("cls");

        switch (op)
        {
        case 1:
            escrever(arquivo);
            break;
        case 2:
            ler(arquivo);
            break;
        case 3:
            pesquisarJogo(arquivo);
            break;
        case 4:
            pesquisarProdutora(arquivo);
            break;
        case 5:
            alterarDados(arquivo);
            break;
        case 6:
            excluirDados(arquivo);
            break;
        case 7:
            sair();
            break;
        }
        fclose(arquivo);

    }
    while(op!=7);
}

void escrever(FILE*arquivo)
{
    int c;
    arquivo = fopen("Dados.txt", "w");



    printf("Digite o nome do jogo e produtora\n");
    getchar();
    for (c=0; c<3; c++)

    {
        printf ("\n\nDigite o %d jogo: \n",c+1);
        gets (jogo[c]);



        printf ("\nDigite a produtora do %d jogo: \n",c+1);
        gets (produtora[c]);

    }
    if(arquivo==NULL)

    {
        printf("Arquivo inexistente\n");
        return 1;
    }


    for(c=0; c<3; c++)
    {
        fwrite(jogo[c],sizeof(jogo[c]),1,arquivo);
        fwrite(produtora[c],sizeof(produtora[c]),1,arquivo);
    }
    fclose(arquivo);
}
void ler(FILE*arquivo)
{
    int c;
    arquivo=fopen("Dados.txt","r");

    if(arquivo==NULL)

    {
        printf("Arquivo inexistente\n");
        return;
    }
    for(c=0; c<3; c++)
    {
        fread(jogo[c],sizeof(jogo[c]),1,arquivo);
        fread(produtora[c],sizeof(produtora[c]),1,arquivo);

        printf("Jogo:%s\nProdutora:%s\n\n", jogo[c], produtora[c]);
    }
    fclose(arquivo);
}

int pesquisarJogo(FILE* arquivo)
{
    arquivo = fopen("Dados.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    char nome[30];
    int i, c, j;
    printf("Digite o nome completo do jogo:\n");
    scanf(" %[^\n]s", nome);
    for (c = 0; c < 3; c++)
    {
        fread(jogo[c], sizeof(jogo[c]), 1, arquivo);
        fread(produtora[c], sizeof(produtora[c]), 1, arquivo);
    }
    for (j = 0; j < 3; j++)
    {
        for (i = 0; nome[i] != '\0' && jogo[j][i] != '\0'; i++)
        {
            if (nome[i] != jogo[j][i])
            {
                break;
            }
        }
        if (nome[i] == '\0' && jogo[j][i] == '\0')
        {
            system("cls");
            printf("\nJogo: %s\n", jogo[j]);
            printf("Produtora: %s\n", produtora[j]);
            fclose(arquivo);
            return j;
        }
    }
    printf("Jogo nao encontrado.\n");
    fclose(arquivo);
    return -1;
}

void pesquisarProdutora(FILE*arquivo)
{
    char letra;
    int i, c;
    arquivo = fopen("Dados.txt", "r");
    for(c=0; c<3; c++)
    {
        fread(jogo[c],sizeof(jogo[c]),1,arquivo);
        fread(produtora[c],sizeof(produtora[c]),1,arquivo);
    }
    printf("Digite a primeira letra da produtora:\n");
    scanf("%s", &letra);
    system("cls");
    printf("\nProdutoras:\n");
    for (i = 0; i < 3; i++)
    {
        if (produtora[i][0] == letra)
        {
            printf("%s\n", produtora[i]);
        }
    }
    fclose(arquivo);
}

void alterarDados(FILE*arquivo)
{
    int opcao, i;

    do
    {
    system("cls");
    printf("O que deseja alterar:\n1- Jogo\n2- Produtora\n");
    scanf("%d", &opcao);
    }
    while (opcao <= 0 || opcao > 2);

    switch(opcao)
    {
    case 1:
    {
        int jogo_encontrado = pesquisarJogo(arquivo);
        if (jogo_encontrado != -1)
        {
            printf("\nDigite o novo nome do jogo:\n");
            scanf("%s", &jogo[jogo_encontrado]);
            arquivo = fopen("Dados.txt", "w");
            for (i = 0; i < 3; i++)
            {
                fwrite(jogo[i], sizeof(jogo[i]), 1, arquivo);
                fwrite(produtora[i], sizeof(produtora[i]), 1, arquivo);
            }
            system("cls");
            printf("\nJogo alterado com sucesso!\n");
            fclose(arquivo);
        }
        break;
    }
    case 2:
    {
        int jogo_encontrado = pesquisarJogo(arquivo);
        if (jogo_encontrado != -1)
        {
            printf("\nDigite a nova produtora:\n");
            scanf("%s", &produtora[jogo_encontrado]);
            arquivo = fopen("Dados.txt", "w");
            for (i = 0; i < 3; i++)
            {
                fwrite(jogo[i], sizeof(jogo[i]), 1, arquivo);
                fwrite(produtora[i], sizeof(produtora[i]), 1, arquivo);
            }
            system("cls");
            printf("\n Produtora alterada com sucesso!\n");
            fclose(arquivo);
        }
        break;
    }

        //printf("Opcao invalida!\n");
    }
    fclose(arquivo);
}

void excluirDados(FILE*arquivo)
{
    int jogo_encontrado = pesquisarJogo(arquivo);
    int c;
    if (jogo_encontrado != -1)
    {
        arquivo = fopen("Dados.txt", "w");

        for (int i = 0; i < 3; i++)
        {
            if (i != jogo_encontrado)
            {
               fwrite(jogo[i], sizeof(jogo[i]), 1, arquivo);
               fwrite(produtora[i], sizeof(produtora[i]), 1, arquivo);
            }
        }

           for (c = 0; c < 3; c++)
    {
        fread(jogo[c], sizeof(jogo[c]), 1, arquivo);
        fread(produtora[c], sizeof(produtora[c]), 1, arquivo);
    }
        printf("Jogo e produtora excluidos com sucesso!\n");
        fclose(arquivo);
    }
}

sair()
{
    printf("Programa encerrado\n");
    exit(0);
}
