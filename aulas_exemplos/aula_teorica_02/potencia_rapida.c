/* Demonstracao do material suplementar de 02_Teoria.pdf, pagina 54.
 * Correcao: no expoente impar, retornar aux * aux * base (nao aux^3).
 * Adaptacoes: long long, entrada validada e os mesmos limites da potencia
 * linear: base de -10 a 10, expoente de 0 a 18; power(0, 0) = 1.
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

    long long aux = power(base, expoente / 2);
    if (expoente % 2 == 0) {
        return aux * aux;
    }
    return aux * aux * base;
}
