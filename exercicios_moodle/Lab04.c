/*Implemente um programa que receba um número inteiro positivo n. O programa deve identificar e imprimir dois números primos:

o primo imediatamente anterior a n;

o primo imediatamente posterior n.

Entrada	Saída
7       5 11

10      7 11

Obs:  caso n não tenha primo anterior ou posterior, informar o usuário. Por exemplo: "Sem primo anterior". */


#include <stdio.h>

int Ehprimo(int num)
{
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;

    for(int i = 3; i * i <= num; i += 2){

        if (num % i == 0) return 0;
    }

    return 1;
}

int main(void)
{
    int num, primo_anterior, primo_posterior;
    scanf("%d", &num);

    primo_anterior = num - 1;
    primo_posterior = num + 1;

    while (primo_anterior >= 2 && !Ehprimo(primo_anterior)){
        primo_anterior--;
    }

    while(!Ehprimo(primo_posterior)){
        primo_posterior++;
    }

    if (primo_anterior < 2)
        printf("Sem primo anterior %d", primo_posterior);
    else
        printf("%d %d", primo_anterior, primo_posterior);

    return 0;
}
