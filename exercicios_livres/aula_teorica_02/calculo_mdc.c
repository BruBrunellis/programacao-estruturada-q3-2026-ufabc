/*
Enunciado: escreva a função mdc, que retorna o máximo divisor comum de dois inteiros: o maior inteiro que divide ambos sem deixar resto. Use o algoritmo de Euclides apresentado pelo professor:

mdc(a, b) = a,                  se b = 0
mdc(a, b) = mdc(b, a mod b),     se b != 0

Convenção para praticar: inteiros não negativos, com pelo menos um positivo. O enunciado não define o tratamento de negativos; rejeite (0, 0) nesta versão.

Dicas: teste o caso base antes de calcular o resto, pois % 0 é inválido. Rastreie como a chamada troca os argumentos e reduz o segundo até zero.

a	b	MDC
18	12	6
11	7	1
12	18	6
8	8	8
9	0	9
0	9	9

*/


#include <stdio.h>

int mdc(int a, int b);

int main(void){

    int a, b;

    scanf("%d", &a);
    scanf("%d", &b);

    int resultado = mdc(a, b);

    printf("%d", resultado);

    return 0;
}

int mdc(int a, int b){

    if(b == 0){return a;}

    return mdc(b, (a % b));

}

