//Jogo de dados simplificado

#include <stdio.h>
#include <stdlib.h> //para funçoes rand() e srand()

int main(void)
{
    int dado1, dado2, seed;

    printf("Seed: ");
    scanf("%d", &seed);

    srand(seed); //inicializa o gerador de números aleatórios com a seed informada

    dado1 = (rand()%6) + 1; //lançamento do dado 1
    dado2 = (rand()%6) + 1; //lançamento do dado 2

    /*
    A função ran() irá gerar um número aleatório grande,
    ao pedir o resto de divisão por 6, (%6), os resultados possíveis
    são [0,1,2,3,4,5]. Como dados não tem o número 0, somamos 1
    */

    int soma = dado1 + dado2;

    if (soma == 7 || soma == 11)
        printf("Resultado %d + %d = %d. Jogador ganhou!\n", dado1, dado2, soma);
    else if (soma == 2 || soma == 3 || soma == 12)
        printf("Resultado %d + %d = %d. Jogador perdeu!\n", dado1, dado2, soma);
    else
        printf("Resultado %d + %d = %d. Jogue novamente!\n", dado1, dado2, soma);

    return 0;
}
