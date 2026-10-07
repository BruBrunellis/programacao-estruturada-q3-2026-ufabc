/* Demonstracao de 02_Teoria.pdf, paginas 7-8.
 * Adaptacoes: prototipo antes de main e main(void).
 */
#include <stdio.h>

int soma(int a, int b);

int main(void)
{
    int total = soma(8, 13);
    printf("%d\n", total);
    return 0;
}

int soma(int a, int b)
{
    int resultado = a + b;
    return resultado;
}
