/*
Enunciado: escreva uma função recursiva power(base, expoente) que retorne base^expoente. Considere expoente inteiro maior ou igual a 1. Exemplo: power(3, 4) = 3 * 3 * 3 * 3.

Dica do professor: use base^expoente = base * base^(expoente - 1); a condição de término ocorre quando expoente == 1, pois base^1 = base.

Dicas adicionais:

Identifique o valor devolvido por cada chamada antes de fazer a multiplicação anterior.
Preserve a exigência de recursão; não substitua por um laço ou pow.
Para estes testes, use base inteira e limite os valores ao intervalo representável pelo tipo escolhido.
Aceitar expoente zero é uma extensão, não parte do domínio original.

Base	Expoente	Resultado
3	4	81
7	1	7
-2	3	-8
-2	4	16
0	2	0

*/

#include <stdio.h>

long long potencia(int base, int expoente);

int main(void){

    int base, expoente;

    scanf("%d", &base);
    scanf("%d", &expoente);

    long long resultado = potencia(base, expoente);

    printf("%d", resultado);

    return 0;
}

long long potencia(int base, int expoente){

    if(expoente == 0){return 1;}

    if(expoente == 1 || base == 1 || base == 0){return base;}

    long long resultado = base * potencia(base, expoente - 1);

    return resultado;
}
