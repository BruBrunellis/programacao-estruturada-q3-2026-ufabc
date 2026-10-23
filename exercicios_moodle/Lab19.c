/*
Laboratório 05 - Estruturas e Arquivos
L05_02 - Dijkstra

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87378
Consultado em 23/10/2026. Formatação normalizada para comentário em C.

Algoritmo de Dijkstra para Caminhos Mínimos

1. Definição do Problema: Caminhos Mínimos de Fonte Única

O problema do caminho mínimo de fonte única busca encontrar o caminho
com o menor peso (ou custo, distância, tempo) de um vértice de partida
específico (a fonte) para todos os outros vértices acessíveis em um grafo
dirigido ponderado. Um grafo dirigido ponderado G = (V, E) consiste em
um conjunto de vértices V e um conjunto de arestas dirigidas E.
Cada aresta (u, v) em E possui um peso w(u, v), que é um valor real.
O peso de um caminho p = <v0, v1, ..., vk> é a soma dos pesos de suas
arestas constituintes:

    w(p) = soma de w(v[i-1], v[i]), para i de 1 até k.

O peso do caminho mínimo de u a v, denotado por d(u, v), é o menor peso
entre todos os caminhos possíveis de u a v. Nosso objetivo é encontrar
esse d(s, v) para um dado vértice fonte s e todos os outros vértices v em V.

2. Exemplo de Aplicação: Planejamento de Rotas

Imagine um serviço de GPS que precisa encontrar a rota mais curta
(ou mais rápida) de uma origem para um destino. Podemos modelar um
mapa rodoviário como um grafo:
    - Vértices (V): cruzamentos, cidades ou pontos de interesse.
    - Arestas (E): segmentos de estradas que conectam esses pontos.
    - Pesos das arestas w(u, v): distância rodoviária, tempo de viagem,
      custo de pedágios etc.
Ao aplicar Dijkstra, podemos determinar a sequência de estradas a
percorrer da origem ao destino com o menor custo, seja em distância,
tempo ou dinheiro. O exemplo citado é um motorista que quer encontrar
a rota mais curta do Rio de Janeiro a São Paulo.

3. O Algoritmo de Dijkstra

Resolve caminhos mínimos de fonte única em grafos dirigidos ponderados
onde todos os pesos das arestas são não negativos. Opera de forma gulosa,
expandindo progressivamente o conjunto de vértices para os quais o
caminho mínimo final foi determinado.

Princípio Fundamental:
O algoritmo mantém um conjunto S de vértices cujos pesos finais dos
caminhos mínimos, a partir da fonte s, já foram calculados.
Repetidamente seleciona o vértice u fora de S que tem a menor estimativa
atual, adiciona u a S e relaxa todas as arestas que saem de u.

Procedimentos Chave:
    1. INITIALIZE-SINGLE-SOURCE(G, s):
       Inicializa estimativas de caminho mínimo e predecessores.
       Para cada vértice v:
           v.d = infinito (estimativa de caminho mínimo).
           v.p = NIL (nenhum predecessor).
       Para a fonte s: s.d = 0.

    2. RELAX(u, v, w):
       Tenta melhorar a estimativa de v encontrando um caminho mais
       curto através de u. Se v.d > u.d + w(u, v):
           v.d = u.d + w(u, v)
           v.p = u
       Relaxar uma aresta (u, v) consiste em testar se podemos melhorar
       o caminho mínimo até v passando por u e, em caso positivo,
       atualizar v.d e v.p.

    3. Fila de Prioridades Mínimas (Q):
       Armazena os vértices em V - S. A prioridade de cada vértice v
       é sua estimativa v.d. Operações essenciais:
           INSERT(Q, v): adiciona v à fila.
           EXTRACT-MIN(Q): remove e retorna o vértice de menor v.d.
           DECREASE-KEY(Q, v, new_key): atualiza a chave de v se
               new_key for menor que sua chave atual.

Algoritmo:
    DIJKSTRA(G, w, s)
        INITIALIZE-SINGLE-SOURCE(G, s)
        S = conjunto vazio // Vértices com caminhos mínimos finalizados
        Q = G.V // Fila mínima com todos os vértices; chaves são os v.d

        while Q não está vazio
            u = EXTRACT-MIN(Q) // Vértice de menor distância
            S = S união {u}   // Adiciona u aos vértices finalizados

            for cada vértice v adjacente a u (aresta (u, v) que sai de u)
                RELAX(u, v, w) // Atualiza v.d e v.p se houver melhora

4. Execução do Exemplo

Exemplo usando s como fonte. Figura original:
    https://moodle.ufabc.edu.br/pluginfile.php/195426/mod_vpl/intro/djisktra.png

Matriz de adjacências apresentada no enunciado (INF representa infinito):
    De / Para | s (0) | t (1) | x (2) | y (3) | z (4)
    s (0)     | INF   | 10    | INF   | 5     | INF
    t (1)     | INF   | INF   | 2     | INF   | INF
    x (2)     | INF   | INF   | INF   | INF   | INF
    y (3)     | INF   | 3     | 9     | INF   | 2
    z (4)     | 7     | INF   | 6     | INF   | INF

    a) Estado inicial:
       INITIALIZE-SINGLE-SOURCE é chamado.
       s.d = 0, t.d = INF, x.d = INF, y.d = INF, z.d = INF.
       s.p = NIL, t.p = NIL, x.p = NIL, y.p = NIL, z.p = NIL.
       S = vazio.
       Q = {s(0), t(INF), x(INF), y(INF), z(INF)}.
       Os valores entre parênteses representam v.d.

    Iteração 1:
       EXTRACT-MIN extrai s (s.d = 0); S = {s}.
       Relaxa (s, t), peso 10: INF > 0 + 10 = 10.
           t.d = 10, t.p = s.
       Relaxa (s, y), peso 5: INF > 0 + 5 = 5.
           y.d = 5, y.p = s.
       Q = {y(5), t(10), x(INF), z(INF)}.

    b) Estado após Iteração 1:
       s.d = 0, t.d = 10, x.d = INF, y.d = 5, z.d = INF.
       s.p = NIL, t.p = s, x.p = NIL, y.p = s, z.p = NIL.
       S = {s}; Q = {y(5), t(10), x(INF), z(INF)}.

    Iteração 2:
       EXTRACT-MIN extrai y (y.d = 5); S = {s, y}.
       Relaxa (y, t), peso 3: 10 > 5 + 3 = 8.
           t.d = 8, t.p = y.
       Relaxa (y, x), peso 9: INF > 5 + 9 = 14.
           x.d = 14, x.p = y.
       Relaxa (y, z), peso 2: INF > 5 + 2 = 7.
           z.d = 7, z.p = y.
       Q = {z(7), t(8), x(14)}.

    c) Estado após Iteração 2:
       s.d = 0, t.d = 8, x.d = 14, y.d = 5, z.d = 7.
       s.p = NIL, t.p = y, x.p = y, y.p = s, z.p = y.
       S = {s, y}; Q = {z(7), t(8), x(14)}.

    Iteração 3:
       EXTRACT-MIN extrai z (z.d = 7); S = {s, y, z}.
       Relaxa (z, x), peso 6: 14 > 7 + 6 = 13.
           x.d = 13, x.p = z.
       Relaxa (z, s), peso 7: s.d = 0 <= 7 + 7 = 14.
           Nenhuma mudança; s já está em S e sua distância é final.
       Q = {t(8), x(13)}.

    d) Estado após Iteração 3:
       s.d = 0, t.d = 8, x.d = 13, y.d = 5, z.d = 7.
       s.p = NIL, t.p = y, x.p = z, y.p = s, z.p = y.
       S = {s, y, z}; Q = {t(8), x(13)}.

    Iteração 4:
       EXTRACT-MIN extrai t (t.d = 8); S = {s, y, z, t}.
       Relaxa (t, x), peso 2: 13 > 8 + 2 = 10.
           x.d = 10, x.p = t.
       Q = {x(10)}.

    e) Estado após Iteração 4:
       s.d = 0, t.d = 8, x.d = 10, y.d = 5, z.d = 7.
       s.p = NIL, t.p = y, x.p = t, y.p = s, z.p = y.
       S = {s, y, z, t}; Q = {x(10)}.

    Iteração 5:
       EXTRACT-MIN extrai x (x.d = 10); S = {s, y, z, t, x}.
       Não há arestas saindo de x neste exemplo; Q fica vazio.

    f) Estado Final:
       s.d = 0, t.d = 8, x.d = 10, y.d = 5, z.d = 7.
       s.p = NIL, t.p = y, x.p = t, y.p = s, z.p = y.
       S = {s, y, z, t, x}; Q = vazio.

O algoritmo termina quando Q está vazio. Os valores v.d representam
os pesos dos caminhos mínimos da fonte s para cada vértice v;
v.p permite reconstruir esses caminhos.

5. Dicas de Implementação

a. Representação do Grafo:
    - Utilize uma matriz de adjacências alocada dinamicamente.
    - Um grafo com N vértices é representado por int** adj_matrix,
      uma matriz N x N.
    - adj_matrix[i][j] armazena o peso da aresta de i para j.
    - Na entrada, 0 significa ausência de aresta direta e é convertido
      internamente para INFINITO. Arestas existentes devem ter pesos
      estritamente positivos.
    - Vértices são indexados de 0 a N-1.
    - NO_PREDECESSOR indica ausência de predecessor conhecido, marcando
      vértices ainda não alcançados ou sem predecessor estabelecido.

b. Estrutura para Vértices e Caminhos:
    typedef struct {
        int dist;     // Distância mínima atual da fonte até este vértice
        int prev;     // Predecessor no caminho mínimo atual
        int id;       // Identificador único: 0 a N-1
        int in_queue; // TRUE se ainda está na fila; FALSE se processado
    } Vertice;

    Aloque dinamicamente um array de Vertice, por exemplo
    Vertice* vertices_info, para gerenciar todos os vértices.

c. Fila de Prioridades (Array Simples):
    - extract_min: percorre vertices_info e seleciona o índice i
      com in_queue == TRUE e menor dist. Depois da seleção,
      define vertices_info[i].in_queue como FALSE.
    - DECREASE-KEY: não precisa de função explícita. Quando relax
      atualiza vertices_info[v].dist, a mudança fica no array;
      extract_min considerará o novo valor na próxima iteração.

d. Reconstrução do Caminho:
    - Comece no destino dest e adicione-o a um array temporário.
    - Vá para vertices_info[dest].prev.
    - Repita até chegar à fonte s, cujo prev é NO_PREDECESSOR.
    - O caminho é construído de trás para frente: inverta-o para a saída.

e. Funções Auxiliares Recomendadas:
    initialize_single_source(Vertice* vertices, int N, int source)
        Inicializa os dados dos vértices.
    relax(Vertice* vertices, int u_id, int v_id, int weight)
        Atualiza distâncias e predecessores.
    extract_min(Vertice* vertices, int N)
        Encontra e retorna o próximo vértice a processar.
    dijkstra(int** adj_matrix, int N, int source, int destination,
             Vertice* vertices)
        Implementa o algoritmo principal.
    print_path(Vertice* vertices, int source, int destination, int N)
        Imprime o caminho e a distância.

f. Constantes:
    - TRUE = 1 e FALSE = 0.
    - INFINITO: inteiro grande, por exemplo 999999999, para distâncias
      inatingíveis. Deve ser maior que qualquer soma possível de pesos
      de arestas no grafo.
    - NO_PREDECESSOR = -1.

6. Formato de Entrada e Saída

Entrada pelo teclado:
    1. Número de vértices N (inteiro).
    2. Matriz N x N: N linhas com N inteiros cada. adj[i][j] é o peso
       de i para j. Zero significa ausência de aresta e será convertido
       internamente para INFINITO. Pesos existentes são positivos.
    3. Vértice de origem (fonte), inteiro de 0 a N-1.
    4. Vértice de destino, inteiro de 0 a N-1.

Saída:
    1. Distância mínima da fonte ao destino. Se não for alcançável,
       imprima "Destino inatingível" (na tabela de exemplos do Moodle,
       a mensagem está sem acento: "Destino inatingivel").
    2. Caminho mínimo, listando os vértices em ordem. Se o destino
       for inatingível, não imprima o caminho.

7. Tabela de Casos de Uso

Exemplo 1 - Entrada (rótulos da tabela omitidos):
    5
    0 10 3 0 0
    0 0 1 2 0
    0 4 0 8 2
    0 0 0 0 5
    1 0 0 0 0
    0
    4
Saída esperada:
    Distancia minima de 0 para 4: 5
    Caminho: 0 -> 2 -> 4

Exemplo 2 - Entrada:
    4
    0 1 0 0
    0 0 1 0
    0 0 0 1
    0 0 0 0
    0
    3
Saída esperada:
    Distancia minima de 0 para 3: 3
    Caminho: 0 -> 1 -> 2 -> 3

Exemplo 3 - Entrada:
    3
    0 5 0
    0 0 0
    0 0 0
    0
    2
Saída esperada:
    Destino inatingivel

Referência: Figura e definições do livro de Thomas H. Cormen,
Algoritmos: teoria e prática.
*/
