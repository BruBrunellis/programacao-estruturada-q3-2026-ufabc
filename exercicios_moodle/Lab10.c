/*Encontrar o segundo menor valor de um vetor
Implemente uma função em C que receba um vetor de inteiros com tamanho fixo de 10 posições e determine o segundo menor valor distinto presente nesse vetor. Considere que o vetor contém pelo menos dois valores diferentes.

Assinatura da função
int segundoMenorValor(const int v[]);
Especificação
O vetor de entrada possui tamanho fixo de 10 elementos.
O resultado é o segundo menor valor distinto do vetor
O vetor possui pelo menos dois valores distintos.
Não utilize a ordenação completa do vetor como solução principal
Evite o uso de estruturas auxiliares desnecessárias
*/

#include <stdio.h>
#define tamanho 10

int segundoMenorValor(const int vetor[]) {
    int menor = vetor[0];

    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
        }
    }

    int segmenor = menor;

    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] != menor &&
            (segmenor == menor || vetor[i] < segmenor)) {
            segmenor = vetor[i];
        }
    }

    return segmenor;
}

int main(){

    int numeros[tamanho], num;

    for(int i = 0; i < tamanho ; i++){
        scanf("%d", &num);
        numeros[i] = num;
    }

    printf("Vetor: ");
    for (int i = 0; i < tamanho; i++){
        printf("%d ", numeros[i]);
    }

    int segmenor = segundoMenorValor(numeros);

    printf("\nSegundo menor valor: %d", segmenor);

    return 0;
}

