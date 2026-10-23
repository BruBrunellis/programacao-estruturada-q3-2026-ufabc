/*
Laboratório 04 - Alocação Dinâmica
L04_01 - Conversão de Bases

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87372
Consultado em 22/10/2026. Formatação normalizada para comentário em C.

Conversão de Binário para Octal e Hexadecimal

Implemente um programa em C que leia uma string de tamanho n representando
um número binário positivo, realize a conversão direta para octal e para
hexadecimal, e exiba os resultados.

Requisitos:
    - Entrada: o tamanho n da string e a string contendo apenas os
      caracteres '0' e '1' (sem prefixos e sem espaços).
    - Armazenamento: manter os dígitos binários em um vetor
      (char *binario ou char binario[]).
    - Conversões necessárias:
        - Binário -> Octal.
        - Binário -> Hexadecimal.
    - Saída: imprimir o valor em octal e em hexadecimal
      (A-F em maiúsculas).
    - Eficiência: realizar conversões diretas por agrupamento de bits;
      não converter para decimal como etapa intermediária.
    - Memória: liberar a string binária após a conversão e impressão
      dos resultados.

Assinatura das funções:
    char *bin_to_oct(char binario[])
        Retorna uma nova string com o valor convertido para octal.

    char *bin_to_hex(char binario[])
        Retorna uma nova string com o valor convertido para hexadecimal.
        OBS: usar letras maiúsculas (A-F).

Conversão:
    - Octal: cada dígito octal corresponde a 3 bits binários.
    - Hexadecimal: cada dígito hexadecimal corresponde a 4 bits binários.

Dicas do enunciado:
    - Lembre-se do terminador nulo '\0' nas strings.
    - Garanta a liberação de toda memória alocada dinamicamente.
    - Para ler a string na próxima linha após ler n, utilize "\n":
        scanf("%d\n", &n);

Exemplos de entrada e saída:
As anotações (n=1), (n=6), (n=8) e (n=13) que acompanham a primeira
linha no Moodle indicam o tamanho, não fazem parte dos dados de entrada.

    Exemplo 1 - Entrada:
        1
        1
    Saída:
        oct: 1
        hex: 1

    Exemplo 2 - Entrada:
        6
        101101
    Saída:
        oct: 55
        hex: 2D

    Exemplo 3 - Entrada:
        8
        11110000
    Saída:
        oct: 360
        hex: F0

    Exemplo 4 - Entrada:
        13
        1000000000001
    Saída:
        oct: 10001
        hex: 1001
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *converter(char binario[], size_t bits_por_grupo) {
    const char digitos[] = "0123456789ABCDEF";
    size_t inicio = 0;
    size_t tamanho = strlen(binario);

    // Zeros a esquerda nao alteram o valor; o zero conserva um digito.
    while (inicio + 1 < tamanho && binario[inicio] == '0') {
        inicio++;
    }
    tamanho -= inicio;
    size_t grupos = tamanho / bits_por_grupo;
    if (tamanho % bits_por_grupo != 0) {
        grupos++;
    }

    char *resultado = malloc(grupos + 1);
    if (resultado == NULL) {
        return NULL;
    }

    // O primeiro grupo pode ser menor: os grupos se alinham pela direita.
    size_t largura = tamanho % bits_por_grupo;
    if (largura == 0) {
        largura = bits_por_grupo;
    }
    for (size_t i = 0; i < grupos; i++) {
        unsigned int valor = 0;
        for (size_t j = 0; j < largura; j++) {
            valor = valor * 2 + (unsigned int)(binario[inicio++] - '0');
        }
        resultado[i] = digitos[valor];
        largura = bits_por_grupo;
    }
    resultado[grupos] = '\0';
    return resultado;
}

char *bin_to_oct(char binario[]) {
    return converter(binario, 3);
}

char *bin_to_hex(char binario[]) {
    return converter(binario, 4);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }

    char *binario = malloc((size_t)n + 1);
    if (binario == NULL) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf(" %c", &binario[i]) != 1 ||
            (binario[i] != '0' && binario[i] != '1')) {
            free(binario);
            return 0;
        }
    }
    binario[n] = '\0';

    char *octal = bin_to_oct(binario);
    char *hexadecimal = bin_to_hex(binario);
    if (octal == NULL || hexadecimal == NULL) {
        free(octal);
        free(hexadecimal);
        free(binario);
        return 1;
    }

    printf("oct: %s\nhex: %s\n", octal, hexadecimal);
    free(octal);
    free(hexadecimal);
    free(binario);
    return 0;
}

