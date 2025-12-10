#include <stdlib.h>
#include <string.h>

#define NOME_ARQUIVO "hardware.dat"
#define TOTAL_REGISTROS 100 // O arquivo deve ser inicializado para 100 registros vazios 

struct ferramenta {
    int numRegistro; // Será o número de identificação da ferramenta 
    char nome[30];
    int quantidade;
    float custo;
};

void inicializarArquivo() {
    FILE *fPtr;
    struct ferramenta ferramentaVazia = {0, "", 0, 0.0};

    if ((fPtr = fopen(NOME_ARQUIVO, "wb")) == NULL) {
        printf("Erro ao abrir/criar o arquivo " NOME_ARQUIVO ".\n");
        exit(1);
    }

    for (int i = 1; i <= TOTAL_REGISTROS; i++) {
        fwrite(&ferramentaVazia, sizeof(struct ferramenta), 1, fPtr);
    }

    fclose(fPtr);
    printf("Arquivo " NOME_ARQUIVO " inicializado com %d registros vazios.\n", TOTAL_REGISTROS);
}

void inserirRegistro(FILE *fPtr) {
    struct ferramenta f;
    int reg;

    printf("\n--- Inserir Ferramenta ---\n");
    printf("Digite o número do registro (1 a %d): ", TOTAL_REGISTROS);
    scanf("%d", &reg);

    if (reg < 1 || reg > TOTAL_REGISTROS) {
        printf("Número de registro inválido.\n");
        return;
    }

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);

    fread(&f, sizeof(struct ferramenta), 1, fPtr);

    if (f.numRegistro != 0) {
        printf("O registro %d já contém dados ('%s').\n", reg, f.nome);
        return;
    }

    f.numRegistro = reg;
    printf("Nome da ferramenta: ");
    scanf("%s", f.nome);
    printf("Quantidade: ");
    scanf("%d", &f.quantidade);
    printf("Custo: ");
    scanf("%f", &f.custo);

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);
    fwrite(&f, sizeof(struct ferramenta), 1, fPtr);
    printf("Ferramenta inserida no registro %d.\n", reg);
}

void listarRegistros(FILE *fPtr) {
    struct ferramenta f;

    printf("\n--- Inventário de Ferramentas ---\n");
    printf("%-10s%-30s%-10s%s\n", "Registro", "Nome", "Quant.", "Custo");
    printf("----------------------------------------------------------------\n");

    fseek(fPtr, 0, SEEK_SET);

    for (int i = 1; i <= TOTAL_REGISTROS; i++) {
        fread(&f, sizeof(struct ferramenta), 1, fPtr);
        if (f.numRegistro != 0) { // Exibe apenas registros preenchidos
            printf("%-10d%-30s%-10d%.2f\n", f.numRegistro, f.nome, f.quantidade, f.custo);
        }
    }
}

void excluirRegistro(FILE *fPtr) {
    struct ferramenta f;
    struct ferramenta ferramentaVazia = {0, "", 0, 0.0};
    int reg;

    printf("\n--- Excluir Ferramenta ---\n");
    printf("Digite o número do registro a ser excluído (1 a %d): ", TOTAL_REGISTROS);
    scanf("%d", &reg);

    if (reg < 1 || reg > TOTAL_REGISTROS) {
        printf("Número de registro inválido.\n");
        return;
    }

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);
    fread(&f, sizeof(struct ferramenta), 1, fPtr);

    if (f.numRegistro == 0) {
        printf("O registro %d já está vazio.\n", reg);
        return;
    }

    printf("Excluindo: Registro %d, Nome: %s\n", f.numRegistro, f.nome);

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);
    fwrite(&ferramentaVazia, sizeof(struct ferramenta), 1, fPtr);
    printf("Registro %d excluído com sucesso.\n", reg);
}

void atualizarRegistro(FILE *fPtr) {
    struct ferramenta f;
    int reg;

    printf("\n--- Atualizar Ferramenta ---\n");
    printf("Digite o número do registro a ser atualizado (1 a %d): ", TOTAL_REGISTROS);
    scanf("%d", &reg);

    if (reg < 1 || reg > TOTAL_REGISTROS) {
        printf("Número de registro inválido.\n");
        return;
    }

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);
    fread(&f, sizeof(struct ferramenta), 1, fPtr);

    if (f.numRegistro == 0) {
        printf("O registro %d está vazio. Use a opção 'Inserir' para preenchê-lo.\n", reg);
        return;
    }

    printf("Registro atual: %d | Nome: %s | Quantidade: %d | Custo: %.2f\n",
           f.numRegistro, f.nome, f.quantidade, f.custo);

    printf("Novo Nome (deixe o anterior: %s): ", f.nome);
    scanf("%s", f.nome); // Simplificado para um token

    printf("Nova Quantidade (anterior: %d): ", f.quantidade);
    scanf("%d", &f.quantidade);

    printf("Novo Custo (anterior: %.2f): ", f.custo);
    scanf("%f", &f.custo);

    fseek(fPtr, (long)(reg - 1) * sizeof(struct ferramenta), SEEK_SET);
    fwrite(&f, sizeof(struct ferramenta), 1, fPtr);
    printf("Registro %d atualizado com sucesso.\n", reg);
}

int main() {
    FILE *fPtr;
    int escolha;

    inicializarArquivo();

    if ((fPtr = fopen(NOME_ARQUIVO, "rb+")) == NULL) {
        printf("Erro ao abrir/acessar o arquivo " NOME_ARQUIVO ".\n");
        return 1;
    }

    do {
        printf("\n\n--- MENU DE INVENTÁRIO ---\n");
        printf("1. Inserir Ferramenta\n");
        printf("2. Listar Todas as Ferramentas\n");
        printf("3. Atualizar Informação\n");
        printf("4. Excluir Registro\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirRegistro(fPtr);
                break;
            case 2:
                listarRegistros(fPtr);
                break;
            case 3:
                atualizarRegistro(fPtr);
                break;
            case 4:
                excluirRegistro(fPtr);
                break;
            case 5:
                printf("Saindo do programa. Arquivo " NOME_ARQUIVO " salvo.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 5);

    fclose(fPtr);
    return 0;
}
