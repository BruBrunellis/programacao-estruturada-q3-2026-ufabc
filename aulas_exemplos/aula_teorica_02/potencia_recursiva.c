/* Demonstracao do material suplementar de 02_Teoria.pdf, pagina 46.
 * Adaptacoes: entrada validada, base entre -10 e 10, expoente entre 0 e 18.
 * Esses limites evitam estouro de long long. Adota-se power(0, 0) = 1.
 */
#include <stdio.h>

long long power(int base, int expoente);

int main(void)
{
    int base, expoente;
    printf("Digite a base (-10 a 10) e o expoente (0 a 18): ");
    if (scanf("%d %d", &base, &expoente) != 2 ||
        base < -10 || base > 10 || expoente < 0 || expoente > 18) {
        fprintf(stderr, "Entrada invalida: base de -10 a 10 e expoente de 0 a 18.\n");
        return 1;
    }

    printf("%d^%d = %lld\n", base, expoente, power(base, expoente));
    return 0;
}

long long power(int base, int expoente)
{
    if (expoente == 0) {
        return 1;
    }
    return base * power(base, expoente - 1);
}
