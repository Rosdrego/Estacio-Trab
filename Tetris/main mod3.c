#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// ----------------------------------------------------
// Estrutura da peça
// ----------------------------------------------------
typedef struct {
    char nome;   // 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;


// ----------------------------------------------------
// Fila circular
// ----------------------------------------------------
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;


// ----------------------------------------------------
// Pilha (topo sempre cresce)
// ----------------------------------------------------
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;


// ----------------------------------------------------
// Gera peça automaticamente
// ----------------------------------------------------
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}


// ----------------------------------------------------
// Inicializa fila e pilha
// ----------------------------------------------------
void inicializarFila(Fila *f, int *id) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca((*id)++);
        f->quantidade++;
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}


// ----------------------------------------------------
// Mostrar estado atual
// ----------------------------------------------------
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n==================== ESTADO ATUAL ====================\n");

    // Fila
    printf("Fila de peças: ");
    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    // Pilha
    printf("Pilha de reserva (Topo -> Base): ");
    if (p->topo == -1) {
        printf("[VAZIA]");
    } else {
        for (int j = p->topo; j >= 0; j--) {
            printf("[%c %d] ", p->itens[j].nome, p->itens[j].id);
        }
    }
    printf("\n======================================================\n");
}


// ----------------------------------------------------
// Operações da FILA
// ----------------------------------------------------
Peca removerDaFila(Fila *f) {
    Peca p = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;
    return p;
}

void inserirNaFila(Fila *f, Peca p) {
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;
}


// ----------------------------------------------------
// Operações da PILHA
// ----------------------------------------------------
void empilhar(Pilha *p, Peca x) {
    p->topo++;
    p->itens[p->topo] = x;
}

Peca desempilhar(Pilha *p) {
    return p->itens[p->topo--];
}


// ----------------------------------------------------
// Troca simples: frente da fila ↔ topo da pilha
// ----------------------------------------------------
void trocarSimples(Fila *f, Pilha *p) {
    Peca temp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = temp;
}


// ----------------------------------------------------
// Troca múltipla: 3 primeiros da fila ↔ 3 da pilha
// ----------------------------------------------------
void trocarMultiplas(Fila *f, Pilha *p) {
    int idxFila = f->frente;

    for (int i = 0; i < 3; i++) {
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;

        idxFila = (idxFila + 1) % TAM_FILA;
    }
}


// ----------------------------------------------------
// Programa principal
// ----------------------------------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    int contadorID = 0;
    int opcao;

    inicializarFila(&fila, &contadorID);
    inicializarPilha(&pilha);

    do {
        mostrarEstado(&fila, &pilha);

        printf("\nAções disponíveis:\n");
        printf("1 – Jogar peça da fila\n");
        printf("2 – Reservar peça (fila → pilha)\n");
        printf("3 – Usar peça reservada (pilha → fora)\n");
        printf("4 – Trocar peça da frente da fila com topo da pilha\n");
        printf("5 – Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 – Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: { // Jogar peça
                Peca jogada = removerDaFila(&fila);
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 2: { // Reservar peça
                if (pilha.topo == TAM_PILHA - 1) {
                    printf("\nA pilha está cheia!\n");
                    break;
                }
                Peca reservada = removerDaFila(&fila);
                empilhar(&pilha, reservada);
                printf("\nPeça reservada: [%c %d]\n", reservada.nome, reservada.id);
                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 3: { // Usar peça reservada
                if (pilha.topo == -1) {
                    printf("\nA pilha está vazia!\n");
                    break;
                }
                Peca usada = desempilhar(&pilha);
                printf("\nPeça da reserva usada: [%c %d]\n", usada.nome, usada.id);
                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 4: { // Troca simples
                if (pilha.topo == -1) {
                    printf("\nNão há peça na pilha para trocar!\n");
                    break;
                }
                trocarSimples(&fila, &pilha);
                printf("\nTroca simples realizada!\n");
                break;
            }

            case 5: { // Troca múltipla
                if (pilha.topo < 2) {
                    printf("\nA pilha não tem 3 peças para trocar!\n");
                    break;
                }
                trocarMultiplas(&fila, &pilha);
                printf("\nTroca múltipla realizada!\n");
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
