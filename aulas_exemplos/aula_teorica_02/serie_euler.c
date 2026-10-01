/* Demonstracao do material suplementar de 02_Teoria.pdf, paginas 41-42.
 * Adaptacoes: main(void), validacao de 1 a MAX_N e unsigned long para
 * o fatorial. O limite de 10 termos do slide foi preservado.
 */
#include <stdio.h>

#define MAX_N 10

unsigned long fatorial(int n);
double euler(int num_termos);

int main(void)
{
    int num_termos;
    printf("Digite o numero de termos (1 a %d): ", MAX_N);
    if (scanf("%d", &num_termos) != 1 || num_termos < 1 || num_termos > MAX_N) {
        fprintf(stderr, "Entrada invalida: informe de 1 a %d termos.\n", MAX_N);
        return 1;
    }

    printf("n = %d, e = %.10f\n", num_termos, euler(num_termos));
    return 0;
}

double euler(int num_termos)
{
    double e = 0.0;
    for (int n = 0; n < num_termos; n++) {
        e += 1.0 / fatorial(n);
    }
    return e;
}

unsigned long fatorial(int n)
{
    unsigned long resultado = 1;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}
