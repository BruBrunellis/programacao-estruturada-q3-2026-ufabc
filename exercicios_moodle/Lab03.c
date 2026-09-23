/*Crie um programa que leia um número inteiro positivo e imprima o número com a posição dos digitos invertidos.
Entrada	Saída
1234	4321
5656	6565
1000	0001
*/

#include <stdio.h>

int main(void)
{
    int num, digito;

    scanf("%d", &num);

    while (num > 0){
        digito = num % 10;
        printf("%d", digito);
        num /= 10;
    }

    return 0;
}
