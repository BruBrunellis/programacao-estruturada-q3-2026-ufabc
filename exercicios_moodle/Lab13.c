/*
Laboratório 03 - Arranjos
L03_04 - Cameras de segurança

Otimização de Câmeras de Segurança

Joãozinho possui uma empresa especializada em segurança de condomínios
e um de seus serviços é a instalação de sistemas de videomonitoramento.
Desenvolva um programa que otimize a colocação de câmeras para garantir
a cobertura total das ruas de um condomínio, respeitando um número
exato de câmeras a serem instaladas.

Modelo do condomínio e funcionamento das câmeras:
    - Cada rua é uma única quadra e conecta exatamente duas esquinas.
    - Não existem ruas sem saída; ambas as extremidades estão conectadas
      a esquinas.
    - As câmeras possuem visão de 360 graus e alcance para cobrir uma
      rua inteira quando instaladas em qualquer uma de suas esquinas.
    - As câmeras só podem ser instaladas nas esquinas das ruas.
    - Uma câmera em uma esquina monitora todas as ruas conectadas a ela.

Problema:
Receba o mapa de ruas e um inteiro K. Determine se é possível vigiar
todas as ruas utilizando exatamente K câmeras. Em caso afirmativo,
identifique e liste as esquinas onde elas devem ser instaladas.

Representação do mapa:
    N: número de esquinas, identificadas de 0 a N - 1.
    M: número de ruas, identificadas de 0 a M - 1.
    Matriz de adjacência A, com N linhas e M colunas:
        A[I][J] = 1: a esquina I é uma extremidade da rua J.
        A[I][J] = 0: a esquina I não é uma extremidade da rua J.
    Cada coluna J possui exatamente dois valores 1; os demais são 0.

No mapa de exemplo, a esquina 7 é extremidade das ruas 6, 7, 8 e 11.
Uma câmera na esquina 7 monitora essas quatro ruas. O mapa possui
N = 11, M = 14 e a seguinte matriz:

    1 0 0 1 0 0 0 0 0 0 0 0 0 0
    1 1 0 0 0 0 0 0 0 0 0 0 0 0
    0 1 1 0 0 0 0 0 1 0 1 0 0 0
    0 0 1 1 0 0 0 0 0 1 0 0 0 0
    0 0 0 0 1 0 0 1 0 0 0 0 0 0
    0 0 0 0 1 1 0 0 0 0 0 0 0 0
    0 0 0 0 0 1 1 0 0 0 0 0 0 0
    0 0 0 0 0 0 1 1 1 0 0 1 0 0
    0 0 0 0 0 0 0 0 0 1 0 0 1 0
    0 0 0 0 0 0 0 0 0 0 1 0 1 1
    0 0 0 0 0 0 0 0 0 0 0 1 0 1

Formato da entrada:
    A primeira linha contém três inteiros positivos N, M e K,
    separados por um espaço em branco:
        N: número de esquinas;
        M: número de ruas;
        K: número exato de câmeras a serem instaladas.
    As N linhas seguintes representam a matriz, cada uma com M valores
    binários (0 ou 1) separados por espaços.

Restrições dos dados:
    3 <= N <= 30
    3 <= M <= 50
    1 <= K <= N

Formato da saída:
    - Se não houver configuração que vigie todas as ruas com K câmeras,
      imprima -1.
    - Se houver, imprima os identificadores das K esquinas selecionadas
      em ordem crescente, separados por um único espaço em branco.
    - Se houver múltiplas combinações válidas, imprima a combinação
      lexicograficamente menor (ordem do dicionário).
      Por exemplo, entre {0, 1, 3, 5, 7, 9} e {1, 2, 3, 5, 7, 9},
      ambas válidas para K = 6, a saída deve ser 0 1 3 5 7 9.
    - A saída deve ser seguida por uma quebra de linha.

Recursividade:
O programa deve utilizar recursividade. Crie uma função específica
chamada distribuiCameras que encapsule a lógica recursiva de busca.

Estratégia sugerida pelo enunciado:
    - Crie um vetor de inteiros vigiada de tamanho M (um vetor de
      50 posições é adequado), inicializado com zeros.
    - vigiada[J] conta quantas câmeras monitoram a rua J na solução
      sendo construída pelo procedimento recursivo.
    - Ao selecionar uma esquina I, incremente vigiada[J] para cada
      rua J conectada a I, conforme a matriz.
    - Ao desfazer a instalação em I durante o backtracking, decremente
      vigiada[J] para todas as ruas conectadas a I. Assim o vetor
      reflete as câmeras consideradas na solução parcial.
    - Uma solução vigia todas as ruas quando todas as posições
      de 0 a M - 1 têm valores positivos: vigiada[J] > 0 para todo J.

Exemplos de execução:
    Exemplo 1 - Condomínio simples (N = 3, M = 3, K = 2)
    Entrada:
        3 3 2
        0 1 1
        1 0 1
        1 1 0
    Saída:
        0 1

    Exemplo 2 - Não é possível (N = 3, M = 3, K = 1)
    Entrada:
        3 3 1
        0 1 1
        1 0 1
        1 1 0
    Saída:
        -1

    Exemplo 3 - Condomínio maior (N = 11, M = 14, K = 7)
    Entrada:
        11 14 7
        1 0 0 1 0 0 0 0 0 0 0 0 0 0
        1 1 0 0 0 0 0 0 0 0 0 0 0 0
        0 1 1 0 0 0 0 0 1 0 1 0 0 0
        0 0 1 1 0 0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 1 0 0 0 0 0 0
        0 0 0 0 1 1 0 0 0 0 0 0 0 0
        0 0 0 0 0 1 1 0 0 0 0 0 0 0
        0 0 0 0 0 0 1 1 1 0 0 1 0 0
        0 0 0 0 0 0 0 0 0 1 0 0 1 0
        0 0 0 0 0 0 0 0 0 0 1 0 1 1
        0 0 0 0 0 0 0 0 0 0 0 1 0 1
    Saída:
        0 1 2 3 5 7 9

    Exemplo 4 - Condomínio maior (N = 11, M = 14, K = 5)
    Entrada:
        11 14 5
        1 0 0 1 0 0 0 0 0 0 0 0 0 0
        1 1 0 0 0 0 0 0 0 0 0 0 0 0
        0 1 1 0 0 0 0 0 1 0 1 0 0 0
        0 0 1 1 0 0 0 0 0 1 0 0 0 0
        0 0 0 0 1 0 0 1 0 0 0 0 0 0
        0 0 0 0 1 1 0 0 0 0 0 0 0 0
        0 0 0 0 0 1 1 0 0 0 0 0 0 0
        0 0 0 0 0 0 1 1 1 0 0 1 0 0
        0 0 0 0 0 0 0 0 0 1 0 0 1 0
        0 0 0 0 0 0 0 0 0 0 1 0 1 1
        0 0 0 0 0 0 0 0 0 0 0 1 0 1
    Saída:
        1 3 5 7 9
*/

#include <stdio.h>


#define MAX_ESQUINAS 30
#define MAX_RUAS 50

int distribuiCameras(int N, int M, int K, int A[][MAX_RUAS],
                    const int ultimaEsquina[], int vigiada[],
                    int escolhidas[], int esquina, int quantidade) {
    // As esquinas restantes precisam comportar as cameras que faltam.
    if (N - esquina < K - quantidade) {
        return 0;
    }

    int todasVigiadas = 1;
    for (int rua = 0; rua < M; rua++) {
        if (vigiada[rua] == 0) {
            todasVigiadas = 0;

            // As duas extremidades ja foram descartadas neste caminho.
            if (ultimaEsquina[rua] < esquina) {
                return 0;
            }
        }
    }

    if (quantidade == K) {
        return todasVigiadas;
    }

    // Se ja cobrimos tudo, completamos K com as menores esquinas livres.
    if (todasVigiadas) {
        while (quantidade < K) {
            escolhidas[quantidade++] = esquina++;
        }
        return 1;
    }

    // Incluir a esquina antes de exclui-la garante a ordem lexicografica.
    escolhidas[quantidade] = esquina;
    for (int rua = 0; rua < M; rua++) {
        vigiada[rua] += A[esquina][rua];
    }

    if (distribuiCameras(N, M, K, A, ultimaEsquina, vigiada,
                        escolhidas, esquina + 1, quantidade + 1)) {
        return 1;
    }

    // Desfaz a instalacao antes de tentar uma solucao sem esta esquina.
    for (int rua = 0; rua < M; rua++) {
        vigiada[rua] -= A[esquina][rua];
    }

    return distribuiCameras(N, M, K, A, ultimaEsquina, vigiada,
                           escolhidas, esquina + 1, quantidade);
}

int main(void) {
    int N, M, K;
    int A[MAX_ESQUINAS][MAX_RUAS];
    int ultimaEsquina[MAX_RUAS];
    int vigiada[MAX_RUAS] = {0};
    int escolhidas[MAX_ESQUINAS];

    if (scanf("%d %d %d", &N, &M, &K) != 3) {
        return 0;
    }
    if (N < 3 || N > MAX_ESQUINAS || M < 3 || M > MAX_RUAS ||
        K < 1 || K > N) {
        return 0;
    }

    for (int rua = 0; rua < M; rua++) {
        ultimaEsquina[rua] = -1;
    }
    for (int esquina = 0; esquina < N; esquina++) {
        for (int rua = 0; rua < M; rua++) {
            if (scanf("%d", &A[esquina][rua]) != 1) {
                return 0;
            }
            if (A[esquina][rua] == 1) {
                ultimaEsquina[rua] = esquina;
            }
        }
    }

    if (distribuiCameras(N, M, K, A, ultimaEsquina, vigiada,
                        escolhidas, 0, 0)) {
        for (int i = 0; i < K; i++) {
            printf("%s%d", i == 0 ? "" : " ", escolhidas[i]);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }

    return 0;
}
