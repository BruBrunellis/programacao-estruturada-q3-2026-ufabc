/*
Laboratório 02 - Modularização
L02_04 - Tetração Usando Recursão

A tetração é a repetição da exponenciação. Na notação ^n(x), x aparece
n vezes em uma torre de potências, avaliada de cima para baixo:

    ^3(2) = 2^(2^2) = 2^4 = 16
    ^4(2) = 2^(2^(2^2)) = 2^16 = 65536

Escreva um programa que implemente a função recursiva em C tetracao
para calcular ^n(x), com x real positivo e n inteiro não negativo.

Assinatura da função:
    long double tetracao(double x, int n);

Dicas do enunciado:
    - Casos base: ^0(x) = 1 e ^1(x) = x.
    - Para n > 1, ^n(x) = x^(^(n-1)(x)); calcule o expoente com uma
      chamada recursiva à função tetracao.
    - Os resultados crescem muito rapidamente. Para x = 2 e n = 5,
      o resultado é 2^65536, com mais de 19.000 dígitos. Nos testes,
      assuma que x e n produzirão um resultado que cabe em long double.
    - O enunciado pede formatação com 8 dígitos e sem zeros adicionais
      à direita; sugere os formatos %.8g para double e %.8Lg para
      long double (por exemplo, 2.24000000 passa a 2.24).

Exemplos:
    Entrada: 2.0 3
    Saída:   ^3(2) = 16

    Entrada: 2.0 2
    Saída:   ^2(2) = 4

    Entrada: 3.0 2
    Saída:   ^2(3) = 27
*/

#define __USE_MINGW_ANSI_STDIO 1
#include <stdio.h>
#include <math.h>

long double tetracao(double x, int n) {
    if (n == 0) {
        return 1.0; // Caso base: ^0(x) = 1
    } else if (n == 1) {
        return x; // Caso base: ^1(x) = x
    } else {
        long double expoente = tetracao(x, n - 1); // Chamada recursiva para calcular ^(n-1)(x)
        return powl(x, expoente); // Calcula x^(^(n-1)(x))
    }
}

int main() {
    double x;
    int n;

    // Lê os valores de x e n
    scanf("%lf", &x);
    scanf("%d", &n);

    // Calcula a tetração e imprime o resultado com 8 dígitos significativos
    long double resultado = tetracao(x, n);
    printf("^%d(%.1f) = %.8Lg\n", n, x, resultado);

    return 0;
}
