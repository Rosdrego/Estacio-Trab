#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

/* ======================================================
   STRUCT PRINCIPAL DO SISTEMA
=========================================================*/
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* ======================================================
   VARIÁVEIS GLOBAIS DE DESEMPENHO
=========================================================*/
long long comparacoes = 0;

/* ======================================================
   FUNÇÃO PARA MOSTRAR COMPONENTES
=========================================================*/
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s | %-15s | prioridade: %d\n",
               v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* ======================================================
   BUBBLE SORT → ORDENAR POR NOME
=========================================================*/
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    Componente temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

/* ======================================================
   INSERTION SORT → ORDENAR POR TIPO
=========================================================*/
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente atual = v[i];
        int j = i - 1;

        while (j >= 0 && strcmp(atual.tipo, v[j].tipo) < 0) {
            comparacoes++;
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = atual;
    }
}

/* ======================================================
   SELECTION SORT → ORDENAR POR PRIORIDADE
=========================================================*/
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }

        // troca
        if (min != i) {
            Componente temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
}

/* ======================================================
   BUSCA BINÁRIA → APENAS DEPOIS DO BUBBLE SORT
=========================================================*/
int buscaBinariaNome(Componente v[], int n, char chave[]) {
    comparacoes = 0;

    int ini = 0, fim = n - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(v[meio].nome, chave);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

/* ======================================================
   MEDIR TEMPO DE ALGORITMO
=========================================================*/
double medirTempo(void (*func)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    func(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/* ======================================================
   CADASTRO DOS COMPONENTES
=========================================================*/
int cadastrar(Componente v[]) {
    int n;
    printf("\nQuantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &n);
    getchar(); // limpar buffer

    if (n > MAX) n = MAX;

    for (int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i + 1);

        printf("Nome: ");
        fgets(v[i].nome, 30, stdin);
        v[i].nome[strcspn(v[i].nome, "\n")] = 0;

        printf("Tipo: ");
        fgets(v[i].tipo, 20, stdin);
        v[i].tipo[strcspn(v[i].tipo, "\n")] = 0;

        printf("Prioridade (1 a 10): ");
        scanf("%d", &v[i].prioridade);
        getchar();
    }

    return n;
}

/* ======================================================
   MENU PRINCIPAL
=========================================================*/
int main() {
    Componente comp[20];
    int n = 0;
    int opc;
    char chave[30];

    do {
        printf("\n========== MISSÃO FINAL: TORRE DE FUGA ==========");
        printf("\n1 - Cadastrar componentes");
        printf("\n2 - Ordenar por NOME (Bubble Sort)");
        printf("\n3 - Ordenar por TIPO (Insertion Sort)");
        printf("\n4 - Ordenar por PRIORIDADE (Selection Sort)");
        printf("\n5 - Buscar componente por NOME (Busca Binária)");
        printf("\n6 - Mostrar componentes");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &opc);
        getchar();

        switch (opc) {
            case 1:
                n = cadastrar(comp);
                break;

            case 2: {
                printf("\nORDENANDO POR NOME...\n");
                Componente temp[20];
                memcpy(temp, comp, sizeof(comp));

                double tempo = medirTempo(bubbleSortNome, temp, n);

                printf("Comparações: %lld\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);

                memcpy(comp, temp, sizeof(temp));
                mostrarComponentes(comp, n);
                break;
            }

            case 3: {
                printf("\nORDENANDO POR TIPO...\n");
                Componente temp[20];
                memcpy(temp, comp, sizeof(comp));

                double tempo = medirTempo(insertionSortTipo, temp, n);

                printf("Comparações: %lld\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);

                memcpy(comp, temp, sizeof(temp));
                mostrarComponentes(comp, n);
                break;
            }

            case 4: {
                printf("\nORDENANDO POR PRIORIDADE...\n");
                Componente temp[20];
                memcpy(temp, comp, sizeof(comp));

                double tempo = medirTempo(selectionSortPrioridade, temp, n);

                printf("Comparações: %lld\n", comparacoes);
                printf("Tempo: %.6f segundos\n", tempo);

                memcpy(comp, temp, sizeof(temp));
                mostrarComponentes(comp, n);
                break;
            }

            case 5: {
                printf("\nDigite o nome para buscar: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;

                printf("\n(É necessário ter ordenado por NOME antes!)\n");

                int pos = buscaBinariaNome(comp, n, chave);

                if (pos >= 0)
                    printf("\n✔ ENCONTRADO: %s | %s | prioridade %d\n",
                           comp[pos].nome, comp[pos].tipo, comp[pos].prioridade);
                else
                    printf("\n❌ Componente não encontrado.\n");

                printf("Comparações Busca Binária: %lld\n", comparacoes);
                break;
            }

            case 6:
                mostrarComponentes(comp, n);
                break;
        }

    } while (opc != 0);

    printf("\nMissão encerrada. Boa fuga, sobrevivente!\n");
    return 0;
}
