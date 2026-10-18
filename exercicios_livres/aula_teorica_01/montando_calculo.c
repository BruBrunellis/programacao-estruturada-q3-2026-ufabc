/*Exercício -
Crie um programa que lê 2 números e, em seguida,
peça um caractere que represente um operador aritmético (+ , -, *, /)
O programa deve realizar a operação entre os dois números e exibir o resultado
*/

#include <stdio.h>

int main(void)
{
    float num1 = 0, num2 = 0;
    char operador = 0;

    printf("Digite o primeiro numero: ");
    scanf("%f", &num1);
    printf("Digite o segundo numero: ");
    scanf("%f", &num2);
    printf("Digite a operacao aritmetica: ");
    scanf(" %c", &operador);

    switch (operador)
    {
    case '+':
        printf("Resuldado de %f + %f: %f", num1, num2, (num1 + num2));
        break;
    case '-':
        printf("Resuldado de %f - %f: %f", num1, num2, (num1 - num2));
        break;
    case '*':
        printf("Resuldado de %f * %f: %f", num1, num2, (num1 * num2));
        break;
    case '/':
        printf("Resuldado de %f / %f: %f", num1, num2, (num1 / num2));
        break;

    default:
        printf("Operador invalido!");
    }

    return 0;
}
