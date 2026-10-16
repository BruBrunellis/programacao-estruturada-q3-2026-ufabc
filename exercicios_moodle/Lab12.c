/*
Laboratório 03 - Arranjos
L03_03 - Maior soma de um subvetor

Maior Soma de Subvetor com Recursão

Implemente uma função recursiva para resolver o problema da maior soma
de um subvetor contíguo de inteiros (maximum subarray).

Aplicação prática:
Considere os preços diários [100, 98, 101, 102, 97, 110]. Comprar a 97
e vender a 110 gera lucro de 13. Transformando os preços em diferenças
consecutivas (variação diária), temos:

    Preços:     [100, 98, 101, 102, 97, 110]
    Diferenças: [ -2, +3,  +1,  -5, +13]

A soma de um subvetor contíguo das diferenças corresponde ao lucro
entre um dia de compra e um de venda. O lucro máximo é a maior soma
de um subvetor dessas diferenças. No exemplo, essa soma é 13.

Algoritmo recursivo:
A abordagem divide o vetor ao meio. A maior soma deve estar em um
destes três casos:
    - Inteiramente no lado esquerdo;
    - Inteiramente no lado direito;
    - Atravessando o meio (parte final da esquerda e inicial da direita).

Resolva recursivamente os casos esquerdo e direito. Para o caso que
cruza o meio, compute em tempo linear a melhor soma terminando no meio
pela esquerda e a melhor soma começando em meio + 1 pela direita.
Some as duas. O resultado é o máximo entre os três casos.

Assinatura da função:
    int MaiorSomaSubvetor(const int A[], int l, int r);

Explicação do caso que cruza o meio:
Para o índice central mid, compute:
    - left_max: maior soma de um sufixo que termina em mid, varrendo
      da direita para a esquerda, acumulando e guardando o melhor valor;
    - right_max: maior soma de um prefixo que começa em mid + 1,
      varrendo da esquerda para a direita, acumulando e guardando
      o melhor valor.

A melhor soma que cruza é left_max + right_max. O resultado final é
o máximo entre left_sum, right_sum e left_max + right_max.

Exemplos de entrada e saída:
A primeira linha de cada entrada indica a quantidade de elementos.

    Exemplo 1 - Entrada:
        8
        -2
        -3
        4
        -1
        -2
        1
        5
        -3
    Saída:
        Vetor: -2 -3 4 -1 -2 1 5 -3
        Maior soma: 7

    Exemplo 2 - Entrada:
        6
        -8
        -3
        -6
        -2
        -5
        -4
    Saída:
        Vetor: -8 -3 -6 -2 -5 -4
        Maior soma: -2

    Exemplo 3 - Entrada:
        10
        1
        2
        -1
        2
        -3
        2
        -5
        4
        -1
        2
    Saída:
        Vetor: 1 2 -1 2 -3 2 -5 4 -1 2
        Maior soma: 5

Tente resolver sem seguir o pseudocódigo.

Pseudocódigo fornecido no enunciado (sugestão):
    função MaiorSomaSubvetor(A, l, r) retorna inteiro
        se l == r então
            // Base: subvetor de um elemento
            retorne A[l]
        fimse

        m <- (l + r) div 2

        esquerda <- MaiorSomaSubvetor(A, l, m)
        direita  <- MaiorSomaSubvetor(A, m + 1, r)
        cruzando <- MaxCruzando(A, l, m, r)

        retorne Max(esquerda, direita, cruzando) // Max retorna o maior valor
    fimfunção

    função MaxCruzando(A, l, m, r) retorna inteiro
        // Melhor sufixo do lado esquerdo (terminando em m)
        soma <- 0
        melhorEsq <- -infinito
        para i de m até l passo -1 faça
            soma <- soma + A[i]
            se soma > melhorEsq então
                melhorEsq <- soma
            fimse
        fimpara

        // Melhor prefixo do lado direito (começando em m + 1)
        soma <- 0
        melhorDir <- -infinito
        para j de m + 1 até r faça
            soma <- soma + A[j]
            se soma > melhorDir então
                melhorDir <- soma
            fimse
        fimpara

        retorne melhorEsq + melhorDir
    fimfunção
*/

#include <stdio.h>

int MaxCruzando(const int A[], int l, int m, int r) {
    // Melhor sufixo do lado esquerdo (terminando em m)
    int soma = 0;
    int melhorEsq = A[m]; // Inicializa com o valor de A[m]
    for (int i = m; i >= l; i--) {
        soma += A[i];
        if (soma > melhorEsq) {
            melhorEsq = soma;
        }
    }

    // Melhor prefixo do lado direito (começando em m + 1)
    soma = 0;
    int melhorDir = A[m + 1]; // Inicializa com o valor de A[m + 1]
    for (int j = m + 1; j <= r; j++) {
        soma += A[j];
        if (soma > melhorDir) {
            melhorDir = soma;
        }
    }

    return melhorEsq + melhorDir;
}

int MaiorSomaSubvetor(const int A[], int l, int r) {
    if (l == r) {
        // Base: subvetor de um elemento
        return A[l];
    }

    int maior = (l + r) / 2;

    int esquerda = MaiorSomaSubvetor(A, l, maior);
    int direita = MaiorSomaSubvetor(A, maior + 1, r);
    int cruzando = MaxCruzando(A, l, maior, r);

    // Retorna o máximo entre os três casos
    return (esquerda > direita) ? ((esquerda > cruzando) ? esquerda : cruzando) : ((direita > cruzando) ? direita : cruzando);
}

int main() {
    int n;

    // Lê a quantidade de elementos
    scanf("%d", &n);
    int A[n];

    // Lê os elementos do vetor
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    // Calcula a maior soma de subvetor
    int maiorSoma = MaiorSomaSubvetor(A, 0, n - 1);

    // Imprime o vetor e a maior soma
    printf("Vetor:");
    for (int i = 0; i < n; i++) {
        printf(" %d", A[i]);
    }
    printf("\nMaior soma: %d\n", maiorSoma);

    return 0;
}
