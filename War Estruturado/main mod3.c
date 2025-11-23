#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ======================== FUNÇÕES DE MISSÃO ======================== */

// Sorteia missão para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Mostra missão apenas no início
void exibirMissao(char* missao) {
    printf("\n=== SUA MISSAO ===\n");
    printf("%s\n\n", missao);
}

// Verifica se o jogador cumpriu sua missão
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Missão 1: Conquistar 2 territórios azuis
    if (strstr(missao, "2 territorios azuis") != NULL) {
        int count = 0;
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "azul") == 0)
                count++;
        return (count >= 2);
    }

    // Missão 2: Ter um território com 10 tropas
    if (strstr(missao, "10 tropas") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (mapa[i].tropas >= 10)
                return 1;
    }

    // Missão 3: Conquistar qualquer território vermelho
    if (strstr(missao, "conquistar um territorio vermelho") != NULL) {
        for (int i = 0; i < tamanho; i++)
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0;  // ainda existe vermelho
        return 1;          // nenhum vermelho = missão cumprida
    }

    return 0;
}

/* ======================== FUNÇÕES DO MAPA ======================== */

void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito (azul = voce): ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(Territorio* mapa, int qtd) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

/* ======================== FUNÇÃO DE ATAQUE ======================== */

// Simula ataque do jogador (cor azul) contra território de outra cor
void atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n===== ATAQUE =====\n");
    printf("%s (azul) ATACA %s (%s)\n",
           atacante->nome, defensor->nome, defensor->cor);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado atacante: %d\n", dadoA);
    printf("Dado defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("Ataque bem-sucedido! Territorio conquistado!\n");
        strcpy(defensor->cor, "azul");
        defensor->tropas /= 2;
        if (defensor->tropas == 0) defensor->tropas = 1;
    } else {
        printf("Defensor resistiu! Voce perdeu 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/* ======================== LIBERAR MEMÓRIA ======================== */

void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

/* ======================== MAIN ======================== */

int main() {
    srand(time(NULL));

    // MISSÕES
    char* missoes[] = {
        "Conquistar 2 territorios azuis",
        "Possuir um territorio com pelo menos 10 tropas",
        "conquistar um territorio vermelho"
    };
    int totalMissoes = 3;

    // Aloca missão dinamicamente
    char* missaoJog = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJog, missoes, totalMissoes);

    // Mostra missão
    exibirMissao(missaoJog);

    // Alocar territórios
    int qtd;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &qtd);

    Territorio* mapa = (Territorio*) malloc(qtd * sizeof(Territorio));
    cadastrarTerritorios(mapa, qtd);

    int opcao;

    // Loop principal
    while (1) {

        printf("\n===== MENU =====\n");
        printf("1 - Exibir mapa\n");
        printf("2 - Atacar territorio inimigo\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirMapa(mapa, qtd);
        }

        else if (opcao == 2) {
            int a, d;

            exibirMapa(mapa, qtd);

            printf("\nSelecione seu territorio atacante: ");
            scanf("%d", &a);

            printf("Selecione um territorio inimigo: ");
            scanf("%d", &d);

            a--; d--;

            if (strcmp(mapa[a].cor, "azul") != 0) {
                printf("Esse territorio nao e seu!\n");
                continue;
            }

            if (strcmp(mapa[d].cor, "azul") == 0) {
                printf("Voce nao pode atacar seus proprios territorios!\n");
                continue;
            }

            atacar(&mapa[a], &mapa[d]);

            // Verifica missão silenciosamente
            if (verificarMissao(missaoJog, mapa, qtd)) {
                printf("\n===== MISSAO CUMPRIDA! VOCE VENCEU! =====\n");
                break;
            }
        }

        else if (opcao == 3) {
            break;
        }
    }

    liberarMemoria(mapa, missaoJog);

    printf("\nMemoria liberada. Fim do jogo.\n");
    return 0;
}
