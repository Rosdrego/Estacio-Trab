#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5   // número fixo inicial de peças na fila

// STRUCT DA PEÇA

typedef struct {
    char nome;   // tipos: 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;

// FILA CIRCULAR

typedef struct {
    Peca itens[TAMANHO_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Função que gera uma peça automaticamente

Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    int r = rand() % 4;

    Peca nova;
    nova.nome = tipos[r];
    nova.id = id;
    return nova;
}

// Inicializa fila e preenche com peças iniciais

void inicializarFila(Fila *f, int *contadorID) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;

    for (int i = 0; i < TAMANHO_FILA; i++) {
        f->tras = (f->tras + 1) % TAMANHO_FILA;
        f->itens[f->tras] = gerarPeca((*contadorID)++);
        f->quantidade++;
    }
}

void mostrarFila(Fila *f) {
    printf("\nFila de peças:\n");

    if (f->quantidade == 0) {
        printf("[VAZIA]\n");
        return;
    }

    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

void enqueue(Fila *f, Peca p) {
    if (f->quantidade == TAMANHO_FILA) {
        printf("\nA fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->tras = (f->tras + 1) % TAMANHO_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;

    printf("\nPeça [%c %d] inserida com sucesso!\n", p.nome, p.id);
}

void dequeue(Fila *f) {
    if (f->quantidade == 0) {
        printf("\nA fila está vazia! Nada para jogar.\n");
        return;
    }

    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAMANHO_FILA;
    f->quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

// Programa principal
int main() {
    srand(time(NULL));

    Fila fila;
    int contadorID = 0;
    int opcao;

    inicializarFila(&fila, &contadorID);

    do {
        mostrarFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2: {
                Peca nova = gerarPeca(contadorID++);
                enqueue(&fila, nova);
                break;
            }

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
