/* Demonstracao de 02_Teoria.pdf, paginas 35-36.
 * Correcao: F(0) = 0 e F(1) = 1, conforme a formula do slide.
 * Adaptacoes: programa completo e limite 30 para conter o tempo de execucao.
 */
#include <stdio.h>

unsigned long fibonacci(int i);

int main(void)
{
    int i;
    printf("Digite um indice de 0 a 30: ");
    if (scanf("%d", &i) != 1 || i < 0 || i > 30) {
        fprintf(stderr, "Entrada invalida: informe um inteiro de 0 a 30.\n");
        return 1;
    }

    printf("F(%d) = %lu\n", i, fibonacci(i));
    return 0;
}

unsigned long fibonacci(int i)
{
    if (i < 2) {
        return (unsigned long) i;
    }
    return fibonacci(i - 1) + fibonacci(i - 2);
}
