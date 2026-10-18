/*Exercicio -
Crie um programa que converta um número da base 10 (decimal)
para a base 2 (binário) e exiba o resultado
*/

#include <stdio.h>
#include <limits.h>

int main(void)
{
    int numero;
    int binario[sizeof(int) * CHAR_BIT];
    int quantidade_digitos = 0;

    printf("Digite um numero inteiro positivo: ");
    if (scanf("%d", &numero) != 1 || numero < 0)
    {
        printf("Entrada invalida!\n");
        return 1;
    }

    printf("O numero %d em binario:\n", numero);

    if (numero == 0)
    {
        printf("0\n");
        return 0;
    }

    while (numero > 0)
    {
        binario[quantidade_digitos] = numero % 2;
        quantidade_digitos++;
        numero = numero / 2;
    }

    for (int i = quantidade_digitos - 1; i >= 0; i--)
    {
        printf("%d", binario[i]);
    }

    printf("\n");
    return 0;
}
