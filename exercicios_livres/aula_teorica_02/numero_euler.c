/*Calculo do numero de Euler por n termos*/

#define _USE_MINGW_ANSI_STDIO 1
#include <stdio.h>

unsigned long long fatorial(int n);
double euler(int n);

int main(void){

    int n;

    printf("Digite o numero de termos: ");
    scanf("%d", &n);

    double e = euler(n);

    printf("O valor aproximado do numero de Euler com %d termos eh: %g\n", n, e);

    return 0;
}

unsigned long long fatorial(int n) {

    if (n <= 1)
        return 1;
    else
        return n * fatorial(n - 1);
}

double euler(int n) {

    double e = 1.0;

    for (int i = 1; i <= n; i++) {
        e += 1.0 / fatorial(i);
    }

    return e;
}
