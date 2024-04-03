#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Jogo {
    char nome[100];
    char produtora[100];
    int quantidade;
    float preco;
};

void entradaDados(FILE *arquivo) {

    struct Jogo novoJogo;
    system("cls");
    printf("Nome do jogo: ");
    scanf("%s", novoJogo.nome);
    printf("Produtora: ");
    scanf("%s", novoJogo.produtora);
    printf("Quantidade: ");
    scanf("%d", &novoJogo.quantidade);
    printf("Preco: ");
    scanf("%f", &novoJogo.preco);

    fseek(arquivo, 0, SEEK_END);
    fwrite(&novoJogo, sizeof(struct Jogo), 1, arquivo);
    printf("Dados salvos com sucesso!\n");
    fclose(arquivo);
    }


void listarDados() {
    FILE *arquivo = fopen("dados.txt", "r");
    struct Jogo jogo;
    fseek(arquivo, 0, SEEK_SET);
    system("cls");
    printf("----- Dados dos jogos -----\n");
    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        printf("Nome: %s\n", jogo.nome);
        printf("Produtora: %s\n", jogo.produtora);
        printf("Quantidade: %d\n", jogo.quantidade);
        printf("Preco: %.2f\n", jogo.preco);
        printf("--------------------------\n");
    }
    fclose(arquivo);
}

void pesquisarJogo(FILE *arquivo) {
    struct Jogo jogo;
    char nome[100];
    system("cls");
    printf("Digite o nome completo do jogo: ");
    scanf("%s", nome);
    fseek(arquivo, 0, SEEK_SET);


    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(nome, jogo.nome) == 0) {
            printf("Nome: %s\n", jogo.nome);
            printf("Produtora: %s\n", jogo.produtora);
            printf("Quantidade: %d\n", jogo.quantidade);
            printf("Preco: %.2f\n", jogo.preco);
            return;
        }
    }

    printf("Jogo nao encontrado.\n");
}

void pesquisarProdutora(FILE *arquivo) {
    struct Jogo jogo;
    char produtora[100];
    system("cls");
    printf("Digite o nome completo da produtora: ");
    scanf("%s", produtora);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(produtora, jogo.produtora) == 0) {
            printf("Nome: %s\n", jogo.nome);
            printf("Produtora: %s\n", jogo.produtora);
            printf("Quantidade: %d\n", jogo.quantidade);
            printf("Preco: %.2f\n", jogo.preco);
        }
    }
}

void pesquisarFaixaPreco(FILE *arquivo) {
    struct Jogo jogo;
    float precoMin, precoMax;
    system("cls");
    printf("Digite o preco minimo: ");
    scanf("%f", &precoMin);
    printf("Digite o preco maximo: ");
    scanf("%f", &precoMax);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (jogo.preco >= precoMin && jogo.preco <= precoMax) {
            printf("Nome: %s\n", jogo.nome);
            printf("Produtora: %s\n", jogo.produtora);
            printf("Quantidade: %d\n", jogo.quantidade);
            printf("Preco: %.2f\n", jogo.preco);
        }
    }
}

void alterarQuantidade() {
    FILE *arquivo = fopen("dados.txt", "r+");
    struct Jogo jogo;
    char nome[100];
    int quantidadeNova;
    system("cls");
    printf("Digite o nome completo do jogo: ");
    scanf("%s", nome);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(nome, jogo.nome) == 0) {
            printf("Digite a nova quantidade: ");
            scanf("%d", &quantidadeNova);

            jogo.quantidade = quantidadeNova;
            fseek(arquivo, -sizeof(struct Jogo), SEEK_CUR);
            fwrite(&jogo, sizeof(struct Jogo), 1, arquivo);

            fclose(arquivo);
            printf("Quantidade alterada com sucesso!\n");
            return;
        }
    }

    printf("Jogo nao encontrado.\n");


}

void alterarPreco() {
    FILE *arquivo = fopen("dados.txt", "r+");
    struct Jogo jogo;
    char nome[100];
    float precoNovo;
    system("cls");
    printf("Digite o nome completo do jogo: ");
    scanf("%s", nome);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(nome, jogo.nome) == 0) {
            printf("Digite o novo preco: ");
            scanf("%f", &precoNovo);

            jogo.preco = precoNovo;
            fseek(arquivo, -sizeof(struct Jogo), SEEK_CUR);
            fwrite(&jogo, sizeof(struct Jogo), 1, arquivo);

            fclose(arquivo);
            printf("Preco alterado com sucesso!\n");
            return;
        }
    }

    printf("Jogo nao encontrado.\n");
}

void alterarDados() {
    FILE *arquivo = fopen("dados.txt", "r+");
    struct Jogo jogo;
    char nome[100];
    char novoNome[100], novaProdutora[100];
    int novaQuantidade;
    float novoPreco;
    system("cls");
    printf("Digite o nome completo do jogo: ");
    scanf("%s", nome);

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(nome, jogo.nome) == 0) {
            printf("Novo nome: ");
            scanf("%s", novoNome);
            printf("Nova produtora: ");
            scanf("%s", novaProdutora);
            printf("Nova quantidade: ");
            scanf("%d", &novaQuantidade);
            printf("Novo preco: ");
            scanf("%f", &novoPreco);

            strcpy(jogo.nome, novoNome);
            strcpy(jogo.produtora, novaProdutora);
            jogo.quantidade = novaQuantidade;
            jogo.preco = novoPreco;

            fseek(arquivo, -sizeof(struct Jogo), SEEK_CUR);
            fwrite(&jogo, sizeof(struct Jogo), 1, arquivo);

            fclose(arquivo);
            printf("Dados alterados com sucesso!\n");
            return;
        }
    }

    printf("Jogo nao encontrado.\n");
}
void excluirDados(FILE *arquivo) {
    struct Jogo jogo;
    char nome[100];
    system("cls");
    printf("Digite o nome completo do jogo: ");
    scanf("%s", nome);

    FILE *arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL) {
        printf("Erro ao abrir o arquivo temporario.\n");
        return;
    }

    fseek(arquivo, 0, SEEK_SET);

    while (fread(&jogo, sizeof(struct Jogo), 1, arquivo) == 1) {
        if (strcmp(nome, jogo.nome) != 0) {
            fwrite(&jogo, sizeof(struct Jogo), 1, arquivoTemp);
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("dados.txt");
    rename("temp.txt", "dados.txt");

    arquivo = fopen("dados.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de dados.\n");
        return;
    }

    printf("Dados excluidos com sucesso!\n");
}

int main() {
    FILE *arquivo = fopen("dados.txt", "a+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de dados.\n");
        return 1;
    }

    int opcao;

    do {
        printf("\n----- MENU -----\n");
        printf("1 - Entrada de dados\n");
        printf("2 - Listar todos os dados\n");
        printf("3 - Pesquisar jogo pelo nome completo\n");
        printf("4 - Pesquisar produtora pelo nome completo\n");
        printf("5 - Pesquisar jogo por faixa de preco\n");
        printf("6 - Alterar quantidade pesquisado pelo nome completo\n");
        printf("7 - Alterar preco de um jogo pesquisado pelo nome completo\n");
        printf("8 - Alterar dados pesquisado pelo nome completo\n");
        printf("9 - Excluir dados pesquisado pelo nome completo\n");
        printf("10 - Saida\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                entradaDados(arquivo);
                break;
            case 2:
                listarDados(arquivo);
                break;
            case 3:
                pesquisarJogo(arquivo);
                break;
            case 4:
                pesquisarProdutora(arquivo);
                break;
            case 5:
                pesquisarFaixaPreco(arquivo);
                break;
            case 6:
                alterarQuantidade(arquivo);
                break;
            case 7:
                alterarPreco(arquivo);
                break;
            case 8:
                alterarDados(arquivo);
                break;
            case 9:
                excluirDados(arquivo);
                break;
            case 10:
                printf("Saida pelo usuario.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (opcao != 10);

    fclose(arquivo);

    return 0;
}
