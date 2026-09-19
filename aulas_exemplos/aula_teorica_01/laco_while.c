/*Comando while
Enquanto a condição for verdadeira, os comandos são executados

while (condicao)
{
//comandos
}

Comando do - while

Sempre executa os comandos pelo menos uma vez. O teste condicional é feito por último

do {
//comandos
} while (condicao);

Comandos continue e break

- break: faz com que a execução seja terminada, passando a execução para o próximo comando depois do final do laço
- continue: faz com que a execução de um laço seja alterada para o final do laço
*/

//Ler n números, mostrar Maior e Menor números

#include <stdio.h>

int main(void)
{
    int count, n;
    double numero, maior, menor;

    printf("Digite a quantidade de numeros n: ");
    scanf("%d", &n);

    printf("Digite o numero: ");
    scanf("%lf", &numero);

    maior = numero;
    menor = numero;
    count = 1;

    while (count < n)
    {
        printf("Digite o numero: ");
        scanf("%lf", &numero);

        if (numero > maior)
            maior = numero;
        else if (numero < menor)
            menor = numero;
        count++;
    }

    printf("Maior = %2.f\nMenor = %.2f\n", maior, menor);
    return 0;
}
