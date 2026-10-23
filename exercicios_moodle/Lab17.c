/*
Laboratório 04 - Alocação Dinâmica
L04_04 - Busca em Largura (BFS)

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87375
Consultado em 22/10/2026. Formatação normalizada para comentário em C.

Busca em Largura (BFS - Breadth-First Search)

A Busca em Largura (BFS) é um dos algoritmos fundamentais para exploração
de grafos, sendo o arquétipo para muitos outros algoritmos importantes.
Seu principal objetivo é descobrir sistematicamente todos os vértices
alcançáveis a partir de um vértice fonte s em um grafo G = (V, E).

O nome "Busca em Largura" deriva da maneira como ele expande a fronteira
entre vértices descobertos e não descobertos. Ele descobre todos os
vértices a uma distância k do vértice fonte s antes de descobrir
quaisquer vértices a uma distância k + 1.

Para rastrear o progresso, a BFS utiliza um esquema de cores:
    - Branco: o vértice ainda não foi descoberto.
    - Cinza: o vértice foi descoberto (enfileirado), mas seus vértices
      adjacentes ainda não foram totalmente examinados. Representam
      a "fronteira" da busca.
    - Preto: o vértice foi descoberto e todos os seus vértices
      adjacentes já foram examinados.

Além disso, a BFS calcula duas informações para cada vértice v:
    - Distância (v.d): o menor número de arestas (caminho mínimo)
      da fonte s até v.
    - Predecessor (v.p): o vértice que o descobriu na árvore de busca
      em largura, essencial para reconstruir o caminho.

Algoritmo BFS (pseudocódigo fornecido no enunciado):

    BFS(G, s)
    1  para cada vértice u ∈ G[V] - {s}
    2       u.cor = BRANCO
    3       u.d = INFINITO
    4       u.p = NIL
    5  s.cor = CINZA
    6  s.d = 0
    7  s.p = NIL
    8  Q = fila vazia
    9  ENQUEUE(Q, s)
    10 WHILE Q não está vazia
    11      u = DEQUEUE(Q)
    12      para cada v ∈ Adj[u]
    13          SE v.cor == BRANCO
    14              v.cor = CINZA
    15              v.d = u.d + 1
    16              v.p = u
    17              ENQUEUE(Q, v)
    18      u.cor = PRETO

O algoritmo segue os seguintes passos:

    Inicialização:
        - Todos os vértices (exceto a fonte s) são pintados de branco.
        - Suas distâncias (d) são definidas como infinito.
        - Seus predecessores (p) são definidos como NIL
          (indicando que não possuem predecessor).

    Configuração da fonte:
        - O vértice fonte s é pintado de cinza.
        - Sua distância s.d é definida como 0.
        - Seu predecessor s.p é definido como NIL.

    Fila:
        Uma fila Q do tipo "primeiro a entrar, primeiro a sair" (FIFO)
        é inicializada e o vértice fonte s é enfileirado nela.
        A fila gerencia os vértices cinzentos.

    Processamento principal:
        Enquanto a fila Q não estiver vazia:
            - Desenfileire um vértice u.
            - Para cada vértice v adjacente a u
              (ou seja, (u, v) é uma aresta em E):
                Se v ainda for branco:
                    - Pinte v de cinza.
                    - Defina v.d = u.d + 1.
                    - Defina v.p = u.
                    - Enfileire v.
            - Após examinar todos os vizinhos de u, pinte u de preto.

Objetivo:
Implementar o algoritmo de Busca em Largura (BFS) em C para encontrar
as distâncias de caminho mínimo e os predecessores de todos os vértices
alcançáveis a partir de um vértice fonte, dado um grafo não-dirigido
representado por uma matriz de adjacências.

Requisitos:
    - Representação do grafo:
        O grafo será representado por uma matriz de adjacências
        int adj[N][N], onde N é uma entrada do programa.
        adj[i][j] = 1 se houver uma aresta entre os vértices i e j,
        e 0 caso contrário. Para um grafo não-dirigido, a matriz
        será simétrica.

    - Implementação:
        Todas as informações sobre os vértices (cor, distância,
        predecessor) devem ser armazenadas em vetores separados,
        onde o índice do vetor corresponde ao ID do vértice.
        Por exemplo:
            int cores[N];
            int distancias[N];
            int predecessores[N];

    - Fila:
        Implemente uma fila FIFO usando um vetor para gerenciar
        os vértices a serem visitados.

    - Função bfs(int grafo[][N], int num_vertices, int fonte):
        Deve realizar a busca em largura, atualizando os vetores
        cores, distancias e predecessores.

    - Saída:
        Após a BFS, imprima a distância e o predecessor de cada vértice
        em relação à fonte. Para vértices inalcançáveis, a distância
        deve ser infinito (represente por um valor grande como INT_MAX)
        e o predecessor como NIL (represente por -1).

Exemplo ilustrativo:
A figura no Moodle ilustra o progresso da BFS em um grafo com 8 vértices
(s, r, w, t, x, v, u, y). Ela mostra como as distâncias (u.d) são
calculadas e como a fila Q evolui a cada passo. As arestas da árvore
de busca são sombreadas à medida que são descobertas.
O vértice fonte inicial é s.

Figura original:
https://moodle.ufabc.edu.br/pluginfile.php/195423/mod_vpl/intro/grafos.png

Para a implementação, o mapeamento dos vértices para inteiros é:
    s -> 0
    r -> 1
    w -> 2
    t -> 3
    x -> 4
    v -> 5
    u -> 6
    y -> 7

Grafo com 8 vértices (0 a 7), vértice fonte = 0 (s):

    Matriz de Adjacências
         0 1 2 3 4 5 6 7
    0(s) 0 1 1 0 0 0 0 0
    1(r) 1 0 0 0 0 1 0 0
    2(w) 1 0 0 1 1 0 0 0
    3(t) 0 0 1 0 1 0 1 0
    4(x) 0 0 1 1 0 0 0 1
    5(v) 0 1 0 0 0 0 0 0
    6(u) 0 0 0 1 0 0 0 1
    7(y) 0 0 0 0 1 0 1 0

    BFS a partir do vértice 0 (s):
    Vertice 0 (s): Distancia = 0, Predecessor = -1
    Vertice 1 (r): Distancia = 1, Predecessor = 0 (s)
    Vertice 2 (w): Distancia = 1, Predecessor = 0 (s)
    Vertice 3 (t): Distancia = 2, Predecessor = 2 (w)
    Vertice 4 (x): Distancia = 2, Predecessor = 2 (w)
    Vertice 5 (v): Distancia = 2, Predecessor = 1 (r)
    Vertice 6 (u): Distancia = 3, Predecessor = 3 (t)
    Vertice 7 (y): Distancia = 3, Predecessor = 4 (x)

Exemplos de entrada e saída:
A entrada será o valor de N e a matriz de adjacências.
Para todos os casos, assumir vértice fonte = 0.

    Exemplo 1 - Todos os vértices alcançáveis
    Entrada:
        6
        0 1 1 0 0 0
        1 0 0 1 0 0
        1 0 0 1 0 0
        0 1 1 0 1 1
        0 0 0 1 0 1
        0 0 0 1 1 0
    Saída:
        BFS a partir do vértice 0:
        Vertice 0: Distancia = 0, Predecessor = -1
        Vertice 1: Distancia = 1, Predecessor = 0
        Vertice 2: Distancia = 1, Predecessor = 0
        Vertice 3: Distancia = 2, Predecessor = 1 (ou 2)
        Vertice 4: Distancia = 3, Predecessor = 3
        Vertice 5: Distancia = 3, Predecessor = 3

    Nota do enunciado: o predecessor de um vértice pode variar se houver
    múltiplos caminhos mínimos. Qualquer predecessor válido que resulte
    em um caminho mínimo é aceitável.

    Exemplo 2 - Vértices inalcançáveis
    Entrada:
        4
        0 1 0 0
        1 0 0 0
        0 0 0 0
        0 0 0 0
    Saída:
        BFS a partir do vértice 0:
        Vertice 0: Distancia = 0, Predecessor = -1
        Vertice 1: Distancia = 1, Predecessor = 0
        Vertice 2: Distancia = 999999, Predecessor = -1
        Vertice 3: Distancia = 999999, Predecessor = -1

Dicas do enunciado:

    Constantes:
        Defina macros para as cores:
            #define BRANCO 0
            #define CINZA 1
            #define PRETO 2
        Defina NIL como -1.

    Representação de INFINITO:
        Por exemplo, #define INFINITO 999999. Garanta que esse valor
        seja sempre maior do que o número máximo de arestas que
        podem existir no caminho mais longo do seu grafo.

    Inicialização:
        Antes de iniciar a BFS, use um laço para inicializar todos
        os vetores cores, distancias e predecessores com seus valores
        padrão (BRANCO, INFINITO, NIL).

    Implementação da fila (com vetores):
        Uma fila pode ser implementada com um array e dois ponteiros
        (ou índices) que controlam o início (head) e o fim (tail).
        Quando head é igual a tail, a fila está vazia.
        O tamanho da fila deve ser, no máximo, N.

    Pseudocódigo fornecido para as operações da fila:

        // Variáveis globais ou passadas por referência
        int FILA[N];
        int head; // Índice do primeiro elemento da fila
        int tail; // Índice da próxima posição livre na fila
                  // (onde o próximo elemento será inserido)
        int tamanho_max_fila = N;

        // Inicializa a fila
        PROCEDIMENTO inicializarFila()
            head = 0
            tail = 0
        FIM PROCEDIMENTO

        // Verifica se a fila está vazia
        FUNCAO booleana filaVazia()
            RETORNA (head == tail)
        FIM FUNCAO

        // Verifica se a fila está cheia (opcional para evitar overflow)
        FUNCAO booleana filaCheia()
            // Uma fila circular está cheia quando
            // (tail + 1) % tamanho_max_fila == head
            RETORNA ((tail + 1) % tamanho_max_fila == head)
        FIM FUNCAO

        // Insere um elemento na fila
        PROCEDIMENTO enfileirar(int valor)
            SE filaCheia() ENTÃO
                // Tratar erro ou redimensionar fila
                // (para este exercício, assumir que não enche)
                IMPRIME "Erro: Fila cheia!"
                RETORNA
            FIM SE
            FILA[tail] = valor
            tail = (tail + 1) % tamanho_max_fila
            // Avança a 'tail' de forma circular
        FIM PROCEDIMENTO

        // Remove e retorna um elemento da fila
        FUNCAO inteiro desenfileirar()
            SE filaVazia() ENTÃO
                // Tratar erro
                IMPRIME "Erro: Fila vazia!"
                RETORNA -1 // Ou outro valor de erro
            FIM SE
            int valor = FILA[head]
            head = (head + 1) % tamanho_max_fila
            // Avança a 'head' de forma circular
            RETORNA valor
        FIM FUNCAO

        Para usar esta fila na BFS, chame inicializarFila() no início,
        enfileirar(s) para o vértice fonte e, dentro de
        while (!filaVazia()), chame u = desenfileirar() e enfileirar(v)
        para os vizinhos.

    Laço para vizinhos:
        Ao percorrer os vizinhos de um vértice u, use um laço
        for (int v = 0; v < num_vertices; v++) e verifique se
        grafo[u][v] == 1.

    Modularidade:
        Mantenha a função bfs clara e separada da lógica principal
        de leitura do grafo e impressão dos resultados.

    Função main:
        No main, declare e aloque a matriz de adjacências, os vetores
        para cores, distâncias e predecessores, preencha a matriz
        e chame a função bfs.

Referência do enunciado:
Definições, algoritmos e figura extraídas do livro
"Algoritmos: teoria e prática", Thomas H. Cormen et al.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define NIL (-1)
#define INFINITO 999999

void bfs(int num_vertices, int grafo[][num_vertices], int fonte,
         int cores[], int distancias[], int predecessores[], int fila[]) {
    for (int u = 0; u < num_vertices; u++) {
        cores[u] = BRANCO;
        distancias[u] = INFINITO;
        predecessores[u] = NIL;
    }

    int inicio = 0;
    int fim = 0;
    cores[fonte] = CINZA;
    distancias[fonte] = 0;
    fila[fim++] = fonte;

    while (inicio < fim) {
        int u = fila[inicio++];
        // Visita em ordem crescente para desempatar caminhos minimos.
        for (int v = 0; v < num_vertices; v++) {
            if (grafo[u][v] == 1 && cores[v] == BRANCO) {
                cores[v] = CINZA;
                distancias[v] = distancias[u] + 1;
                predecessores[v] = u;
                // Cada vertice entra uma unica vez: N posicoes bastam.
                fila[fim++] = v;
            }
        }
        cores[u] = PRETO;
    }
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 0;
    }
    if ((size_t)n > SIZE_MAX / sizeof(int) / (size_t)n) {
        return 1;
    }

    int (*grafo)[n] = malloc((size_t)n * sizeof(*grafo));
    int *cores = malloc((size_t)n * sizeof(*cores));
    int *distancias = malloc((size_t)n * sizeof(*distancias));
    int *predecessores = malloc((size_t)n * sizeof(*predecessores));
    int *fila = malloc((size_t)n * sizeof(*fila));
    int resultado = 0;

    if (grafo == NULL || cores == NULL || distancias == NULL ||
        predecessores == NULL || fila == NULL) {
        resultado = 1;
        goto liberar;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &grafo[i][j]) != 1) {
                goto liberar;
            }
        }
    }

    bfs(n, grafo, 0, cores, distancias, predecessores, fila);
    printf("BFS a partir do vértice 0:\n");
    for (int i = 0; i < n; i++) {
        printf("Vertice %d: Distancia = %d, Predecessor = %d\n",
               i, distancias[i], predecessores[i]);
    }

liberar:
    free(grafo);
    free(cores);
    free(distancias);
    free(predecessores);
    free(fila);
    return resultado;
}

