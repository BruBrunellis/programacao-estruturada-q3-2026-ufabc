/*Crie um programa que receba um numero inteiro positivo
e informe quantos algarismos 7 existem.
Ex: O número 7657 tem 2 algarismos 7.
*/

#include <stdio.h>

int main(void)
{
    int numero, cont7 = 0, digito = 0;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &numero);

    int numero_salvo = numero;

    while(numero > 0)
    {
        digito = numero % 10;
        numero = numero / 10;

        if (digito == 7)
            cont7++;
    }
    printf("O numero %d possui %d algarismos 7\n", numero_salvo, cont7);
    return 0;
}
