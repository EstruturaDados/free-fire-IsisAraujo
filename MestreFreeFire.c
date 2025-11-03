#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

enum Criterio
{
    NOME = 1,
    TIPO,
    PRIORIDADE
};

struct Item
{
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
};

// Funções auxiliares
void ordenar(struct Item *mochila, int total, enum Criterio crit, int *comparacoes);
int buscaBinaria(struct Item *mochila, int total, const char *nome);
void listar(struct Item *mochila, int total);

int main()
{
    struct Item mochila[MAX_ITENS];
    int total = 0, opcao, comparacoes = 0;
    bool ordenadaPorNome = false;

    do
    {
        printf("\n=== MENU DO INVENTÁRIO ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Listar itens\n");
        printf("3 - Ordenar mochila\n");
        printf("4 - Buscar item (binária por nome)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            if (total < MAX_ITENS)
            {
                printf("Nome: ");
                fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                printf("Prioridade (1-5): ");
                scanf("%d", &mochila[total].prioridade);
                getchar();

                total++;
                ordenadaPorNome = false;
            }
            else
            {
                printf("Mochila cheia!\n");
            }
            break;

        case 2:
            listar(mochila, total);
            break;

        case 3:
        {
            printf("\nOrdenar por:\n1 - Nome\n2 - Tipo\n3 - Prioridade\nEscolha: ");
            int criterio;
            scanf("%d", &criterio);
            getchar();

            comparacoes = 0;
            ordenar(mochila, total, criterio, &comparacoes);
            printf("Mochila ordenada (%d comparações).\n", comparacoes);
            ordenadaPorNome = (criterio == NOME);
            break;
        }

        case 4:
        {
            if (!ordenadaPorNome)
            {
                printf("A mochila precisa estar ordenada por nome antes da busca.\n");
                break;
            }

            char nomeBusca[50];
            printf("Digite o nome do item para buscar: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            int pos = buscaBinaria(mochila, total, nomeBusca);
            if (pos != -1)
                printf("Item encontrado: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                       mochila[pos].nome, mochila[pos].tipo,
                       mochila[pos].quantidade, mochila[pos].prioridade);
            else
                printf("Item não encontrado.\n");
            break;
        }

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Funções auxiliares
void listar(struct Item *mochila, int total)
{
    if (total == 0)
    {
        printf("Mochila vazia.\n");
        return;
    }
    printf("\n%-20s %-15s %-10s %-10s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("%-20s %-15s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo,
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

void ordenar(struct Item *mochila, int total, enum Criterio crit, int *comparacoes)
{
    struct Item chave;
    int j;

    for (int i = 1; i < total; i++)
    {
        chave = mochila[i];
        j = i - 1;

        while (j >= 0)
        {
            (*comparacoes)++;
            int cmp = 0;
            if (crit == NOME)
                cmp = strcmp(mochila[j].nome, chave.nome);
            else if (crit == TIPO)
                cmp = strcmp(mochila[j].tipo, chave.tipo);
            else
                cmp = mochila[j].prioridade - chave.prioridade;

            if (cmp > 0)
            {
                mochila[j + 1] = mochila[j];
                j--;
            }
            else
                break;
        }
        mochila[j + 1] = chave;
    }
}

int buscaBinaria(struct Item *mochila, int total, const char *nome)
{
    int ini = 0, fim = total - 1;
    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0)
            return meio;
        if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}
