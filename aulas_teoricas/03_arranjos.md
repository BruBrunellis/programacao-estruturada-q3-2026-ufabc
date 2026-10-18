# Aula 03 - Arranjos

Transcrição organizada pelo Codex de `PE/Aulas/03_Teoria_Arranjos.pdf` (76 páginas), consultado em 18/10/2026. Acentuação, espaçamento e quebras de linha foram normalizados; cabeçalhos repetidos e contatos pessoais foram omitidos. Trechos distribuídos em vários slides foram reunidos. As figuras são descritas em texto. Os códigos preservam a lógica dos slides, inclusive limitações apontadas nas **notas de revisão do Codex**, que não fazem parte da exposição original.

Os [exercícios com dicas](../exercicios_livres/aula_teorica_03/README.md) ficam em uma lista separada, sem soluções. Nesta transcrição, o material suplementar inclui as resoluções fornecidas pelo professor em blocos recolhíveis.

## Apresentação e roteiro (p. 1-3)

Programação Estruturada, UFABC, MCTA028-15. Aula 03: Arranjos, teoria e prática.

Roteiro: vetores; declaração e organização na memória; leitura e preenchimento; vetores em funções e recursão; matrizes e funções; strings e entrada/saída; ordenação por seleção e inserção; pesquisa sequencial e binária; material suplementar.

## Arranjos e declaração de vetores (p. 4-6)

Um arranjo reúne espaços de memória do mesmo tipo sob um identificador. Cada elemento é acessado pelo nome do arranjo e por sua posição. Um vetor é uma coleção de variáveis de mesmo tipo, com posições contíguas na memória, acesso por índice inteiro e tamanho definido para aquele vetor.

```c
tipo identificador[tamanho];
```

Para um vetor de tamanho `n`, os índices válidos vão de `0` até `n - 1`. A primeira posição tem índice 0, a última tem índice `n - 1` e a i-ésima posição tem índice `i - 1`.

```c
float notas[10];
notas[5] = 9.5;
```

O índice 5 identifica a sexta posição. A figura da p. 6 usa `int d; int vetor[5]; int f;`: `vetor[3] = 10` é um acesso válido; `vetor[5] = 5` e `vetor[-1] = 1` ficam fora do vetor. A figura ilustra a possibilidade de atingir dados vizinhos ou provocar falhas difíceis de rastrear.

**Nota de revisão:** acessar fora dos limites tem comportamento indefinido. A figura não garante que `d` e `f` estarão fisicamente nas posições desenhadas, nem que o programa sempre encerrará com erro.

## Exemplo 1: preenchimento e impressão (p. 7)

O código inicializa dez posições com zero, altera o índice 1 e preenche os índices pares com o próprio índice.

```c
/* Exemplo 1 - vetor */
#include <stdio.h>

int main( ) {
    int vetor[10]; //vetor de inteiros de 10 posicoes
    int i;

    //inicializando as posicoes do vetor com zeros
    for ( i = 0; i < 10; i++ )
        vetor[ i ] = 0;

    vetor[ 1 ] = -1; //modificando o valor de uma posicao

    for ( i = 0; i < 10; i = i+2 ) //modificando valores com loop
        vetor[ i ] = i;

    for ( i = 0; i < 10; i++ ) //imprimindo os valores do vetor
        printf("%d ", vetor[ i ]);

    printf("\n");
    return 0;
}
```

Saída:

```text
0 -1 2 0 4 0 6 0 8 0
```

## Exemplo 2: leitura de notas (p. 8-9)

A constante `TAMANHO_MAX` define a capacidade. O programa lê a quantidade de notas, preenche as posições utilizadas e imprime os valores com duas casas decimais.

```c
/* Exemplo 2: Le e preenche dados no vetor */
#include <stdio.h>
#define TAMANHO_MAX 100 //define o tamanho do vetor

int main() {
    int n, i;
    float nota;
    float vetNotas[TAMANHO_MAX]; //declaracao de vetor tipo float

    printf("Digite a quantidade de notas: ");
    scanf("%d",&n);

    //verifica se n esta dentro limite do tamanho do vetor
    if ( n <= TAMANHO_MAX ) {
        for ( i = 0; i < n; i++ ) { //le n notas
            printf("Digite a nota %d: ", ( i+1 )); //orienta o usuario
            scanf("%f", &vetNotas[i]);
        }

        //imprime as notas lidas (nao e obrigatorio)
        printf("Notas lidas: ");
        for ( i = 0; i < n; i++ )
            printf("%.2f ", vetNotas[i]);

        printf("\n");
    }
    else //avisa que n e maior que o tamanho maximo
        printf("A quantidade maxima e %d\n", TAMANHO_MAX);

    return 0;
}
```

Exemplo de execução:

```text
Digite a quantidade de notas: 5
Digite a nota 1: 9.4
Digite a nota 2: 4
Digite a nota 3: 8.6
Digite a nota 4: 5
Digite a nota 5: 7.6
Notas lidas: 9.40 4.00 8.60 5.00 7.60
```

**Nota de revisão:** o original valida somente o limite superior e declara `nota` sem utilizá-la. Ao adaptar, confira o resultado de `scanf` e o limite inferior de `n` antes de usar os dados.

## Vetores como parâmetros de funções (p. 10-12)

Ao passar uma variável simples para uma função, seu valor inicializa um parâmetro local. Passar um vetor não cria uma cópia de todos os elementos; a função pode modificar o vetor original. Um vetor não pode ser o tipo de retorno direto de uma função em C; preencher um vetor recebido permite produzir um resultado com vários elementos.

O exemplo separa leitura e impressão:

```c
/* Exemplo 3: modifica o exemplo 2 */
/* Funcoes le e imprime dados com vetor */
#include <stdio.h>
#define TAMANHO_MAX 100 //define o tamanho do vetor

void leVetor(float vetor[], int tamanho);
void imprimeVetor(float vetor[], int tamanho);

int main() {
    int n;
    float vetNotas[TAMANHO_MAX]; //declaracao de vetor tipo float

    printf("Digite a quantidade de notas: ");
    scanf("%d",&n);

    //verifica se n esta dentro limite do tamanho do vetor
    if ( n <= TAMANHO_MAX ) {
        leVetor( vetNotas, n );  //le n notas
        printf("\nNotas lidas:\n");
        imprimeVetor( vetNotas, n ); //imprime as notas lidas
    }
    else //avisa que n e maior que o tamanho maximo
        printf("A quantidade maxima e %d\n", TAMANHO_MAX);

    return 0;
}

void leVetor(float vetor[], int tamanho) {
    int i;
    for ( i = 0; i < tamanho; i++ ) {
        printf("Digite a nota %2d: ", ( i + 1 ));
        scanf("%f", &vetor[ i ]);
    }
}

void imprimeVetor(float vetor[], int tamanho) {
    int i;
    for ( i = 0; i < tamanho; i++ )
        printf("nota %2d = %.2f\n", ( i + 1 ), vetor[ i ]);
}
```

**Nota de revisão:** em um parâmetro, `float vetor[]` é ajustado para um ponteiro. O ponteiro também é passado por valor; os elementos são acessados por meio dele. Passe separadamente o tamanho que a função deve percorrer.

## Vetores e recursão (p. 13-14)

É possível usar recursão para somar elementos de um vetor. A relação apresentada é:

```text
soma(v, 0) = v[0]
soma(v, n) = v[n] + soma(v, n - 1), para n > 0
```

Nesse exemplo, `n` representa o **último índice**, e não a quantidade de elementos. Para um vetor de tamanho `tam`, a chamada inicial é `soma(v, tam - 1)`.

```c
/* Exemplo 4: soma recursiva  */
#include <stdio.h>

int soma(int v[], int n);

int main() {
    int v[5] = {4, 3, 6, 2, 5};
    printf("Soma: %d\n", soma( v, 4 ));
    return 0;
}

int soma(int v[], int n){
    if ( n == 0 )
        return v[0];
    else
        return v[n] + soma( v, ( n - 1 ) );
}
```

O vetor `{4, 3, 6, 2, 5}` produz `Soma: 20`.

**Nota de revisão:** a versão pressupõe um vetor não vazio, índice válido e soma representável em `int`.

## Exercícios de vetores (p. 15)

1. Ler dois vetores de tamanho `n` e computar o produto interno (produto escalar).
2. Ler dois vetores com `n` inteiros cada e verificar quais elementos do segundo são iguais a algum elemento do primeiro. Informar se não houver elementos em comum.
3. Escrever um programa com uma função recursiva que encontre o maior elemento de um vetor de inteiros.

Veja os [enunciados com dicas e testes](../exercicios_livres/aula_teorica_03/README.md).

## Matrizes e passagem para funções (p. 16-19)

Matrizes representam tabelas organizadas em linhas e colunas. Por convenção, o primeiro índice identifica a linha e o segundo identifica a coluna.

```c
int a[3][4];
```

A figura da p. 16 mostra três linhas, de 0 a 2, e quatro colunas, de 0 a 3. Cada posição é identificada por `a[i][j]`.

Para um vetor unidimensional, o tamanho pode ser omitido na declaração do parâmetro. No exemplo de matriz, a função recebe linhas com 10 colunas:

```c
void imprimeMatriz(int matriz[][10], int linhas);
```

**Correção de redação da p. 17:** o texto do slide diz “primeira dimensão”, mas o próprio protótipo informa a **segunda dimensão**, o número de colunas. Ela permite calcular o deslocamento entre linhas. O número de linhas utilizado é passado em outro parâmetro.

Exemplo completo, reunindo as p. 18-19:

```c
/* Exemplo 5: ler e imprimir uma matriz */
#include <stdio.h>
#define MAX_LINHAS  20
#define MAX_COLUNAS 20

void leMatriz(int matriz[][MAX_COLUNAS], int nLinhas, int nColunas);
void imprimeMatriz(int matriz[][MAX_COLUNAS], int nLinhas, int nColunas);

int main() {
    int matriz[MAX_LINHAS][MAX_COLUNAS];
    leMatriz(matriz, 2, 2);
    imprimeMatriz(matriz, 2, 2);
    return 0;
}

void leMatriz(int matriz[][MAX_COLUNAS], int nLinhas, int nColunas){
    int i, j;
    for ( i = 0; i < nLinhas; i++ )
        for ( j = 0; j < nColunas; j++ ){
        printf("Digite o valor matriz[%d][%d]: ", i, j);
        scanf("%d", &matriz[i][j]);
    }
}

void imprimeMatriz(int matriz[][MAX_COLUNAS], int nLinhas, int nColunas){
    int i, j;
    for ( i = 0; i < nLinhas; i++ ) {
        for ( j = 0; j < nColunas; j++ )
            printf("%-3d ", matriz[i][j]);
        printf("\n");
    }
}
```

Para entradas `1`, `2`, `3`, `4`, a impressão é:

```text
1 2
3 4
```

## Exercícios de matrizes (p. 20-21)

**4. Multiplicação:** escrever um programa para multiplicar `A`, de dimensões `m × n`, por `B`, de dimensões `n × p`. O resultado `C` tem dimensões `m × p`:

```text
c[i,j] = soma de a[i,k] * b[k,j], para k de 1 até n
1 <= i <= m; 1 <= j <= p
```

Os índices acima seguem a notação matemática do slide; em C, começam em zero.

**5. Transposição:** implementar a transposição de uma matriz quadrada `n × n` **in-place**, sem criar uma segunda matriz auxiliar.

```text
[a11 a12]                 [a11 a21]
[a21 a22]  transposta ->  [a12 a22]
```

## Strings em C (p. 22-23)

C não tem um tipo básico específico chamado `string`. Uma string é representada por uma sequência de caracteres terminada por `\0`. Reserve uma posição adicional para esse terminador; para dez caracteres de conteúdo, use capacidade 11:

```c
char texto[11];
```

Exemplo:

```c
#include <stdio.h>

int main() {
    char st[80];
    st[0] = 'o';
    st[1] = 'l';
    st[2] = 'a';
    st[3] = '\0';
    printf("%s\n", st);
    return 0;
}
```

Saída: `ola`. O slide ilustra que, sem o terminador, podem aparecer caracteres adicionais como `ola8u`.

**Nota de revisão:** essa saída extra não é garantida. Se `%s` continuar lendo além da região válida por falta de `\0`, ocorre comportamento indefinido.

## Leitura, escrita e inicialização de strings (p. 24-26)

O formato `%s` permite ler e imprimir strings. Na leitura de um vetor de caracteres, não se coloca `&` antes do identificador. `scanf` acrescenta `\0` e a conversão `%s` termina ao encontrar espaço em branco, incluindo espaços e quebras de linha.

Exemplo da p. 24:

```c
#include <stdio.h>

int main() {
    char st[80];
    printf("Digite uma palavra: ");
    scanf("%s", st);
    printf("%s", st);
    return 0;
}
```

**Nota de revisão:** o `%s` sem largura do original pode ultrapassar o vetor. Para esse tamanho, limite a conversão a `%79s` e confira o retorno de `scanf`.

Para ler uma linha incluindo espaços, o material apresenta `fgets(identificador, limite, stdin)`:

```c
#include <stdio.h>

int main() {
    char st[80];
    printf("Digite uma frase: ");
    fgets(st, 80, stdin);
    printf("%s", st);
    return 0;
}
```

**Notas de revisão da p. 25:** `fgets` lê no máximo `limite - 1` caracteres e acrescenta `\0` quando a leitura tem sucesso. Pode guardar `\n` se ele couber. Verifique o retorno antes de usar a string. `stdin` identifica a entrada padrão por meio de uma macro de `stdio.h`; não é uma palavra reservada da linguagem.

É possível inicializar um vetor com um literal:

```c
char texto[100] = "ola mundo!";
```

O terminador é incluído nessa inicialização. Depois de declarado, um vetor não recebe outra string por atribuição com `=`; é preciso copiar os caracteres, por exemplo com uma função apropriada.

## Biblioteca `string.h` (p. 27)

O material apresenta funções para concatenar, comparar, copiar e medir strings:

```c
char *strcat(char *s1, const char *s2);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *s1, const char *s2);
size_t strlen(const char *s1);
```

**Correção explícita:** o slide escreve retorno `int` para `strlen`; o tipo correto é `size_t`. A lista acima é uma forma simplificada das declarações, com essa correção. `strlen` não conta `\0`. `strcmp` informa a ordem lexicográfica pelo sinal do retorno. Em `strcpy` e `strcat`, o destino precisa ter capacidade suficiente, incluindo o terminador.

## Exercício de strings (p. 28)

**6. Contagem de palavras:** fazer um programa que conte o número de palavras em um texto de tamanho no máximo 100. Lembretes: fim da string `\0`; quebra de linha `\n`.

## Fundamentos de ordenação (p. 29-32)

Ordenar é rearranjar objetos em ordem crescente ou decrescente, facilitando sua recuperação posterior. A aula cita dicionários, índices de livros, tabelas e arquivos, além do processamento comercial e científico. Como contexto histórico, o material menciona que até 30% dos ciclos de computação eram gastos em ordenação; essa é uma afirmação do slide, sem fonte indicada ali.

Critérios para comparar métodos:

- **Estabilidade:** preserva a ordem relativa de itens com chaves iguais. Se nomes já estiverem em ordem alfabética, uma ordenação estável por salário mantém essa ordem entre funcionários com o mesmo salário. O material cita inserção e mergesort como estáveis; seleção, Shellsort, quicksort e heapsort como não estáveis em suas versões usuais.
- **Complexidade de tempo:** quantidade de comparações e movimentações. A aula contrasta métodos simples de ordem `O(n²)` com métodos eficientes de ordem `O(n log n)`.
- **Memória adicional:** espaço extra utilizado para ordenar. Métodos in-place reorganizam o próprio vetor; estruturas auxiliares, inclusive a pilha de recursão, também devem ser consideradas na análise.
- **Ordenação interna:** os dados cabem na memória principal. **Externa:** os dados não cabem nela e são acessados em disco/fita, sequencialmente ou em blocos.
- **Adaptatividade:** aproveitamento de uma entrada já parcialmente ordenada, como na ordenação por inserção.

## Ordenação por seleção - Selection Sort (p. 33-37)

Selecione o menor elemento e troque-o com o da primeira posição. Repita com os elementos restantes até restar apenas um. O método apresentado tem tempo `O(n²)` e não é estável.

```c
/* Pré: vetor de inteiros a[] e n sendo tamanho do vetor */
/* Pós: vetor a[] ordenado */
void selectionSort(int a[], int n) {
    int i, j, min, temp;

    for ( i = 0; i < n - 1; i++ ) {
        min = i;
        /* Seleciona o menor item */
        for ( j = i + 1; j < n; j++ ) {
            if ( a[j] < a[min] ) {
                min = j;
            }
        }
        /* Troca a[i] com a[min] */
        temp   = a[i];
        a[i]   = a[min];
        a[min] = temp;
    }
}
```

A figura da p. 35 acompanha o vetor após cada troca: o prefixo já colocado em ordem cresce uma posição por passagem. O exemplo das p. 36-37 usa caracteres:

```c
/* Exemplo 6: Select Sort  */
#include <stdio.h>
#include <string.h>

void imprime(char a[], int n);
void selectionSort(char a[], int n);
void troca(char a[], int i, int min);

int main() {
    char palavra[] = "SORTEXAMPLE";
    int tamanho = (int) strlen(palavra);

    imprime(palavra, tamanho);
    selectionSort(palavra, tamanho);
    imprime(palavra, tamanho);

    return 0;
}

void imprime(char a[], int n){
    int i;

    for ( i = 0; i < n; i++ )
        printf("%c ", a[i]);
    printf("\n");
}
void selectionSort(char a[], int n) {
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        troca(a, i, min);
    }
}
void troca(char a[], int i, int min){
    char temp = a[i];
    a[i] = a[min];
    a[min] = temp;
}
```

Saída:

```text
S O R T E X A M P L E
A E E L M O P R S T X
```

## Ordenação por inserção - Insertion Sort (p. 38-40)

Em cada passo, retire um item e insira-o na posição adequada entre os elementos já considerados. Os maiores são deslocados para a direita, preservando o prefixo ordenado.

O material destaca `O(n²)` comparações e movimentações no pior caso, com ordem inversa, e `O(n)` no melhor caso, quando a entrada já está ordenada. O método é estável e adequado para entradas pequenas ou quase ordenadas.

```c
/* Pré: vetor de inteiros a[] e n tamanho do vetor */
/* Pós: vetor a[] ordenado */
void insertionSort(int a[], int n) {
    int i, j, key;

    for ( i = 1; i < n; i++ ) {
        key = a[i];
        j = i - 1;

        /* Insere a[i] na sequência ordenada a[0 .. i-1] */
        while ( j >= 0 && a[j] > key ) { /*  Desloca os maiores que key uma posição à direita */
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;  /* Insere a key na posição correta */
    }
}
```

A figura da p. 40 mostra o estado após cada inserção. O teste `a[j] > key`, sem incluir igualdade, mantém a ordem relativa dos elementos iguais. O suplemento traz um rastreamento textual completo com `SORTEXAMPLE`.

## Pesquisa sequencial (p. 41-44)

A pesquisa começa no primeiro registro e percorre a lista até encontrar a chave. Em uma tabela de registros, uma chave identifica a informação pesquisada. No exemplo com inteiros, cada elemento é a própria chave; o resultado é um índice.

Análise apresentada:

- Busca sem sucesso: `N` comparações.
- Busca com sucesso: uma comparação no melhor caso e `N` no pior.
- Média: `(N + 1) / 2`, se todas as posições forem igualmente prováveis.
- Inserir `N` chaves distintas com uma busca prévia para cada inserção pode exigir aproximadamente `N² / 2` comparações.

```c
/*Pré: vetor de inteiros A, n o tamanho do vetor e valor a chave a ser pesquisada */
/*Pós: retorna o índice da primeira ocorrência da chave ou -1 quando a chave não for encontrada */

int busca_sequencial(int A[], int n, int valor) {
    for (int i = 0; i < n; i++) {
        if (A[i] == valor) {
            return i; // Retorna o índice do vetor
        }
    }
    return -1; // Não encontrou
}
```

O código retorna a primeira ocorrência ou `-1`. A descrição genérica da p. 42 fala em retornar um valor associado ou nulo; esse não é o contrato desta implementação, que retorna índices.

## Pesquisa binária (p. 45-48)

Exige dados ordenados. Compare a chave ao elemento central; se for menor, continue na metade anterior; se for maior, na posterior. Repita até encontrar a chave ou esvaziar o intervalo.

```c
/* Pré: vetor A em ordem crescente, n o tamanho do vetor e valor a chave a ser pesquisada  */
/* Pós: retorna o índice da primeira ocorrência da chave ou -1 quando a chave não for encontrada */
int busca_binaria(int A[], int n, int valor) {
    int ini = 0;
    int fim = n - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (A[meio] == valor) {
            return meio;
        }
        else if (A[meio] < valor) {
            ini = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }
    return -1; // Não encontrado
}
```

Na figura da p. 46, o vetor é `A C E H L M P R S X`. A busca por `P` examina os índices centrais 4, 7, 5 e 6, encontrando o índice 6. A busca por `Q` termina sem correspondência; a figura apresenta a posição de inserção 7.

**Divergências do original:**

- O texto da p. 46 diz que a ausência retorna o índice de um número menor; a figura usa a posição de inserção, e o código da p. 47 retorna `-1`.
- O comentário do código promete a primeira ocorrência. A implementação retorna uma ocorrência encontrada, sem garantir a primeira quando há duplicatas.
- Para evitar estouro na soma de índices grandes, uma adaptação pode calcular o meio como `ini + (fim - ini) / 2`.

A cada iteração, o intervalo é aproximadamente dividido por 2: o número de iterações é de ordem `log₂ N`. O slide estima `log N + 1` comparações. Manter o vetor ordenado pode custar caro: inserir em uma posição interna exige deslocar o sufixo. O material estima cerca de `2N` acessos no pior caso por inserção e `N²` para inserir `N` chaves no pior caso.

## Material suplementar (p. 49-74)

As resoluções abaixo pertencem ao PDF. A lógica original foi preservada; consulte as notas antes de reutilizar os programas. Blocos com `main` são programas separados e não devem ser reunidos em um único arquivo.

### Solução do exercício 1: produto escalar (p. 50-51)

<details>
<summary>Código do professor</summary>

```c
/* Exercicio 1: produto escalar */
#include <stdio.h>
#define TAMANHO_MAX 100 //define o tamanho do vetor

void leVetor(double vetor[], int tamanho);
double produtoEscalar(double vetorA[],  double vetorB[], int tamanho);

int main() {
    int n;
    double resultado;
    //declaracao de vetores tipo double
    double  vetA[TAMANHO_MAX], vetB[TAMANHO_MAX];
    printf("Digite n: ");
    scanf("%d",&n);

    //verifica se n esta dentro limite do tamanho do vetor
    if ( n <= TAMANHO_MAX ) {
        printf("\nDigite os valores do vetor 1:\n");
        leVetor( vetA, n );  //le n valores do primeiro vetor

        printf("\nDigite os valores do vetor 2:\n");
        leVetor( vetB, n );  //le n valores do segundo vetor

        resultado = produtoEscalar(vetA, vetB, n);
        printf("\nO produto escalar e: %lf\n", resultado);
    }
    else //avisa que n e maior que o tamanho maximo
        printf("n maximo e %d\n", TAMANHO_MAX);
    return 0;
}

void leVetor(double vetor[], int tamanho) {
    int i;
    for ( i = 0; i < tamanho; i++ ) {
        printf("Digite o valor %2d: ", ( i + 1 ));
        scanf("%lf", &vetor[ i ]);
    }
}

double produtoEscalar(double vetorA[], double vetorB[], int tamanho) {
    int i;
    double produto = 0.0;
    for ( i = 0; i < tamanho; i++ )
        produto = produto + ( vetorA[ i ] * vetorB[ i ] );
    return produto;
}
```

</details>

O acumulador começa em `0.0`; cada parcela multiplica posições correspondentes. A validação original verifica apenas `n <= 100`.

### Solução do exercício 2: elementos iguais (p. 52-54)

<details>
<summary>Código do professor</summary>

```c
/* Exercicio 2: elementos iguais */
#include <stdio.h>

#define TRUE  1
#define FALSE 0
#define TAMANHO_MAX 100 //define o tamanho do vetor

void leVetor(int vetor[], int tamanho);
int comparaVetores(int vetorA[], int tamanhoA, int vetorB[], int tamanhoB);

int main() {
    int tamA, tamB;

    //declaracao de vetores tipo int
    int  vetA[TAMANHO_MAX], vetB[TAMANHO_MAX];

    printf("Digite o tamanho do vetor A: ");
    scanf("%d",&tamA);

    printf("Digite o tamanho do vetor B: ");
    scanf("%d",&tamB);

    if ( tamA <= TAMANHO_MAX && tamB <= TAMANHO_MAX ) {
        printf("\nDigite os valores do vetor 1:\n");
        leVetor( vetA, tamA );  //le valores do primeiro vetor

        printf("\nDigite os valores do vetor 2:\n");
        leVetor( vetB, tamB );  //le valores do segundo vetor

        if ( comparaVetores( vetA, tamA, vetB, tamB ) == FALSE )
            printf("\nOs vetores nao possuem elementos iguais\n") ;
    }
    else //avisa que tamanho e maior que o tamanho maximo
        printf("Tamanho maximo e %d\n", TAMANHO_MAX);

    return 0;
}

void leVetor(int vetor[], int tamanho) {
    int i;

    for ( i = 0; i < tamanho; i++ ) {
        printf("Digite o valor %2d: ", ( i + 1 ));
        scanf("%d", &vetor[ i ]);
    }
}

int comparaVetores(int vetorA[], int tamanhoA,  int vetorB[], int tamanhoB) {
    int i, j;
    int elementoComum = FALSE; //false para nenhum elemento em comum

    for ( i = 0; i < tamanhoA; i++ ) //percorre vetorA
        for ( j = 0; j < tamanhoB; j++) { //percorre vetorB
        if ( vetorA[ i ] == vetorB[ j ] ) { //encontrou elemento em comum
            printf("A[%d] = B[%d] = %d\n", i, j, vetorA[ i ]);
            elementoComum = TRUE;
        }
    }

    return elementoComum;
}
```

</details>

O suplemento lê tamanhos independentes, embora o enunciado use o mesmo `n`. Imprime todos os pares de índices com valores iguais; duplicatas podem produzir várias linhas. `comparaVetores` indica se encontrou ao menos uma igualdade.

### Solução do exercício 3: maior elemento (p. 55)

<details>
<summary>Código do professor</summary>

```c
/* Exercicio 4: maior elemento do vetor   */
#include <stdio.h>

int maiorElementoVetor(int vetor[], int i);

int main() {
    int v[] = {1, 4, 5, 8, 2, 3};
    printf("%d\n", maiorElementoVetor( v, 5 ));
    return 0;
}

int maiorElementoVetor(int vetor[], int i){
    int maior;

    if ( i == 0 ) return vetor[0];

    maior =  maiorElementoVetor(vetor, ( i - 1 ));
    if ( vetor[i] > maior )
        return vetor[i];
    else
        return maior;
}
```

</details>

Para o vetor apresentado, o resultado é `8`. O parâmetro `i` é o último índice. O comentário inicial chama este de “Exercício 4”; trata-se do exercício 3 da p. 15.

### Solução do exercício 4: multiplicação de matrizes (p. 56-59)

<details>
<summary>Código do professor</summary>

```c
#include <stdio.h>
#define MAX_ROW 30
#define MAX_COL 30

void multiplicaMatriz(int A[][MAX_COL], int B[][MAX_COL], int C [][MAX_COL], int m, int n, int p);
void imprimeMatriz(int matriz[][MAX_COL], int linha, int coluna);
void leMatriz(int matriz[][MAX_COL], int linha, int coluna);

int main() {
    int A[MAX_ROW][MAX_COL];
    int B[MAX_ROW][MAX_COL];
    int C[MAX_ROW][MAX_COL];
    int linhaA, colunaA, linhaB, colunaB;

    scanf("%d %d", &linhaA, &colunaA);
    leMatriz(A, linhaA, colunaA);
    printf("Matriz A\n");
    imprimeMatriz(A, linhaA, colunaA);

    scanf("%d %d", &linhaB, &colunaB);
    leMatriz(B, linhaB, colunaB);
    printf("Matriz B\n");
    imprimeMatriz(B, linhaB, colunaB);

    if (colunaA == linhaB)
        multiplicaMatriz(A, B, C, linhaA, colunaA, colunaB);
    printf("Matriz C\n");
    imprimeMatriz(C, linhaA, colunaB);

    return 0;
}

void leMatriz(int matriz[][MAX_COL], int linha, int coluna){
    int i, j;
    for ( i = 0; i < linha; i++ )
        for ( j = 0; j < coluna; j++ )
            scanf("%d", &matriz[i][j]);
}

void multiplicaMatriz(int A[][MAX_COL], int B[][MAX_COL], int C [][MAX_COL], int m, int n, int p){
    int i, j, k;

    for ( i = 0; i < m; i++ ){
        for ( j = 0; j < p; j++ ){
            int soma = 0;
            for ( k = 0; k < n; k++ )
                soma +=  A[ i ][ k ] * B[ k ][ j ];
            C[ i ][ j ] = soma;
        }
    }
}

void imprimeMatriz(int matriz[][MAX_COL], int linha, int coluna){
    int i, j;

    for ( i = 0; i < linha; i++ ){
        for ( j = 0; j < coluna; j++)
            printf("%3d ", matriz[ i ][ j ]);
        printf("\n");
    }
}
```

</details>

Exemplo do slide:

```text
Matriz A       Matriz B       Matriz C
 2 3           1 2 3         -4  4 18
 0 1          -2 0 4         -2  0  4
-1 4                        -9 -2 13
```

**Nota de revisão:** no original, somente a chamada a `multiplicaMatriz` está condicionada à compatibilidade. A impressão de `C` ocorre mesmo se a multiplicação não acontecer. Uma adaptação deve impedir essa leitura de valores não inicializados e validar as dimensões antes de preencher matrizes de capacidade `30 × 30`.

### Solução do exercício 5: transposição (p. 60-61)

<details>
<summary>Código do professor</summary>

```c
#include <stdio.h>
#define MAX_ROW 3
#define MAX_COL 3

void matrizTransposta(int A[][MAX_COL], int linha, int coluna);

int main() {

    int A[MAX_ROW][MAX_COL] = {{1,2,3},
        {4,5,6},
        {7,8,9}};

    matrizTransposta(A, 3, 3);

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    return 0;
}

void matrizTransposta(int A[][MAX_COL], int linha, int coluna){
    int i, j, temp;

    for ( i = 0; i < linha; i++ ){
        for( j = i; j < coluna; j++ ){
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}
```

</details>

Saída:

```text
1 4 7
2 5 8
3 6 9
```

O laço percorre a diagonal e um dos triângulos. Trocar cada posição da diagonal consigo mesma é desnecessário, mas não altera o resultado. O algoritmo pressupõe matriz quadrada.

### Solução do exercício 6: contagem de palavras (p. 62-64)

<details>
<summary>Código do professor</summary>

```c
/* Exercicio 6: conta palavras do texto */
#include <stdio.h>

int contaPalavras(char texto[], int tamanho);

int main() {
    char texto[100];

    fgets(texto, 100, stdin);
    printf("%s\n", texto);
    printf("Total de palavras: %d\n", contaPalavras(texto, 100));

    return 0;
}

int contaPalavras(char texto[], int tamanho){
    int i = 0, contaPalavras = 0;

    /* enquanto nao for final do texto */
    while ( texto[i] != '\n' && texto[i] != '\0' ){

        /* pula espaco */
        while ( texto[i] == ' ' )
            i++;

        /* procura o comeco de uma palavra ou fim do texto */
        if ( texto[i] != '\n' && texto[i] != '\0' ) { /* encontrou a palavra */
            contaPalavras++; /* incrementa a quantidade de palavras */

            /* passa pela palavra */
            while( texto[i] != '\n' && texto[i] != '\0' && texto[ i] != ' ' )
                i++;
        }
    }

    return contaPalavras;
}
```

</details>

O algoritmo pula espaços, identifica uma palavra e avança até o separador seguinte. A frase apresentada é “Não é a linguagem de programação que define o programador, mas sim sua lógica”, com resultado **14 palavras**. A quebra visual do texto no slide não representa uma segunda chamada de leitura.

**Nota de revisão:** o parâmetro `tamanho` não é usado; a função depende de uma string terminada. `texto[100]` não comporta 100 caracteres de conteúdo mais o terminador. Confira o retorno de `fgets` e estabeleça uma política para entradas maiores.

### Exemplo: ocorrências de uma palavra (p. 65-67)

Encontrar todas as posições iniciais de uma palavra em um texto de tamanho no máximo 100.

```text
Texto: a lala lalaland
Palavra: lala
Saída: 2 7 9
```

<details>
<summary>Código do professor</summary>

```c
/*Exemplo 1 - mostrar posicoes de ocorrencia de uma palavra */
#include <stdio.h>
#include <string.h>

#define TRUE  1
#define FALSE 0

void buscaPalavra(char palavra[], char texto[]);

int main() {
    char texto[100];
    char palavra[100];

    printf("Digite o texto: ");
    fgets(texto, 100, stdin);

    printf("Digite a palavra: ");
    fgets(palavra, 100, stdin);

    buscaPalavra(palavra, texto);

    return 0;
}

void buscaPalavra(char palavra[], char texto[]){
    int tamPalavra = strlen(palavra) - 1;
    int tamTexto   = strlen(texto) - 1; //o -1 por motivo do /n
    int i, j, iguais;

    for ( i = 0; i < tamTexto - tamPalavra; i++ ) { //percorre o texto
        /* dado i, testar se palavra ocorre a partir de i */
        j = 0;
        iguais = TRUE;

        while ( j < tamPalavra && iguais ){ //percorre a palavra
            if ( palavra[ j ] != texto[ i + j ] ) //compara palavra com palavra do texto
                iguais = FALSE;
            j++;
        }

        if ( iguais )
            printf("%d ", i); //imprime posicao
    }
    printf("\n");
}
```

</details>

**Notas de revisão:** o exemplo procura substrings e admite sobreposição. O teste `i < tamTexto - tamPalavra` perde a última posição possível; deve incluí-la em uma adaptação. Subtrair 1 de `strlen` só representa a remoção de `\n` se ele realmente estiver presente. Defina ainda o comportamento para palavra vazia e confira as leituras.

### Arranjos multidimensionais (p. 68)

A forma geral é `tipo nome_vetor[d1][d2]...[dn];`. Exemplo de armazenamento da quantidade de chuva por ano, mês e dia:

```c
double chuva[3000][12][31];
chuva[1980][8][22] = 4.5;
```

O total é `3000 × 12 × 31 = 1.116.000` posições. Se `double` ocupar 8 bytes, serão **8.928.000 bytes** (8.928 kB decimais). Os índices do exemplo são índices do vetor; a correspondência com datas precisa ser definida pelo programa.

### Exemplo de rastreamento do Insertion Sort (p. 69-71)

<details>
<summary>Código do professor e saída</summary>

```c
/* Exemplo Insertion Sort  */
#include <stdio.h>
#include <string.h>

void imprimePasso(char a[], int n, int i, int j, char key);
void insertionSort(char a[], int n);

int main() {
    char palavra[] = "SORTEXAMPLE";
    int tamanho = (int) strlen(palavra);

    insertionSort(palavra, tamanho);

    return 0;
}

void imprimePasso(char a[], int n, int i, int j, char key){
    int k;

    printf("%2d %2d  ", i , j);
    for ( k = 0; k < n; k++ )
        printf("%c ", a[k]);

    printf(" key = %c \n", key);
}

void insertionSort(char a[], int n) {
    int i, j, key;

    for ( i = 1; i < n; i++ ) {
        key = a[i];
        j = i - 1;
        while ( j >= 0 && a[j] > key ) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
        imprimePasso(a, n, i, j+1, key);
    }
}
```

```text
 1  0 O S R T E X A M P L E key = O
 2  1 O R S T E X A M P L E key = R
 3  3 O R S T E X A M P L E key = T
 4  0 E O R S T X A M P L E key = E
 5  5 E O R S T X A M P L E key = X
 6  0 A E O R S T X M P L E key = A
 7  2 A E M O R S T X P L E key = M
 8  4 A E M O P R S T X L E key = P
 9  2 A E L M O P R S T X E key = L
10  2 A E E L M O P R S T X key = E
```

</details>

### Shellsort (p. 72-74)

Shellsort estende a inserção, permitindo mover elementos distantes. Um vetor h-ordenado tem ordenadas as subsequências formadas a cada `h` posições. Reduza `h` até 1; a última passagem equivale à inserção, com os elementos já mais próximos de seus lugares finais. O método não é estável.

O material o apresenta como opção para tamanhos moderados, cita cerca de 5.000 registros e menciona `O(n log n)` na prática e pior caso `O(N^(3/2))`.

**Nota de revisão:** as afirmações de custo dependem da sequência de incrementos e do modelo de análise. Não trate `O(n log n)` como garantia geral do Shellsort nem o número de registros como limite obrigatório.

```c
void shellSort(int a[], int n) {
    int h = 1;
    // Gera o maior h da sequência
    while (h < n/3) {
        h = 3 * h + 1; // Sequência 1, 4, 13, 40, ...
    }
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = a[i];
            int j = i;
            while (j >= h && a[j - h] > temp) {
                a[j] = a[j - h];
                j -= h;
            }
            a[j] = temp;
        }
        h = h/3;
    }
}
```

O código usa incrementos `1, 4, 13, 40, ...`. Já a figura da p. 74 ilustra outra sequência, `4, 2, 1`, sobre a palavra `ORDENA`:

```text
Inicial: O R D E N A
h = 4:   N A D E O R
h = 2:   D A N E O R
h = 1:   A D E N O R
```

Na figura, as posições são numeradas de 1 a 6. Com `h = 4`, comparam-se posições 1 e 5, depois 2 e 6. Com `h = 2`, reordenam-se as subsequências das posições ímpares e pares. A passagem final usa `h = 1`.

## Pergunta final e contatos (p. 75-76)

Pergunta do professor: **como se cria um vetor de strings ou um vetor de vetores em C?** Há uma dica na [lista de exercícios](../exercicios_livres/aula_teorica_03/README.md).

A p. 76 contém contatos pessoais, omitidos desta transcrição de estudo.

[Voltar ao índice de teoria](README.md)
