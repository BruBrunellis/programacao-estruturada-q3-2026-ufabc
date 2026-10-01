/* Demonstracao do material suplementar de 02_Teoria.pdf, pagina 48.
 * Adaptacoes: main(void), leitura de inteiros nao negativos e rejeicao
 * do par (0, 0), que nao possui maior divisor comum positivo.
 */
#include <stdio.h>

int mdc(int a, int b);

int main(void)
{
    int a, b;
    printf("Digite dois inteiros nao negativos (ao menos um positivo): ");
    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b < 0 || (a == 0 && b == 0)) {
        fprintf(stderr, "Entrada invalida: use inteiros nao negativos, nao ambos zero.\n");
        return 1;
    }

    printf("mdc(%d, %d) = %d\n", a, b, mdc(a, b));
    return 0;
}

int mdc(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return mdc(b, a % b);
}
