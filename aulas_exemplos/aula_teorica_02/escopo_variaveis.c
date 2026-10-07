/* Demonstracao do material suplementar de 02_Teoria.pdf, paginas 51-53.
 * Adaptacoes: main(void), funB(void) com retorno void e saida sem tabulacoes.
 * Globais e parametros com mesmo nome foram mantidos para estudar escopo.
 */
#include <stdio.h>

int x_global = 10;
int y = 20;

void funA(int x_local_a, int y);
void funB(void);
int funC(int x_local_c, int y);

int main(void)
{
    int x_local_main = 100;
    printf("1 - main: x_global = %d, x_local_main = %d, y = %d\n", x_global, x_local_main, y);

    funA(x_local_main, y);
    printf("3 - main: x_global = %d, x_local_main = %d, y = %d\n", x_global, x_local_main, y);

    funB();
    printf("5 - main: x_global = %d, x_local_main = %d, y = %d\n", x_global, x_local_main, y);

    x_local_main = funC(x_local_main, y);
    printf("7 - main: x_global = %d, x_local_main = %d, y = %d\n", x_global, x_local_main, y);
    return 0;
}

void funA(int x_local_a, int y)
{
    x_global = x_local_a + y;
    y = x_local_a + y;
    printf("2 - funA: x_global = %d, x_local_a = %d, y = %d\n", x_global, x_local_a, y);
}

void funB(void)
{
    x_global = 300;
    y = 400;
    printf("4 - funB: x_global = %d, y = %d\n", x_global, y);
}

int funC(int x_local_c, int y)
{
    x_global = x_local_c + y;
    y = x_local_c + y;
    printf("6 - funC: x_global = %d, x_local_c = %d, y = %d\n", x_global, x_local_c, y);
    return y;
}
