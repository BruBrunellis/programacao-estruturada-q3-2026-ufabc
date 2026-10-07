/* Demonstracao do material suplementar de 02_Teoria.pdf, pagina 47.
 * Adaptacoes: main(void) e leitura validada de um long long nao negativo.
 * A funcao imprime os digitos; nao retorna um numero invertido.
 */
#include <stdio.h>

void imprimeInvertido(long long n);

int main(void)
{
    long long n;
    printf("Digite um inteiro nao negativo: ");
    if (scanf("%lld", &n) != 1 || n < 0) {
        fprintf(stderr, "Entrada invalida: informe um inteiro nao negativo.\n");
        return 1;
    }

    imprimeInvertido(n);
    return 0;
}

void imprimeInvertido(long long n)
{
    if (n < 10) {
        printf("%lld\n", n);
        return;
    }

    int digito = (int) (n % 10);
    printf("%d", digito);
    imprimeInvertido(n / 10);
}
