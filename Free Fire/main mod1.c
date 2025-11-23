#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACIDADE 10  

/*-----------------------------------------------------------
    STRUCT ITEM
-----------------------------------------------------------*/
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/*-----------------------------------------------------------
    FUNÇÃO PARA LISTAR ITENS
-----------------------------------------------------------*/
void listarItens(Item mochila[], int contador) {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", contador, CAPACIDADE);

    if (contador == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < contador; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

/*-----------------------------------------------------------
    FUNÇÃO PARA INSERIR ITEM
-----------------------------------------------------------*/
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= CAPACIDADE) {
        printf("\n Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");

    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo (arma, municao, cura, recurso, comida): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[*contador] = novo;
    (*contador)++;

    printf("\n Item cadastrado com sucesso!\n");
}

/*-----------------------------------------------------------
    FUNÇÃO PARA REMOVER ITEM PELO NOME
-----------------------------------------------------------*/
void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("\nA mochila esta vazia! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nNome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    int encontrado = -1;

    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\n Item nao encontrado!\n");
        return;
    }

    for (int i = encontrado; i < *contador - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*contador)--;

    printf("\n Item removido com sucesso!\n");
}

/*-----------------------------------------------------------
    FUNÇÃO DE BUSCA SEQUENCIAL
-----------------------------------------------------------*/
void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("\n Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\n Item nao encontrado!\n");
}

/*-----------------------------------------------------------
    PROGRAMA PRINCIPAL
-----------------------------------------------------------*/
int main() {

    Item mochila[CAPACIDADE];  
    int contador = 10;        

    Item itensIniciais[10] = {
        {"KitMedP", "cura", 1},
        {"KitMedG", "cura", 1},
        {"Agua", "comida", 2},
        {"ComidaLata", "comida", 3},
        {"Madeira", "recurso", 5},
        {"Pedra", "recurso", 8},
        {"Faca", "arma", 1},
        {"Pistola", "arma", 1},
        {"Muni9mm", "municao", 24},
        {"Bandagem", "cura", 4}
    };

    for (int i = 0; i < 10; i++) {
        mochila[i] = itensIniciais[i];
    }

    int opcao;

    do {
        printf("\n=========================\n");
        printf("   SISTEMA DE INVENTARIO\n");
        printf("=========================\n");
        printf("1. Inserir Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &contador);
                listarItens(mochila, contador);
                break;

            case 2:
                removerItem(mochila, &contador);
                listarItens(mochila, contador);
                break;

            case 3:
                listarItens(mochila, contador);
                break;

            case 4:
                buscarItem(mochila, contador);
                break;

            case 5:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\n⚠ Opcao inválida!\n");
        }

    } while (opcao != 5);

    return 0;
}
