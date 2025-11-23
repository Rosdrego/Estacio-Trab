#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 10

/*===========================================================
   STRUCTS DO SISTEMA
===========================================================*/

// Item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/*===========================================================
   VARIÁVEIS GLOBAIS PARA CONTAR COMPARAÇÕES
===========================================================*/

int comparacoesSeq = 0;
int comparacoesBin = 0;

/*===========================================================
   FUNÇÕES DO VETOR
===========================================================*/

// Inserir item no vetor
void inserirItemVetor(Item vet[], int *n) {
    if (*n >= TAM) {
        printf("\nMochila cheia!\n");
        return;
    }
    printf("\n--- Inserindo item no vetor ---\n");
    printf("Nome: ");
    scanf("%s", vet[*n].nome);
    printf("Tipo: ");
    scanf("%s", vet[*n].tipo);
    printf("Quantidade: ");
    scanf("%d", &vet[*n].quantidade);

    (*n)++;
}

// Remover item do vetor
void removerItemVetor(Item vet[], int *n) {
    char nome[30];
    printf("\nNome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < *n; i++) {
        if (strcmp(vet[i].nome, nome) == 0) {
            for (int j = i; j < *n - 1; j++)
                vet[j] = vet[j + 1];
            (*n)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

// Listar itens do vetor
void listarVetor(Item vet[], int n) {
    printf("\n--- Itens no vetor ---\n");
    for (int i = 0; i < n; i++) {
        printf("%s | %s | %d\n", vet[i].nome, vet[i].tipo, vet[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item vet[], int n, char nome[]) {
    comparacoesSeq = 0;
    for (int i = 0; i < n; i++) {
        comparacoesSeq++;
        if (strcmp(vet[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Ordenar vetor (Bubble Sort)
void ordenarVetor(Item vet[], int n) {
    Item tmp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
            }
        }
    }
    printf("\nVetor ordenado!\n");
}

// Busca binária no vetor
int buscarBinariaVetor(Item vet[], int n, char nome[]) {
    int ini = 0, fim = n - 1;
    comparacoesBin = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoesBin++;

        int cmp = strcmp(vet[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/*===========================================================
   FUNÇÕES DA LISTA ENCADEADA
===========================================================*/

// Inserir item na lista encadeada
void inserirItemLista(No** inicio) {
    No* novo = (No*)malloc(sizeof(No));

    printf("\n--- Inserindo item na lista ---\n");
    printf("Nome: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = *inicio;
    *inicio = novo;
}

// Remover item da lista encadeada
void removerItemLista(No** inicio) {
    char nome[30];
    printf("\nNome do item para remover: ");
    scanf("%s", nome);

    No *aux = *inicio, *ant = NULL;

    while (aux != NULL) {
        if (strcmp(aux->dados.nome, nome) == 0) {
            if (ant == NULL)
                *inicio = aux->proximo;
            else
                ant->proximo = aux->proximo;

            free(aux);
            printf("Item removido!\n");
            return;
        }
        ant = aux;
        aux = aux->proximo;
    }
    printf("Item não encontrado!\n");
}

// Listar itens da lista encadeada
void listarLista(No* inicio) {
    No* aux = inicio;
    printf("\n--- Itens na lista encadeada ---\n");
    while (aux != NULL) {
        printf("%s | %s | %d\n", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux = aux->proximo;
    }
}

// Busca sequencial na lista encadeada
No* buscarLista(No* inicio, char nome[]) {
    comparacoesSeq = 0;
    No* aux = inicio;

    while (aux != NULL) {
        comparacoesSeq++;
        if (strcmp(aux->dados.nome, nome) == 0)
            return aux;

        aux = aux->proximo;
    }
    return NULL;
}

/*===========================================================
   MENU PRINCIPAL
===========================================================*/

int main() {
    Item mochilaVet[TAM];
    int n = 0;

    No* lista = NULL;

    int escolha, op;
    char nomeBusca[30];

    do {
        printf("\n===== SISTEMA DE MOCHILA =====");
        printf("\n1 - Usar Mochila com Vetor");
        printf("\n2 - Usar Mochila com Lista Encadeada");
        printf("\n3 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &escolha);

        if (escolha == 1) {
            do {
                printf("\n===== MOCHILA VETOR =====");
                printf("\n1 - Inserir");
                printf("\n2 - Remover");
                printf("\n3 - Listar");
                printf("\n4 - Ordenar");
                printf("\n5 - Buscar Sequencial");
                printf("\n6 - Buscar Binária");
                printf("\n7 - Voltar");
                printf("\nEscolha: ");
                scanf("%d", &op);

                switch (op) {
                    case 1: inserirItemVetor(mochilaVet, &n); break;
                    case 2: removerItemVetor(mochilaVet, &n); break;
                    case 3: listarVetor(mochilaVet, n); break;
                    case 4: ordenarVetor(mochilaVet, n); break;
                    case 5:
                        printf("Nome para buscar: ");
                        scanf("%s", nomeBusca);
                        buscarSequencialVetor(mochilaVet, n, nomeBusca);
                        printf("Comparações: %d\n", comparacoesSeq);
                        break;
                    case 6:
                        printf("Nome para buscar: ");
                        scanf("%s", nomeBusca);
                        ordenarVetor(mochilaVet, n);
                        buscarBinariaVetor(mochilaVet, n, nomeBusca);
                        printf("Comparações busca binária: %d\n", comparacoesBin);
                        break;
                }

            } while (op != 7);
        }

        else if (escolha == 2) {
            do {
                printf("\n===== MOCHILA LISTA =====");
                printf("\n1 - Inserir");
                printf("\n2 - Remover");
                printf("\n3 - Listar");
                printf("\n4 - Buscar Sequencial");
                printf("\n5 - Voltar");
                printf("\nEscolha: ");
                scanf("%d", &op);

                switch (op) {
                    case 1: inserirItemLista(&lista); break;
                    case 2: removerItemLista(&lista); break;
                    case 3: listarLista(lista); break;
                    case 4:
                        printf("Nome para buscar: ");
                        scanf("%s", nomeBusca);
                        buscarLista(lista, nomeBusca);
                        printf("Comparações: %d\n", comparacoesSeq);
                        break;
                }

            } while (op != 5);
        }

    } while (escolha != 3);

    printf("\nEncerrando...\n");
    return 0;
}
