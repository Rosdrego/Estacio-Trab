#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5      // Sempre cheia
#define TAM_PILHA 3     // Capacidade máxima da reserva

// Estrutura de PEÇA
typedef struct {
    char nome;   // 'I', 'O', 'T', 'L'
    int id;      // identificador único
} Peca;

// Estrutura da FILA CIRCULAR
typedef struct {
    Peca itens[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Estrutura da PILHA
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Gerar peça automaticamente
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];
    p.id = id;
    return p;
}

// Inicializar fila
void inicializarFila(Fila *f, int *contadorID) {
    f->frente = 0;
    f->tras = -1;
    f->quantidade = 0;

    for (int i = 0; i < TAM_FILA; i++) {
        f->tras = (f->tras + 1) % TAM_FILA;
        f->itens[f->tras] = gerarPeca((*contadorID)++);
        f->quantidade++;
    }
}

// Inicializar pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// Mostrar estado do jogo
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n================== ESTADO ATUAL ==================\n");

    // Fila
    printf("Fila de peças:\n");
    int i = f->frente;
    for (int c = 0; c < f->quantidade; c++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");

    // Pilha
    printf("Pilha de reserva (Topo -> Base):\n");
    if (p->topo == -1) {
        printf("[VAZIA]\n");
    } else {
        for (int j = p->topo; j >= 0; j--) {
            printf("[%c %d] ", p->itens[j].nome, p->itens[j].id);
        }
        printf("\n");
    }

    printf("=================================================\n");
}

// Remover peça da FILA (dequeue)
Peca jogarPeca(Fila *f) {
    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}


// -----------------------------
// Adicionar peça ao fim da FILA (enqueue)
// -----------------------------
void inserirNaFila(Fila *f, Peca p) {
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->quantidade++;
}

// Empilhar peça (push)
void reservarPeca(Pilha *p, Peca x) {
    p->topo++;
    p->itens[p->topo] = x;
}

// Desempilhar peça (pop)
Peca usarPecaReservada(Pilha *p) {
    return p->itens[p->topo--];
}

// PROGRAMA PRINCIPAL
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

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: { // JOGAR PEÇA
                Peca jogada = jogarPeca(&fila);
                printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);

                // Repõe nova peça na fila
                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 2: { // RESERVAR PEÇA
                if (pilha.topo == TAM_PILHA - 1) {
                    printf("\nA pilha de reserva está cheia! Não é possível reservar.\n");
                    break;
                }

                Peca reservada = jogarPeca(&fila);
                reservarPeca(&pilha, reservada);
                printf("\nPeça reservada: [%c %d]\n", reservada.nome, reservada.id);

                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 3: { // USAR PEÇA RESERVADA
                if (pilha.topo == -1) {
                    printf("\nNão há peças reservadas!\n");
                    break;
                }

                Peca usada = usarPecaReservada(&pilha);
                printf("\nPeça da reserva usada: [%c %d]\n", usada.nome, usada.id);

                inserirNaFila(&fila, gerarPeca(contadorID++));
                break;
            }

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
