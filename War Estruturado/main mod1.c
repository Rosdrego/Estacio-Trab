#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    Territorio territorios[5];

    printf("=== Cadastro de Territorios ===\n\n");

    for (int i = 0; i < 5; i++) {

        printf("--- Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    printf("\n=== Territorios Cadastrados ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}