/*
Laboratório 04 - Alocação Dinâmica
L04_03 - Histograma

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87374
Consultado em 22/10/2026. Formatação normalizada para comentário em C.

Histograma

Um histograma é uma representação da distribuição de frequências de
um conjunto de dados numéricos. Ele divide o eixo dos valores em
intervalos contíguos e não sobrepostos (bins) e conta quantos elementos
caem em cada intervalo.

Programa:
    - Ler duas dimensões m e n e, em seguida, ler m linhas com n valores
      double por linha (leitura linha a linha).
    - Calcular o histograma dos m*n valores.
    - Imprimir o histograma no formato:
        centro_do_bin: sequência_de_asteriscos
    - Implementar:
        - Uma função histograma que calcula as frequências dos bins.
        - Uma função imprimir que mostra o histograma na tela
          no formato acima.
    - Garantir que toda memória alocada dinamicamente seja devidamente
      desalocada ao final.

Método para determinar os bins:

    Número de bins (B) - Regra de Rice:
        B = ceil(2 * N^(1/3))
        onde N = m*n é a quantidade total de valores.

    Largura do bin (w) e centros:
        Encontre os extremos do conjunto de dados: xmin e xmax.
        Largura: w = (xmax - xmin) / B
        Centro do bin i (com i = 0, 1, ..., B-1):
            ci = xmin + (i + 0.5) * w

    Atribuição de cada valor x a um bin:
        i(x) = floor((x - xmin) / w)

        Para garantir que o valor máximo entre no último bin:
            i(x) = min(max(floor((x - xmin) / w), 0), B-1)

Dicas do enunciado:
    - Leitura linha a linha:
        - Leia m e n.
        - Leia n doubles para cada linha de m.
    - Checagem de casos degenerados:
        - Se xmax == xmin (todos os valores iguais), force B = 1,
          w = 1.0 (qualquer positivo), centers[0] = xmin e f[0] = N.
    - math.h: funções matemáticas
      (ceil, pow, floor, fabs, fmax, fmin).

Exemplos de entrada/saída:

    Exemplo 1 - Entrada:
        2 3
        -1.0 0.2 0.5
        1.4 2.0 -0.3
    Saída:
        -0.62: **
         0.12: *
         0.88: *
         1.62: **

    Exemplo 2 - Entrada:
        3 3
        -2.0 -1.0 0.0
        1.0  2.0  3.0
        -1.5 0.5  1.5
    Saída:
        -1.50: **
        -0.50: *
         0.50: **
         1.50: **
         2.50: **
*/

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t histograma(const double valores[], size_t quantidade,
                  double **centros, size_t **frequencias) {
    double minimo = valores[0];
    double maximo = valores[0];
    for (size_t i = 1; i < quantidade; i++) {
        if (valores[i] < minimo) {
            minimo = valores[i];
        }
        if (valores[i] > maximo) {
            maximo = valores[i];
        }
    }

    size_t bins = minimo == maximo ? 1 :
                  (size_t)ceil(2.0 * cbrt((double)quantidade));
    *centros = malloc(bins * sizeof(**centros));
    *frequencias = calloc(bins, sizeof(**frequencias));
    if (*centros == NULL || *frequencias == NULL) {
        free(*centros);
        free(*frequencias);
        *centros = NULL;
        *frequencias = NULL;
        return 0;
    }

    if (minimo == maximo) {
        (*centros)[0] = minimo;
        (*frequencias)[0] = quantidade;
        return bins;
    }

    double largura = (maximo - minimo) / (double)bins;
    for (size_t i = 0; i < bins; i++) {
        (*centros)[i] = minimo + ((double)i + 0.5) * largura;
    }
    for (size_t i = 0; i < quantidade; i++) {
        double posicao = floor((valores[i] - minimo) / largura);
        size_t indice;
        if (posicao <= 0.0) {
            indice = 0;
        } else if (posicao >= (double)bins) {
            indice = bins - 1;
        } else {
            indice = (size_t)posicao;
        }
        (*frequencias)[indice]++;
    }
    return bins;
}

void imprimir(const double centros[], const size_t frequencias[], size_t bins) {
    for (size_t i = 0; i < bins; i++) {
        // O espaco reserva o lugar do sinal para centros positivos.
        printf("% .2f: ", centros[i]);
        for (size_t j = 0; j < frequencias[i]; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}

int main(void) {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        return 0;
    }
    if ((size_t)m > SIZE_MAX / (size_t)n) {
        return 1;
    }
    size_t quantidade = (size_t)m * (size_t)n;
    if (quantidade > SIZE_MAX / sizeof(double)) {
        return 1;
    }

    // As linhas ficam consecutivas em um unico vetor dinamico.
    double *valores = malloc(quantidade * sizeof(*valores));
    if (valores == NULL) {
        return 1;
    }
    for (size_t i = 0; i < quantidade; i++) {
        if (scanf("%lf", &valores[i]) != 1) {
            free(valores);
            return 0;
        }
    }

    double *centros;
    size_t *frequencias;
    size_t bins = histograma(valores, quantidade, &centros, &frequencias);
    if (bins == 0) {
        free(valores);
        return 1;
    }
    imprimir(centros, frequencias, bins);
    free(centros);
    free(frequencias);
    free(valores);
    return 0;
}

