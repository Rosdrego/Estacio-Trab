#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ----------- FUNÇÕES -----------
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

// ----------- MAIN -----------
int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);

    int opcao;
    do {
        printf("\n====== MENU ======\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar territorio\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirTerritorios(mapa, n);
        }

        else if (opcao == 2) {
            int iAtacante, iDefensor;

            exibirTerritorios(mapa, n);

            printf("\nEscolha o indice do território atacante: ");
            scanf("%d", &iAtacante);

            printf("Escolha o indice do território defensor: ");
            scanf("%d", &iDefensor);

            // validações
            if (iAtacante < 0 || iAtacante >= n ||
                iDefensor < 0 || iDefensor >= n) {
                printf("Indices invalidos!\n");
                continue;
            }

            if (strcmp(mapa[iAtacante].cor, mapa[iDefensor].cor) == 0) {
                printf("Nao pode atacar um territorio da mesma cor!\n");
                continue;
            }

            if (mapa[iAtacante].tropas <= 1) {
                printf("O atacante precisa de pelo menos 2 tropas!\n");
                continue;
            }

            atacar(&mapa[iAtacante], &mapa[iDefensor]);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// ----------- IMPLEMENTAÇÕES -----------

void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\nCadastro dos territorios:\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Território %d ---\n", i);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito (Ex: azul, vermelho, neutro): ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n--- TERRITORIOS ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função de ataque com rand()
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n--- ATAQUE ENTRE %s -> %s ---\n",
           atacante->nome, defensor->nome);

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("Dado atacante: %d\n", dadoAtq);
    printf("Dado defensor: %d\n", dadoDef);

    // Lógica de vitória
    if (dadoAtq > dadoDef) {
        printf(">> O atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas;

        printf("O territorio %s agora pertence ao atacante!\n", defensor->nome);

    } else {
        printf(">> O defensor resistiu!\n");
        atacante->tropas--;  
    }

    printf("Atualizacao:\n");
    printf("Atacante -> Tropas: %d\n", atacante->tropas);
    printf("Defensor -> Tropas: %d | Cor: %s\n", defensor->tropas, defensor->cor);
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso.\n");
}
