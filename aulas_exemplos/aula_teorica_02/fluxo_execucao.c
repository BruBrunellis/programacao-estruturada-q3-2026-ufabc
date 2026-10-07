/* Demonstracao de 02_Teoria.pdf, paginas 14-30.
 * Adaptacoes: prototipos, main(void) e impressao do resultado.
 * Use o depurador para acompanhar main -> f2 -> f1 -> f2 -> main.
 */
#include <stdio.h>

int f1(int a, int b);
int f2(int a, int b);

int main(void)
{
    int x = f2(2, 3);
    printf("x = %d\n", x);
    return 0;
}

int f1(int a, int b)
{
    int c = a - b;
    return a + b + c;
}

int f2(int a, int b)
{
    int c = f1(b, a);
    return b + c - a;
}
