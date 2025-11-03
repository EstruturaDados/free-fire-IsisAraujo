#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura que representa um item da mochila
struct Item
{
    char nome[50];
    char tipo[30];
    int quantidade;
};

int main()
{
    struct Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do
    {
        printf("\n=== MENU DO INVENTÁRIO ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch (opcao)
        {
        case 1: // Adicionar item
            if (total < MAX_ITENS)
            {
                printf("Digite o nome do item: ");
                fgets(mochila[total].nome, sizeof(mochila[total].nome), stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                printf("Digite o tipo do item: ");
                fgets(mochila[total].tipo, sizeof(mochila[total].tipo), stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                printf("Digite a quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                getchar();

                total++;
                printf("Item adicionado com sucesso!\n");
            }
            else
            {
                printf("A mochila está cheia!\n");
            }
            break;

        case 2:
        { // Remover item
            char nomeRemover[50];
            int encontrado = 0;

            printf("Digite o nome do item que deseja remover: ");
            fgets(nomeRemover, sizeof(nomeRemover), stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

            for (int i = 0; i < total; i++)
            {
                if (strcmp(mochila[i].nome, nomeRemover) == 0)
                {
                    for (int j = i; j < total - 1; j++)
                    {
                        mochila[j] = mochila[j + 1];
                    }
                    total--;
                    encontrado = 1;
                    printf("Item removido com sucesso!\n");
                    break;
                }
            }

            if (!encontrado)
                printf("Item não encontrado!\n");
            break;
        }

        case 3: // Listar itens
            if (total == 0)
            {
                printf("A mochila está vazia.\n");
            }
            else
            {
                printf("\n=== ITENS NA MOCHILA ===\n");
                printf("%-20s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
                printf("---------------------------------------------\n");
                for (int i = 0; i < total; i++)
                {
                    printf("%-20s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                }
            }
            break;
        }
    } while (opcao != 0);

    printf("Saindo do inventário...\n");
    return 0;
}
