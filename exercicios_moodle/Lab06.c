/*
Verificação de Número Harshad (ou Niven)

Um número Harshad (também conhecido como Número de Niven) é um número inteiro que é divisível pela soma de
seus próprios dígitos. Por exemplo, o número 21 é um número Harshad porque a soma de seus dígitos é
(2 + 1 = 3),  e 21 é divisível por 3 (21 / 3 = 7). Outro exemplo é 156: a soma dos dígitos é (1 + 5 + 6 = 12),
e 156 é divisível por 12 (156 / 12 = 13).

Crie programa que implemente uma função em C chamada ehHarshad que receba um número inteiro como entrada e retorne 1 (verdadeiro)
se o número for um Harshad, ou 0 (falso) caso contrário.

Assinatura da Função:
int ehHarshad(int numero);
*/

#include <stdio.h>

int numero = 0, digito = 0, soma = 0, check = 0;

int Somadigitos (int numero)
{
    while(numero != 0)
    {
        digito = numero % 10;
        soma += digito;
        numero = numero / 10;
    }

    return soma;
}


int ehHarshad (int numero)
{
    soma = Somadigitos(numero);
    check = numero % soma;
    if (check == 0)
        return 1;
    else
        return 0;
}

int main(void)
{
    while(numero == 0){scanf("%d", &numero);}

    check = ehHarshad(numero);

    switch (check)
    {
    case 1:
        printf("1");
        break;

    default:
        printf("0");
        break;
    }

    return 0;
}
