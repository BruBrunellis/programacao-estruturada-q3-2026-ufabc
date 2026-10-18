# Aula 04 - Alocação dinâmica de memória

Transcrição organizada pelo Codex de `PE/Aulas/04_TEORIA_Alocacao.pdf` (60 páginas), consultado em 18/10/2026. Acentuação, espaçamento e quebras de linha foram normalizados; cabeçalhos repetidos e contatos pessoais foram omitidos. Códigos distribuídos em várias páginas foram reunidos e figuras foram descritas em texto. A lógica dos exemplos foi preservada. **Notas de revisão do Codex** distinguem correções e cuidados adicionais do conteúdo original.

Os [enunciados com dicas](../exercicios_livres/aula_teorica_04/README.md) estão separados das resoluções. O material suplementar desta transcrição inclui as soluções do professor em blocos recolhíveis. Cada bloco com `main` corresponde a um programa independente.

## Apresentação e roteiro (p. 1-3)

Programação Estruturada, UFABC, MCTA028-15. Aula 04: Alocação dinâmica de memória, teoria e prática.

Roteiro: ponteiros; passagem de argumentos por referência simulada; relação entre ponteiros e vetores; alocação dinâmica de vetores e matrizes; material suplementar.

## Ponteiros e seus operadores (p. 4-6)

Ponteiros armazenam endereços e permitem acessar valores indiretamente, modificar objetos da função chamadora e manipular estruturas dinâmicas que podem crescer ou encolher durante a execução.

Declaração:

```c
tipo *nome_variavel;
```

Operadores apresentados:

- `&`: operador unário de endereço, que obtém o endereço de seu operando.
- `*`: operador unário de desreferenciação, que permite acessar o objeto apontado.
- `NULL`: valor usado para indicar que um ponteiro não aponta para um objeto.

**Nota de revisão:** comparar um ponteiro com `NULL` identifica o valor nulo, mas um ponteiro diferente de `NULL` ainda pode ser inválido, estar fora dos limites ou apontar para memória já liberada.

```c
/* Exemplo 1: */
/* Operadores de Ponteiros*/
#include <stdio.h>

int main() {
    int varInteiro;

    // ponteiro para um inteiro
    int *ponteiroVarInteiro;

    varInteiro = 80;

    // atribui o endereco de varInteiro
    ponteiroVarInteiro = &varInteiro;

    printf( "O valor de *ponteiroVarInteiro e %d\n", * ponteiroVarInteiro );
    return 0;
}
```

Saída apresentada: `O valor de *ponteiroVarInteiro e 80`.

A figura da p. 6 distingue a variável `varInteiro`, cujo conteúdo passa a ser 80, da variável ponteiro, que recebe o endereço de `varInteiro`. O acesso `*ponteiroVarInteiro` chega ao valor por meio desse endereço.

## Erros comuns com ponteiros (p. 7-8)

Os trechos abaixo são exemplos **incorretos** apresentados para análise.

Ponteiro não inicializado:

```c
int a;
int *c;
a = 10;
*c = 13; /* Erro: c ainda nao aponta para um objeto valido. */
```

Confusão entre multiplicação e desreferenciação:

```c
int a, b = 5;
int *c;
c = &a;
*c = 13;
a = b * c; /* Incorreto: multiplica um inteiro por um ponteiro. */
```

O material propõe `a = b * (*c);` quando a intenção é multiplicar pelo valor apontado.

O asterisco da declaração não se aplica automaticamente a todos os identificadores:

```c
int *a, b, c;  /* Somente a e ponteiro. */
float *x, *y;  /* x e y sao ponteiros. */
```

Tipos incompatíveis e confusão entre endereço e conteúdo:

```c
int *a;
double b;
b = 12.34;
a = &b; /* Tipos incompatíveis: int * e double *. */
```

```c
double a = 12.34;
double *b = &a;
b = 22.80; /* Incorreto: atribui um double a um ponteiro. */
```

A sugestão didática é identificar ponteiros pelo nome, por exemplo `bPtr`, e usar `*bPtr = 22.80;` para alterar o valor apontado.

**Nota de revisão:** `b * c` com `c` ponteiro e a atribuição de `double` a ponteiro são violações que exigem diagnóstico do compilador; não são operações válidas sobre um suposto endereço numérico.

## Comparação de ponteiros e valores reais (p. 9-10)

O exemplo contrasta comparar endereços com comparar os valores apontados e ilustra arredondamento em ponto flutuante:

```c
/* Exemplo 2 - Comparacao de Ponteiros e Float e Double */
#include <stdio.h>

int main(){
    double a = 100,  b = 0.1,  c = 0.2, r1 = 0 , r2 = 0;
    double  *r1Ptr = NULL, *r2Ptr = NULL;

    //distributiva
    r1 = a * b + a * c;
    r2 = a * (b + c);

    r1Ptr = &r1;
    r2Ptr = &r2;

    //CUIDADO com a comparacao de igualdade entre floats e/ou doubles
    if ( *r1Ptr == *r2Ptr )
        printf("r1 e r2 sao iguais\n");
    else
        printf("r1 e r2 sao diferentes, r1 = %lf e r2 = %lf\n", r1, r2);

    //comparacao entre enderecos de ponteiros
    if ( r1Ptr < r2Ptr ){
        printf("Endereco r1Ptr %p\n", r1Ptr);
        printf("Endereco r2Ptr %p\n", r2Ptr);
    }
    return 0;
}
```

A saída exibida no slide inclui:

```text
r1 e r2 sao diferentes, r1 = 30.000000 e r2 = 30.000000
Endereco r1Ptr 0x7ffe2c8bd6d0
Endereco r2Ptr 0x7ffe2c8bd6d8
```

Os endereços são apenas os de uma execução mostrada pelo professor. Duas expressões matematicamente equivalentes podem sofrer arredondamentos diferentes, mesmo que a impressão com seis casas mostre o mesmo texto.

A p. 10 propõe comparar a diferença com um epsilon:

```c
double eps = 1e-15;
if (fabs(*r1Ptr - *r2Ptr) < eps)
    printf("r1 e r2 sao iguais\n");
```

**Notas de revisão:**

- `fabs` deve ser declarado por `math.h`. A tolerância deve ser escolhida conforme a escala e a precisão desejada; `1e-15` não garante considerar iguais os resultados desse exemplo.
- O teste `r1Ptr < r2Ptr` compara endereços de dois objetos independentes e não tem comportamento definido por C nesse caso. Para ensinar ordenação de ponteiros, use posições do mesmo vetor.
- Em `printf`, `%p` exige argumento do tipo `void *`; em adaptações, use conversões como `(void *)r1Ptr`. Essa correção também se aplica aos demais exemplos de endereços da aula.

## Modificação de argumentos por meio de ponteiros (p. 11-12)

Todos os argumentos em C são passados **por valor**. Ponteiros e indireção simulam passagem por referência: passa-se o endereço do objeto que a função precisa alterar, geralmente com `&` na chamada. Isso também permite acessar objetos grandes sem copiar todos os seus elementos.

O exemplo conta pares e ímpares e escreve os dois resultados nas variáveis da função chamadora:

```c
/* Exemplo 3 - qtd pares e impares do vetor e retorna os dois valores */
#include <stdio.h>

void totalParImpar(int vetor[], int tamanho, int *par, int *impar);

int main() {
    int vetor[] = {1,2,3,4,5,6,7,8,9};
    int numPares = 0, numImpares = 0;

    totalParImpar(vetor, 9, &numPares, &numImpares);
    printf("Pares = %d, Impares = %d\n", numPares, numImpares);
    return 0;
}
void totalParImpar(int vetor[], int tamanho, int *par, int *impar) {
    int i;
    for ( i = 0; i < tamanho; i++ ) {
        if ( vetor[i] % 2 == 0 )
            (*par)++;
        else
            (*impar)++;
    }
}
```

Para os valores de 1 a 9, a saída é `Pares = 4, Impares = 5`. Os contadores começam em zero no chamador. `(*par)++` incrementa o inteiro apontado, não o ponteiro.

## Questão: erros na troca de valores (p. 13)

Pergunta do professor: **quais são os erros do código abaixo?** O resultado esperado para entradas 10 e 20 é `a = 20, b = 10`.

**Código intencionalmente incorreto:**

```c
#include <stdio.h>

void troca(int *x, int *y);

int main(){
    int a;
    int *p;

    scanf("%d",&a);
    scanf("%d", p);
    troca(&a, p);
    printf("a= %d, b= %d\n", a, *p);
    return 0;
}
void troca(int *x, int *y){
    int *aux;
    aux = x;
    x = y;
    y = aux;
}
```

As dicas estão na [lista de exercícios](../exercicios_livres/aula_teorica_04/README.md). A solução do professor aparece no suplemento, p. 39.

## Ponteiros e vetores (p. 14-17)

Vetores ocupam posições contíguas na memória. Ao passar um vetor para uma função no uso apresentado, passa-se o endereço de seu primeiro elemento; a função acessa e pode modificar os elementos originais.

O material descreve o nome do vetor como um “ponteiro constante”. **Precisão acrescentada:** um vetor é um objeto diferente de um ponteiro. Na maioria das expressões, seu nome é convertido em ponteiro para o primeiro elemento; há exceções, como `sizeof arr` e `&arr`. Não se pode reatribuir um vetor como se fosse uma variável ponteiro.

```c
/* Exemplo 4 - relacao entre ponteiro e vetor */
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int i;

    printf("Endereco do primeiro elemento (arr):     %p\n", arr);
    printf("Endereco do primeiro elemento (&arr[0]): %p\n", &arr[0]);

    // O nome do vetor arr pode ser atribuido a um ponteiro
    int *p = arr; // p agora aponta para arr[0]

    printf("\nConteudo de p (endereco de arr[0]):   %p\n", p);
    printf("Conteudo apontado por p (*p):         %-d\n", *p);
    printf("Conteudo apontado por p[2] ou *(p+2): %-d\n", *(p+2));

    // Vetor e contigua na memoria?
    printf("\nPosicao endereco\n");
    for ( i = 4; i >= 0; i-- )
        printf("arr[%d]  %p\n", i,  &arr[i]);
    return 0;
}
```

O exemplo mostra a igualdade dos endereços representados por `arr`, `&arr[0]` e `p`, e os valores `*p = 10` e `*(p + 2) = 30`. Na execução ilustrada, os endereços consecutivos diferem por 4 bytes:

```text
arr[4] 0x7fff9aafd220
arr[3] 0x7fff9aafd21c
arr[2] 0x7fff9aafd218
arr[1] 0x7fff9aafd214
arr[0] 0x7fff9aafd210
```

Perguntas do professor (p. 16):

1. Qual é o tamanho de um `int` em bytes?
2. Qual é o valor de `&arr[1] - &arr[0]`?

**Nota de revisão:** consulte `sizeof(int)` no ambiente usado. A subtração desses ponteiros mede a distância em elementos, não em bytes.

No parâmetro de uma função, `int *arr` e `int arr[]` permitem o mesmo acesso aos elementos. Exemplo:

```c
/* Exemplo 6 Modificando um Vetor em uma Funcao */
#include <stdio.h>
//observe que int *arr, neste caso, equivate a int arr[]
void zerarVetor(int *arr, int tamanho);

int main() {
    int i, meuVetor[5] = {1, 2, 3, 4, 5};
    printf("Vetor antes de zerar: ");
    for ( i = 0; i < 5; i++ )
        printf("%d ", meuVetor[i]);
    printf("\n");

    zerarVetor(meuVetor, 5); //passa o endereco inicial do vetor
    printf("Vetor depois de zerar: ");
    for ( i = 0; i < 5; i++ )
        printf("%d ", meuVetor[i]);
    printf("\n");
    return 0;
}
void zerarVetor(int *arr, int tamanho) {
    int i;
    //verifique se o ponteiro e valido
    if ( arr != NULL ){ //arr e um ponteiro para o primeiro elemento
        for (i = 0; i < tamanho; i++)
            arr[i] = 0; // modifica o vetor original
    }
}
```

Saída:

```text
Vetor antes de zerar: 1 2 3 4 5
Vetor depois de zerar: 0 0 0 0 0
```

O teste de `NULL` não comprova que existam `tamanho` elementos acessíveis; isso também faz parte do contrato da função.

## Necessidade de alocação dinâmica (p. 18)

Os exemplos anteriores usavam, em geral, capacidades conhecidas na compilação. A alocação dinâmica permite solicitar memória durante a execução conforme a necessidade. O material usa o modelo de uma região de heap, gerenciada por ponteiros, em contraste com a pilha de chamadas.

**Nota de revisão:** heap e stack descrevem uma organização usual da implementação. A memória disponível continua limitada; pedidos podem falhar.

## `malloc` (p. 19-20)

`malloc`, declarada em `stdlib.h`, solicita um bloco com a quantidade de bytes especificada:

```c
void *malloc(size_t size);
```

O retorno aponta para o início do bloco ou é `NULL` em caso de falha. Use `sizeof` para calcular o tamanho de forma portável. O conteúdo não é inicializado.

```c
/* Exemplo 6 - Uso do malloc  */
#include <stdio.h>
#include <stdlib.h> // Para malloc e free

int main() {
    int *ptr;
    int i, n = 5; // Queremos alocar espaco para 5 inteiros

    // Aloca (n * sizeof(int)) bytes de memoria
    ptr = (int *)malloc( n * sizeof(int) );

    // Verifica se a alocacao foi bem-sucedida
    if ( ptr == NULL ) {
        printf("Falha na alocacao de memoria.\n");
        return 1;
    }

    // Inicializa e imprime os elementos
    for ( i = 0; i < n; i++) {
        ptr[i] = i + 1;
        printf("%d ", ptr[i]); // Saida 1 2 3 4 5
    }
    printf("\n");

    free(ptr); // Libera a memoria alocada
    return 0;
}
```

Saída do exemplo: `1 2 3 4 5`.

**Nota de revisão:** o slide diz que o retorno deve ser convertido. Em C, a conversão de `void *` para um ponteiro de objeto é implícita; o cast explícito usado no original não é obrigatório. Uma forma de adaptação é `ptr = malloc(n * sizeof *ptr);`, com validação prévia de `n` e do cálculo de bytes.

## `calloc` (p. 21-22)

`calloc` recebe a quantidade de elementos e o tamanho de cada um:

```c
void *calloc(size_t num, size_t size);
```

Retorna um ponteiro ou `NULL` em caso de falha. A diferença destacada é a inicialização de todos os bits do bloco com zero, enquanto `malloc` deixa o conteúdo indeterminado.

```c
/* Exemplo 8 - Uso do calloc */
#include <stdio.h>
#include <stdlib.h> // Para calloc e free

int main() {
    int *ptr;
    int n = 3; // Aloca espaco para 3 inteiros

    // Aloca (n) elementos de tamanho (sizeof(int)) e inicializa com zero
    ptr = (int *)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Falha na alocacao de memoria.\n");
        return 1;
    }

    printf("Elementos inicializados por calloc: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]); // Saida: 0 0 0
    }
    printf("\n");

    free(ptr); // Libera a memoria
    return 0;
}
```

Saída: `Elementos inicializados por calloc: 0 0 0`.

**Nota de revisão:** para inteiros, os bits zerados representam zero. Não generalize esse detalhe para a representação de qualquer tipo, como ponteiros, em toda implementação de C.

## Liberação com `free` (p. 23)

`free`, também em `stdlib.h`, libera um bloco obtido por alocação dinâmica:

```c
void free(void *ptr);
```

O argumento deve identificar o início de um bloco alocado ainda não liberado, ou ser `NULL`. Libere a memória quando ela não for mais necessária. O slide menciona `malloc`, `calloc` e `realloc` como origens desses blocos; a implementação do exercício desta aula usa alocar, copiar e liberar, sem depender de `realloc`.

## Organização da memória (p. 24)

O material apresenta quatro regiões típicas:

| Região | Conteúdo no modelo apresentado |
| --- | --- |
| Código executável, ou text | Instruções de máquina |
| Dados estáticos, ou data | Variáveis globais e estáticas, com duração durante toda a execução |
| Pilha, ou stack | Chamadas, parâmetros, variáveis locais automáticas e endereços de retorno; organização LIFO |
| Heap | Blocos dinâmicos, que não precisam ser liberados na ordem inversa de todas as alocações |

A figura mostra código e dados na parte inferior, heap crescendo para cima e pilha crescendo para baixo. Um ponteiro local na pilha pode apontar para um vetor no heap. Trata-se de um esquema ilustrativo; endereços, direções e limites dependem do ambiente.

## Vetores de tamanho variável e alocação dinâmica (p. 25)

O material lembra que C99 introduziu vetores de tamanho variável (VLA), cujo tamanho pode ser definido durante a execução:

```c
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int vetor[n];
    return 0;
}
```

O slide contrasta a pilha, normalmente com limite relativamente pequeno, com a alocação dinâmica para grandes volumes. Um vetor automático muito grande pode esgotar a pilha em implementações que a utilizem para esse armazenamento.

**Notas de revisão:** valide `n > 0` e a leitura antes de declarar um VLA. Seu suporte é opcional em C17, padrão usado neste repositório. A linguagem não exige uma região física específica para ele. O heap também tem limites e a alocação dinâmica pode falhar; “não possuir essa restrição” não significa memória ilimitada.

## Exemplo: separar pares e ímpares em vetores dinâmicos (p. 26-29)

O programa aloca um vetor de `n` inteiros, preenche-o com valores pseudoaleatórios entre -1000 e 1000, conta pares e ímpares e cria dois vetores com as quantidades correspondentes. Depois imprime duas colunas, usando `*` quando uma delas não tem mais elementos.

```c
/* Exemplo 8 - separa pares e impares em dois vetores */
#include <stdio.h>
#include <stdlib.h>

void totalParImpar(int vetor[], int tamanho, int *par, int *impar);
void separaVetorParImpar(int vetor[], int tamanho, int vetorPares[],  int vetorImpares[]);

int main() {
    int n, i, totalPares = 0, totalImpares = 0;
    int *vetor    = NULL;
    int *vPares   = NULL;
    int *vImpares = NULL;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    vetor = (int *) malloc( n * sizeof(int) ); //aloca n posicoes na heap
    if ( vetor == NULL ) {
        printf("Memoria insuficiente\n");
        return 1; //encerra o programa
    }

    //preenche o vetor
    for ( i = 0; i < n; i++ ){
        vetor[i] = (rand()%2001 - 1000); //gera numeros entre[-1000, 1000]
        printf("%d ", vetor[i]);
    }
    printf("\n");

    //conta a quantidade de numeros pares e impares
    totalParImpar( vetor, n, &totalPares, &totalImpares );
    //aloca os vetores de pares e impares
    vPares   = (int *) malloc( totalPares * sizeof(int) );
    vImpares = (int *) malloc( totalImpares * sizeof(int) );

    if ( vPares != NULL && vImpares != NULL ) {
        separaVetorParImpar(vetor, n, vPares, vImpares);
        free(vetor); //libera a memoria de vetor
        printf("Pares   Impares\n");
        i = 0;
        while( i < totalPares || i < totalImpares ) {
            //imprime pares e impares em 2 colunas
            if ( i <  totalPares && i <  totalImpares )
                printf("%5d %5d\n" , vPares[i], vImpares[i]);
            if ( i <  totalPares && i >= totalImpares )
                printf("%5d    *\n", vPares[i]);
            if ( i >= totalPares && i <  totalImpares )
                printf("*    %5d\n", vImpares[i]);
            i++;
        }
        free(vPares);
        free(vImpares);
    }
    return 0;
}
void totalParImpar(int vetor[], int tamanho, int *par, int *impar) {
    int i;
    for ( i = 0; i < tamanho; i++ ) {
        if ( vetor[i] % 2 == 0 )
            (*par)++;
        else
            (*impar)++;
    }
}
void separaVetorParImpar(int vetor[], int tamanho, int vetorPares[], int vetorImpares[]) {
    int i, j = 0, k = 0;
    for( i = 0; i < tamanho; i++ ){
        if ( vetor[i] % 2 == 0 ){
            vetorPares[j] = vetor[i];
            j++;
        }
        else {
            vetorImpares[k] = vetor[i];
            k++;
        }
    }
}
```

Saída ilustrativa do slide, não uma sequência universal de `rand()`:

```text
Digite o tamanho do vetor: 10
690 633 -649 -975 409 -678 624 -976 -460 -102
Pares Impares
 690   633
-678  -649
 624  -975
-976   409
-460     *
-102     *
```

**Notas de revisão:**

- Valide `n`, a leitura e o cálculo de bytes antes de alocar.
- Se todos os números tiverem a mesma paridade, uma das quantidades será zero. Uma alocação de tamanho zero pode retornar `NULL` sem significar o mesmo cenário de falta de memória; trate o vetor vazio explicitamente.
- No original, se uma alocação secundária falhar, o bloco inicial e qualquer outro bloco já obtido não são liberados pelo fluxo do programa. Uma adaptação deve liberar tudo que já conseguiu alocar.
- Os contadores devem estar inicializados e os vetores de saída devem ter espaço suficiente.

## Ponteiros para ponteiros (p. 30)

Um ponteiro para ponteiro guarda o endereço de uma variável ponteiro. Pode ser usado para alterar um ponteiro do chamador ou representar um vetor de ponteiros para linhas.

```c
int a = 99, *b, **c;
b = &a;
c = &b;
printf("%d %d %d\n", a, *b, *(*c));
```

Saída: `99 99 99`. O percurso é `c -> b -> a`.

## Alocação e desalocação de matrizes dinâmicas (p. 31-32)

O método apresentado aloca primeiro um vetor de ponteiros para as linhas e, depois, um vetor de elementos para cada linha:

```c
int **matriz; //um ponteiro para um ponteiro de inteiro
matriz    = (int **) malloc ( 2 * sizeof(int *) );//passo 1
matriz[0] = (int *)  malloc ( 3 * sizeof(int) );  //passo 2
matriz[1] = (int *)  malloc ( 3 * sizeof(int) );  //passo 2
```

A figura mostra o bloco de ponteiros com duas entradas. Cada entrada aponta para uma linha com três inteiros; os valores ilustrativos das linhas são `10 20 30` e `40 50 60`.

Para liberar essa representação, libere cada linha e depois o bloco de ponteiros:

```c
free(matriz[0]);
free(matriz[1]);
free(matriz);
```

**Notas de revisão:** cada alocação deve ser verificada antes do uso. As linhas alocadas separadamente não precisam ser contíguas entre si, embora cada linha seja contígua. Um `int **` dessa representação não é equivalente a `int matriz[L][C]` nem deve ser passado indistintamente a uma função que espera essa matriz. Ponteiros duplos são uma estratégia, não a única forma possível de alocar matrizes.

## Exemplo completo de matriz dinâmica (p. 33-35)

```c
/*Exemplo 9 - aloca e desaloca matriz */
#include <stdio.h>
#include <stdlib.h> //para malloc e free

int main() {
    int **matriz;
    int linha, coluna, i , j;

    printf("Digite a quantidade linhas e colunas da matriz: ");
    scanf("%d %d", &linha, &coluna);

    //aloca o bloco princial
    matriz = (int **) malloc(linha * sizeof(int *));
    if (matriz == NULL) {
        printf("Erro na alocacao da matriz de ponteiros!\n");
        return 1;
    }
    printf("\nBloco principal de ponteiros para linhas alocado (endereco: %p).\n", matriz);

    //aloca de memoria para cada linha individualmente
    for (i = 0; i < linha; i++) {
        matriz[i] = (int *) malloc(coluna * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro na alocacao da linha %d!\n", i);
            return 1;
        }
        printf("Linha %d alocada (endereco: %p).\n", i, matriz[i]);
    }
    printf("Alocacao concluida com sucesso!\n");

    //preenche a matriz com alguns valores de exemplo
    printf("\nPreenchendo a matriz:\n");
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            matriz[i][j] = (i + 1) * 10 + (j + 1); // exemplo: 11, 12, 13, 21, 22, 23
            printf("matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
        }
    }

    printf("\nConteudo da matriz:\n");
    for (i = 0; i < linha; i++) {
        for (j = 0; j < coluna; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }

    //desaloca de memoria
    printf("\nDesalocando memoria...\n");
    for (i = 0; i < linha; i++) {
        free(matriz[i]); // Libera a memoria da i-esima linha
        printf("Linha %d desalocada.\n", i);
    }

    //libera a memoria da matriz de ponteiros principal.
    free(matriz); //libera o bloco de ponteiros de linha
    printf("Bloco principal de ponteiros desalocado.\n");
    printf("Memoria desalocada com sucesso.\n");
    return 0;
}
```

Para entrada `2 3`, os valores são:

```text
matriz[0][0] = 11
matriz[0][1] = 12
matriz[0][2] = 13
matriz[1][0] = 21
matriz[1][1] = 22
matriz[1][2] = 23

Conteudo da matriz:
  11  12  13
  21  22  23
```

A execução também informa a alocação do bloco principal e de cada linha, seus endereços, e a liberação de cada linha seguida do bloco principal.

**Nota de revisão:** se a alocação de uma linha falhar, o original encerra sem liberar as linhas anteriores nem o bloco de ponteiros. Corrija esse caminho ao adaptar; valide dimensões e leituras. Para `%p`, converta o argumento para `void *`.

## Exercício: vetor com redimensionamento automático (p. 36-37)

Implemente um vetor dinâmico com:

- Inserção no final.
- Remoção da primeira ocorrência de um elemento especificado.
- Exibição do conteúdo e dos metadados.
- Expansão e contração automáticas conforme a ocupação.

Estados: `tam`, quantidade de elementos ativos, e `max_tam`, capacidade alocada no heap.

Regras:

1. Capacidade inicial e mínima de 4 elementos.
2. Dobrar `max_tam` ao inserir quando `tam == max_tam`.
3. Reduzir a capacidade pela metade quando, após a remoção, `tam < max_tam / 4` e `max_tam > 4`.

Funções propostas:

```c
int *inicializaVetor(int *tam_ptr, int *max_tam_ptr);
void imprimeVetor(int *elementos, int tam, int max_tam);
int *adicionaElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem);
int buscaElemento(int *elementos, int tam, int elem);
int *removeElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem);
```

`inicializaVetor` aloca a capacidade inicial; `imprimeVetor` mostra os elementos até `tam`; `adicionaElemento` insere e gerencia expansão; `buscaElemento` retorna o índice da primeira ocorrência ou `-1`; `removeElemento` remove a primeira ocorrência e gerencia contração.

Veja a [atividade com dicas e casos de teste](../exercicios_livres/aula_teorica_04/README.md).

## Material suplementar (p. 38-58)

### Solução da questão da troca (p. 39)

<details>
<summary>Código do professor e explicação</summary>

```c
/* Codigo Questao */
#include <stdio.h>

void troca(int *x, int *y);

int main(){
    int a, b;
    int *p;
    p = &b;
    scanf("%d",&a);
    scanf("%d", p);
    troca(&a, p);
    printf("a= %d, b= %d\n", a, *p);
    return 0;
}
void troca(int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}
```

O ponteiro `p` passa a apontar para uma variável `b` existente. A função usa um inteiro temporário e troca `*x` com `*y`, alterando os objetos apontados, em vez de trocar apenas cópias locais dos endereços.

</details>

### Solução do vetor dinâmico (p. 40-49)

<details>
<summary>Código do professor</summary>

```c
#include <stdio.h>
#include <stdlib.h>

#define TAM_MINIMO 4

// Prototipos das funcoes
int *inicializaVetor(int *tam_ptr, int *max_tam_ptr);
void imprimeVetor(const int *elementos, int tam, int max_tam);
int *adicionaElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem);
int buscaElemento(const int *elementos, int tam, int elem);
int *removeElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem);

int main() {
    int *meuVetor_elementos = NULL; // Ponteiro para o vetor de elementos
    int meuVetor_tam = 0;           // Tamanho atual do vetor
    int meuVetor_max_tam = 0;       // Capacidade maxima alocada

    // Inicializa o vetor
    meuVetor_elementos = inicializaVetor(&meuVetor_tam, &meuVetor_max_tam);
    if (meuVetor_elementos == NULL) {
        printf("Falha ao inicializar o vetor.\n");
        return 1;
    }
    printf("Vetor inicializado:\n");
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    // Adiciona elementos
    printf("Adicionando elementos: 10, 20, 30, 40, 50, 60\n");
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 10);
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 20);
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 30);
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 40);
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 50); // Deve redimensionar
    meuVetor_elementos = adicionaElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 60);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    // Remove elementos
    printf("Removendo 20:\n");
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 20);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    printf("Removendo 10:\n");
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 10);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    printf("Removendo 30:\n");
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 30);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    printf("Removendo 40:\n");
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 40);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    printf("Removendo 50:\n");  // Deve redimensionar
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 50);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    printf("Removendo 60:\n");  // Deve redimensionar
    meuVetor_elementos = removeElemento(meuVetor_elementos, &meuVetor_tam, & meuVetor_max_tam, 60);
    imprimeVetor(meuVetor_elementos, meuVetor_tam, meuVetor_max_tam);
    printf("----------------------------------\n");

    // Libera a memoria alocada
    if (meuVetor_elementos != NULL) {
        free(meuVetor_elementos);
        meuVetor_elementos = NULL;
    }
    printf("Memoria liberada.\n");

    return 0;
}

int *inicializaVetor(int *tam_ptr, int *max_tam_ptr) {
    if (tam_ptr == NULL || max_tam_ptr == NULL) {
        fprintf(stderr, "Erro: Ponteiros para tam ou max_tam sao NULL na inicializacao .\n");
        return NULL;
    }

    *tam_ptr = 0;       // Inicializa o tamanho atual do vetor como 0 elementos
    *max_tam_ptr = TAM_MINIMO;   // Capacidade inicial alocada (pelo menos 4)

    // Usando calloc para alocar memoria para os elementos
    int *elementos = (int *) calloc(*max_tam_ptr, sizeof(int));
    if (elementos == NULL) {
        printf("Erro: Falha na alocacao inicial de memoria para elementos.\n");
        return NULL;
    }
    return elementos;
}

void imprimeVetor(const int *elementos, int tam, int max_tam) {
    if (elementos == NULL) {
        printf("Vetor vazio ou nao inicializado.\n");
        return;
    }
    printf("Elementos do vetor: [ ");
    for (int i = 0; i < tam; i++) {
        printf("%d ", elementos[i]);
    }
    printf("]\n");
    printf("Tamanho atual: %d, Capacidade maxima: %d\n", tam, max_tam);
}

int *adicionaElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem) {
    if (elementos == NULL || tam_ptr == NULL || max_tam_ptr == NULL) {
        printf("Erro: Ponteiro(s) invalido(s) para adicionar elemento.\n");
        return NULL;
    }

    // Verifica se o vetor esta cheio (tamanho atual igual a capacidade maxima)
    if (*tam_ptr == *max_tam_ptr) {
        // Redimensiona: dobra a capacidade
        int novo_max_tam = (*max_tam_ptr) * 2;
        printf("Redimensionando (adicionar): capacidade de %d para %d.\n", *max_tam_ptr , novo_max_tam);

        // 1. Aloca um novo bloco de memoria com o novo tamanho
        int *novos_elementos = (int *) calloc(novo_max_tam, sizeof(int));
        if (novos_elementos == NULL) {
            printf("Erro: Falha na alocacao de memoria ao adicionar elemento (novo bloco).\n");
            return NULL; // Falha na alocacao
        }

        // 2. Copia os elementos do bloco antigo para o novo bloco
        for (int i = 0; i < *tam_ptr; i++) {
            novos_elementos[i] = elementos[i];
        }

        // 3. Libera o bloco de memoria antigo
        free(elementos);

        elementos = novos_elementos;     // Atualiza o ponteiro local 'elementos'
        *max_tam_ptr = novo_max_tam;     // Atualiza a capacidade maxima
    }

    // Adiciona o novo elemento
    elementos[*tam_ptr] = elem;
    (*tam_ptr)++; // Incrementa o tamanho atual do vetor
    return elementos; // Retorna o (possivelmente novo) ponteiro base do vetor
}

int buscaElemento(const int *elementos, int tam, int elem) {
    if (elementos == NULL) {
        return -1; // Vetor nao inicializado ou vazio
    }
    for (int i = 0; i < tam; i++) {
        if (elementos[i] == elem) {
            return i; // Elemento encontrado no indice 'i'
        }
    }
    return -1; // Elemento nao encontrado
}

int *removeElemento(int *elementos, int *tam_ptr, int *max_tam_ptr, int elem){
    if (elementos == NULL || tam_ptr == NULL || max_tam_ptr == NULL){
        printf("Erro: Ponteiro(s) invalido(s) para remover elemento.\n");
        return NULL;
    }

    int pos = buscaElemento(elementos, *tam_ptr, elem); // Encontra a posicao do elemento
    if (pos == -1){
        printf("Elemento %d nao encontrado para remocao.\n", elem);
        return elementos;
    }

    // Desloca os elementos a direita do elemento removido uma posicao para a esquerda
    for ( int i = pos; i < (*tam_ptr - 1); i++)
        elementos[i] = elementos[i+1];
    (*tam_ptr)--;

    // Redimensiona o vetor se o numero de elementos for menor que 1/4 da capacidade maxima
    // e a capacidade maxima for maior que a capacidade minima (4).
    if (*tam_ptr < (*max_tam_ptr / TAM_MINIMO) && *max_tam_ptr > TAM_MINIMO){
        int novo_max = (*max_tam_ptr / 2) < TAM_MINIMO ?  TAM_MINIMO : (*max_tam_ptr / 2);

        // 1. Aloca um novo bloco de memoria com o novo tamanho
        int *novo_elementos = (int *) malloc( novo_max * sizeof(int));
        if (novo_elementos == NULL) {
            printf("Erro: Falha na alocacao de memoria ao remover elemento (encolher).\n");
            return NULL;
        }
        printf("Redimensionando (remover): capacidade de %d para %d.\n", *max_tam_ptr, novo_max);

        // 2. Copia os elementos do bloco antigo para o novo bloco (apenas os relevantes)
        for (int i = 0; i < *tam_ptr; i++)
            novo_elementos[i] = elementos[i];

        // 3. Libera o bloco de memoria antigo
        free(elementos);
        elementos = novo_elementos; // Atualiza o ponteiro local 'elementos'
        *max_tam_ptr = novo_max;    // Atualiza a capacidade maxima
    }
    return elementos;
}
```

</details>

Rastreamento apresentado nas p. 48-49:

| Etapa | Elementos | Tamanho | Capacidade |
| --- | --- | --- | --- |
| Inicialização | `[]` | 0 | 4 |
| Adicionar 10, 20, 30, 40, 50, 60 | `[10, 20, 30, 40, 50, 60]` | 6 | 8 |
| Remover 20 | `[10, 30, 40, 50, 60]` | 5 | 8 |
| Remover 10 | `[30, 40, 50, 60]` | 4 | 8 |
| Remover 30 | `[40, 50, 60]` | 3 | 8 |
| Remover 40 | `[50, 60]` | 2 | 8 |
| Remover 50 | `[60]` | 1 | 4 |
| Remover 60 | `[]` | 0 | 4 |

A expansão de 4 para 8 ocorre na inserção de 50. A contração de 8 para 4 ocorre ao remover 50; tamanho 2 com capacidade 8 ainda não satisfaz a desigualdade estrita. A execução termina liberando a memória.

**Notas de revisão:**

- O chamador atribui diretamente os retornos a `meuVetor_elementos`. Se uma realocação manual falhar e a função retornar `NULL`, ele perde o único ponteiro para o bloco antigo. Preserve-o por meio de um temporário ou de outro contrato de falha.
- Em `removeElemento`, a remoção já aconteceu quando a tentativa de encolher falha. A política de erro deve levar em conta esse novo tamanho lógico.
- O código não verifica estouro ao dobrar a capacidade ou calcular a quantidade de bytes.
- O comentário “Deve redimensionar” ao remover 60 não corresponde à execução: a capacidade já está no mínimo de 4 e permanece assim.
- A solução usa `const` em impressão e busca; a p. 37 não o usa nesses protótipos.

### Endereço do ponteiro e endereço apontado (p. 50-51)

```c
/* Exemplo - Operadores de Ponteiros */
#include <stdio.h>

int main() {
    int varInteiro; //variaval inteiro
    int *ponteiroVarInteiro = NULL; // ponteiro para um inteiro

    printf( "O endereco de varInteiro e: %p\n", &varInteiro );
    printf( "O endereco de ponteiroVarInteiro e: %p\n", &ponteiroVarInteiro );

    varInteiro = 80; //atribui o valor 80
    ponteiroVarInteiro = &varInteiro; // atribui o endereco de varInteiro

    printf( "\nO endereco de varInteiro e: %p\n", &varInteiro );
    printf( "O valor de ponteiroVarInteiro e: %p\n", ponteiroVarInteiro );

    printf( "\nO valor de varInteiro e: %d\n", varInteiro );
    printf( "O valor de *ponteiroVarInteiro e: %d\n", *ponteiroVarInteiro );

    printf( "\nMostrando que * e & sao complementos um do outro\n");
    printf( "*&ponteiroVarInteiro = %p\n", *&ponteiroVarInteiro );
    printf( "&*ponteiroVarInteiro = %p\n", &*ponteiroVarInteiro );
    return 0;
}
```

A saída distingue o endereço da variável `varInteiro` do endereço da variável `ponteiroVarInteiro`. Depois da atribuição, o valor armazenado no ponteiro coincide com `&varInteiro`; tanto `varInteiro` quanto `*ponteiroVarInteiro` produzem 80. Para o ponteiro válido desse exemplo, `*&ponteiroVarInteiro` e `&*ponteiroVarInteiro` reproduzem seu valor.

**Nota de revisão:** os endereços concretos variam entre execuções; use `(void *)` nos argumentos de `%p` em uma adaptação.

### Aritmética de ponteiros (p. 52-53)

Adicionar ou subtrair um inteiro a um ponteiro avança ou recua em unidades do tipo apontado. `p++`, para `int *p`, avança uma posição de inteiro, não necessariamente um byte.

```c
/* Exemplo Aritmetica de Ponteiros */
#include <stdio.h>

int main() {
    int arr[3] = {10, 20, 30};
    int *p = arr; // p aponta para arr[0]

    printf("Endereco de arr[0]: %p, Valor: %d\n", p, *p); // 10

    p++; // p agora aponta para arr[1] (avanca sizeof(int) bytes)
    printf("Endereco de arr[1]: %p, Valor: %d\n", p, *p); // 20

    p = p + 1; // p agora aponta para arr[2]
    printf("Endereco de arr[2]: %p, Valor: %d\n", p, *p); // 30

    // Acesso direto via deslocamento
    printf("Valor de arr[0] via ponteiro: %d\n", *(arr + 0)); // 10
    printf("Valor de arr[1] via ponteiro: %d\n", *(arr + 1)); // 20
    printf("Valor de arr[2] via ponteiro: %d\n", *(arr + 2)); // 30

    return 0;
}
```

Os valores acessados são 10, 20 e 30. O acesso `*(arr + i)` corresponde a `arr[i]`. Os endereços da execução ilustrada avançam 4 bytes, conforme o tamanho de `int` naquele ambiente.

**Nota de revisão:** mantenha a aritmética dentro do mesmo vetor ou na posição imediatamente após seu final; essa posição final pode ser formada, mas não desreferenciada.

### Erros de gerenciamento de memória (p. 54-55)

- **Ponteiro pendurado:** o objeto foi liberado, mas ainda há ponteiros que o referenciavam; acessá-lo por eles é inválido.
- **Vazamento de memória:** um bloco necessário para liberação deixa de ser alcançável sem ter sido liberado.
- **Dupla liberação:** tentar liberar novamente um bloco já liberado, com comportamento indefinido.

```c
/* Exemplo 2 - erro de liberacao de memoria */
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1 = (int *)malloc(sizeof(int));
    int *p2 = p1; // p2 tambem aponta para a mesma area de memoria

    *p1 = 10;
    printf("Valor via p1: %d\n", *p1);
    printf("Valor via p2: %d\n", *p2);

    free(p1); // Memoria liberada, p1 e p2 sao agora dangling pointers
    // p1 = NULL; // Boa pratica para evitar dangling pointer

    // printf("Valor via p2 apos free(p1): %d\n", *p2); // ERRO: Acesso a memoria liberada

    // free(p2); // ERRO: Dupla liberacao da mesma memoria (p2 aponta para a mesma que p1)

    return 0;
}
```

O exemplo cria dois ponteiros para o mesmo bloco. Depois de `free(p1)`, o acesso por `p2` e a chamada `free(p2)` permanecem comentados para mostrar os erros que não devem ser executados.

**Notas de revisão:** confira `malloc` antes de `*p1 = 10`. Atribuir `NULL` a `p1` não corrige automaticamente `p2` nem outros ponteiros que referenciavam o mesmo bloco.

### Propósito de `const` (p. 56)

`const` é um qualificador de tipo usado para expressar acesso somente para leitura. Em parâmetros, ajuda a indicar o que uma função pretende preservar.

| Declaração | Restrição |
| --- | --- |
| `const int *ptr;` | Não modificar o inteiro por meio de `ptr`; o ponteiro pode mudar |
| `int * const ptr = &valor;` | O ponteiro não pode mudar; o inteiro pode ser modificado por ele |
| `const int * const ptr = &valor;` | Não mudar o ponteiro nem modificar o inteiro por meio dele |

**Precisão acrescentada:** um ponteiro para `const` restringe modificações por esse acesso. Isso não impede outro acesso de modificar um objeto que originalmente não foi definido como `const`.

### Alterar um ponteiro do chamador (p. 57-58)

A aula compara devolver um ponteiro com receber o endereço de um ponteiro:

```c
/* Exemplo 4 - passagem de ponteiro por referencia */
#include <stdio.h>
#include <stdlib.h>

int *alocaVetor1(int tam); //forma usual
void alocaVetor2(int **vetor, int tam); //forma de ponteiro para ponteiro

int main() {
    int *v1 = NULL;
    int *v2 = NULL;

    //aloca vetor de 5 posicoes
    v1 = alocaVetor1(5);

    //aloca vetor de 5 posicoes
    alocaVetor2(&v2, 5); //passando ponteiro por referencia

    //preenche vetores
    for (int i = 0; i < 5; i++){
        v1[i] = i;
        v2[i] = i+10;
    }

    //imprime vetores
    for (int i = 0; i < 5; i++)
        printf("v1[%d]=%2d, v2[%d]=%2d\n", i, i, v1[i], v2[i]);

    free(v1);
    free(v2);
    return 0;
}

int *alocaVetor1(int tam){
    return (int *) calloc( tam, sizeof(int) );
}

void alocaVetor2(int **vetor, int tam){
    *vetor = (int *) calloc( tam, sizeof(int) );
}
```

Na primeira forma, `v1` recebe o retorno de `alocaVetor1`. Na segunda, `&v2` é passado para `alocaVetor2`, cujo parâmetro é `int **`; a atribuição a `*vetor` altera `v2`.

Saída apresentada pelo material:

```text
v1[0]= 0, v2[0]=10
v1[1]= 1, v2[1]=11
v1[2]= 2, v2[2]=12
v1[3]= 3, v2[3]=13
v1[4]= 4, v2[4]=14
```

**Notas de revisão:** o `printf` original passa os argumentos na ordem `i, i, v1[i], v2[i]`; a ordem correta para os campos é `i, v1[i], i, v2[i]`. Como `v1[i] == i` nesse exemplo, a divergência fica escondida na saída. Verifique também ambas as alocações antes de preencher os vetores, liberando o bloco que tiver sido obtido caso a outra alocação falhe.

## Pergunta final e contatos (p. 59-60)

Pergunta do professor: **dado que funções em C residem em endereços de memória, é possível declarar um ponteiro para uma função?** Há uma dica na [lista de exercícios](../exercicios_livres/aula_teorica_04/README.md).

A p. 60 contém contatos pessoais, omitidos desta transcrição de estudo.

[Voltar ao índice de teoria](README.md)
