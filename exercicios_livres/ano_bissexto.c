/*Exercício -
Crie um programa em C que leaia um ano e verifique se ele é bissexto.
Um ano é considerado bissexto quando atende a uma das seguintes condições:
- É divisível por 4 e não é divisível por 100; ou
- é divisível por 400.
O programa deve informar se o ano fornecido é ou não bissexto.
*/

#include <stdio.h>

int main(void)
{
    int ano;

    printf("Informe um ano: ");
    scanf("%d", &ano);

    if ((ano % 4 == 0) && (ano % 100 != 0) || (ano % 400 == 0))
        printf("Ano bissexto\n");
    else
        printf("Ano nao bissexto\n");


    return 0;
}
