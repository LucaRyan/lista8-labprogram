#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USUARIOS 3

struct usuario {
    char nome[50];
    int idade;
    float altura;
};

int main() {
    FILE *arquivo;
    struct usuario usuarios[MAX_USUARIOS];

    printf("--- Coleta de Dados dos Usuários ---\n");
    for (int i = 0; i < MAX_USUARIOS; i++) {
        printf("\nUsuário %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", usuarios[i].nome); // Assumindo nome simples sem espaços
        printf("Idade: ");
        scanf("%d", &usuarios[i].idade);
        printf("Altura (m): ");
        scanf("%f", &usuarios[i].altura);
    }

    arquivo = fopen("dados_usuarios.csv", "w"); // Abre para escrita (sobrescreve se existir)

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    fprintf(arquivo, "Nome,Idade,Altura(m)\n");

    for (int i = 0; i < MAX_USUARIOS; i++) {
        fprintf(arquivo, "%s,%d,%.2f\n",
                usuarios[i].nome,
                usuarios[i].idade,
                usuarios[i].altura);
    }

    fclose(arquivo);
    printf("\nDados gravados com sucesso em 'dados_usuarios.csv'\n");

    return 0;
}
