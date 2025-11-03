#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

struct Item
{
    char nome[50];
    char tipo[30];
    int quantidade;
};

int main()
{
    struct Item mochila[MAX_ITENS];
    int total = 0, opcao;

    do
    {
        printf("\n=== MENU DO INVENTÁRIO ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item por nome\n");
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
                getchar();

                total++;
                printf("Item adicionado!\n");
            }
            else
            {
                printf("Mochila cheia!\n");
            }
            break;

        case 2:
        {
            char nomeRemover[50];
            int encontrado = 0;
            printf("Digite o nome do item para remover: ");
            fgets(nomeRemover, sizeof(nomeRemover), stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            for (int i = 0; i < total; i++)
            {
                if (strcmp(mochila[i].nome, nomeRemover) == 0)
                {
                    for (int j = i; j < total - 1; j++)
                        mochila[j] = mochila[j + 1];
                    total--;
                    encontrado = 1;
                    printf("Item removido!\n");
                    break;
                }
            }
            if (!encontrado)
                printf("Item não encontrado.\n");
            break;
        }

        case 3:
            if (total == 0)
                printf("A mochila está vazia.\n");
            else
            {
                printf("\n%-20s %-15s %-10s\n", "Nome", "Tipo", "Qtd");
                printf("-------------------------------------------\n");
                for (int i = 0; i < total; i++)
                    printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            }
            break;

        case 4:
        {
            char nomeBusca[50];
            int encontrado = 0;
            printf("Digite o nome do item para buscar: ");
            fgets(nomeBusca, sizeof(nomeBusca), stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

            for (int i = 0; i < total; i++)
            {
                if (strcmp(mochila[i].nome, nomeBusca) == 0)
                {
                    printf("\nItem encontrado!\n");
                    printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                           mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado)
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
