/* Adaptacao do material suplementar de 02_Teoria.pdf, paginas 43-45.
 * Busca a menor base inteira positiva b tal que b^k = n, com k >= 1.
 * As potencias sao construidas sem math.h e sem multiplicar alem de n.
 */
#include <stdio.h>

int menorBase(int n);

int main(void)
{
    int n;
    printf("Digite um inteiro positivo: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Entrada invalida: informe um inteiro positivo.\n");
        return 1;
    }

    printf("O menor b tal que b^k = %d e: %d\n", n, menorBase(n));
    return 0;
}

int menorBase(int n)
{
    if (n == 1) {
        return 1;
    }

    /* Para k >= 2, basta procurar bases com base^2 <= n. */
    for (int base = 2; base <= n / base; base++) {
        int resultado = base;
        while (resultado <= n / base) {
            resultado *= base;
            if (resultado == n) {
                return base;
            }
        }
    }

    return n; /* Caso restante: n^1 = n. */
}
