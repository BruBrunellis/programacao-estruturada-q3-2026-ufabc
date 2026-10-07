/* Demonstracao de 02_Teoria.pdf, paginas 33-34.
 * Adaptacoes: programa completo, entrada de 0 a 20 e unsigned long long
 * para representar os resultados desse intervalo sem estouro.
 */
#include <stdio.h>

unsigned long long fatorial(int n);

int main(void)
{
    int n;
    printf("Digite um inteiro de 0 a 20: ");
    if (scanf("%d", &n) != 1 || n < 0 || n > 20) {
        fprintf(stderr, "Entrada invalida: informe um inteiro de 0 a 20.\n");
        return 1;
    }

    printf("%d! = %llu\n", n, fatorial(n));
    return 0;
}

unsigned long long fatorial(int n)
{
    if (n <= 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}
