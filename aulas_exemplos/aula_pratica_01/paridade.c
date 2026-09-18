/* Demonstracao de 01_PRATICA.pdf, paginas 6 e 12.
 * Adaptacoes: main(void), validacao da entrada e laco sem incremento
 * alem de INT_MAX. O resultado para entradas positivas e o dos slides.
 */
#include <stdio.h>

int main(void)
{
    int N, i;

    printf("Digite um numero inteiro positivo: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        fprintf(stderr, "Entrada invalida: informe um inteiro positivo.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        int numero = i + 1;
        if (numero % 2 == 0) {
            printf("%d eh par\n", numero);
        } else {
            printf("%d eh impar\n", numero);
        }
    }

    return 0;
}
