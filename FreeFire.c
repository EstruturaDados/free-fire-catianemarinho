#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMITE_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

/* Representa um item da mochila */
typedef struct {
    char nome[TAM_NOME];
    char categoria[TAM_TIPO];
    int quantidade;
} Registro;

Registro mochila[LIMITE_ITENS];
int itensTotais = 0;

/* Remove quebra de linha do fgets */
void retirarQuebraLinha(char *s) {
    size_t tam = strlen(s);
    if (tam > 0 && s[tam - 1] == '\n') {
        s[tam - 1] = '\0';
    }
}

/* Exibição geral dos itens */
void mostrarInventario() {
    if (itensTotais == 0) {
        printf("A mochila está vazia no momento.\n");
        return;
    }

    printf("\n--- Conteúdo da Mochila (%d itens) ---\n", itensTotais);

    for (int i = 0; i < itensTotais; i++) {
        printf("%d) Nome: %s | Categoria: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].categoria,
               mochila[i].quantidade);
    }
}

/* Procura item por nome — retorna índice ou -1 */
int localizarPorNome(const char *busca) {
    for (int i = 0; i < itensTotais; i++) {
        if (strcmp(mochila[i].nome, busca) == 0) {
            return i;
        }
    }
    return -1;
}

/* Insere novo item ou soma quantidade caso já exista */
void adicionarItem() {
    if (itensTotais >= LIMITE_ITENS) {
        printf("A mochila atingiu sua capacidade máxima.\n");
        return;
    }

    Registro novo;

    printf("Informe o nome do item: ");
    fgets(novo.nome, TAM_NOME, stdin);
    retirarQuebraLinha(novo.nome);

    if (strlen(novo.nome) == 0) {
        printf("Nome inválido. Operação cancelada.\n");
        return;
    }

    printf("Informe a categoria (cura/arma/municao/outros): ");
    fgets(novo.categoria, TAM_TIPO, stdin);
    retirarQuebraLinha(novo.categoria);

    if (strlen(novo.categoria) == 0) {
        strcpy(novo.categoria, "indefinido");
    }

    printf("Quantidade: ");
    if (scanf("%d", &novo.quantidade) != 1) {
        printf("Entrada inválida!\n");
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    int c; while ((c = getchar()) != '\n' && c != EOF); // limpa buffer

    int pos = localizarPorNome(novo.nome);

    if (pos != -1) {
        mochila[pos].quantidade += novo.quantidade;
        printf("Item já existia. Nova quantidade: %d\n", mochila[pos].quantidade);
    } else {
        mochila[itensTotais++] = novo;
        printf("Item cadastrado na mochila!\n");
    }
}

/* Remoção de item pelo nome */
void excluirItem() {
    char nomeBusca[TAM_NOME];

    printf("Informe o nome do item para remover: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    retirarQuebraLinha(nomeBusca);

    int pos = localizarPorNome(nomeBusca);

    if (pos == -1) {
        printf("Nenhum item encontrado com esse nome.\n");
        return;
    }

    for (int i = pos; i < itensTotais - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    itensTotais--;
    printf("Item removido com sucesso.\n");
}

/* Busca item e exibe informações */
void consultarItem() {
    char nomeBusca[TAM_NOME];

    printf("Digite o nome do item a pesquisar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    retirarQuebraLinha(nomeBusca);

    int pos = localizarPorNome(nomeBusca);

    if (pos == -1) {
        printf("Item não encontrado.\n");
    } else {
        printf("Encontrado! -> Nome: %s | Categoria: %s | Quantidade: %d\n",
               mochila[pos].nome,
               mochila[pos].categoria,
               mochila[pos].quantidade);
    }
}

/* Menu de ações */
int exibirMenu() {
    printf("\n==== MENU — Inventário de Jogo ====\n");
    printf("1 - Adicionar item\n");
    printf("2 - Remover item\n");
    printf("3 - Exibir mochila\n");
    printf("4 - Buscar item\n");
    printf("0 - Finalizar programa\n");
    printf("Escolha sua opção: ");

    int opcao;

    if (scanf("%d", &opcao) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF);
        return -1;
    }

    int c; while ((c = getchar()) != '\n' && c != EOF);
    return opcao;
}

/* Função principal */
int main() {
    int escolha;

    printf("=== Sistema de Inventário — Versão Aprimorada ===\n");

    do {
        escolha = exibirMenu();

        switch (escolha) {
            case 1: adicionarItem(); break;
            case 2: excluirItem(); break;
            case 3: mostrarInventario(); break;
            case 4: consultarItem(); break;
            case 0: printf("Encerrando... Até logo!\n"); break;
            default: printf("Opção inválida.\n");
        }

    } while (escolha != 0);

    return 0;
}
