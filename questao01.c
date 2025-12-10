#include <stdio.h>

int main(){
    
    int numero;

    printf("Digite um numero de valor real: ");
    scanf("%d", &numero);

    printf("O valor em hexadecial é: %X\n", numero);
    printf("O valor em octal é : %o\n", numero);

    return 0;

}