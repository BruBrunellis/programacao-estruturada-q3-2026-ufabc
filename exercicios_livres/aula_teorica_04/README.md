# Aula teórica 04 - Ponteiros e alocação dinâmica

Atividades do professor em `PE/Aulas/04_TEORIA_Alocacao.pdf` (60 páginas), conferidas em 18/10/2026: uma questão de correção de código, um exercício de vetor dinâmico e perguntas de revisão. **Dicas, testes e orientações de robustez indicados abaixo são complementos do Codex.** Esta lista não contém soluções.

Consulte a [transcrição da aula 04](../../aulas_teoricas/04_alocacao_dinamica.md). Crie arquivos separados para suas tentativas. O material suplementar da transcrição contém resoluções; tente resolver antes de consultá-lo.

## Questão: encontre e corrija os erros na troca (p. 13)

**Enunciado:** quais são os erros do código abaixo? Corrija-o para que, ao receber `10` e `20`, imprima `a = 20, b = 10`.

Código original com formatação normalizada. **Contém erros intencionais; analise antes de executar.**

```c
#include <stdio.h>

void troca(int *x, int *y);

int main() {
    int a;
    int *p;
    scanf("%d", &a);
    scanf("%d", p);
    troca(&a, p);
    printf("a = %d, b = %d\n", a, *p);
    return 0;
}

void troca(int *x, int *y) {
    int *aux;
    aux = x;
    x = y;
    y = aux;
}
```

**Dicas:**

- Antes do segundo `scanf`, desenhe para qual objeto `p` aponta. Existe endereço válido atribuído a ele?
- Diferencie trocar dois ponteiros locais e trocar os valores dos objetos apontados.
- C passa argumentos por valor, inclusive ponteiros. O que precisa ser desreferenciado para alterar as variáveis de `main`?
- Escolha o tipo da variável auxiliar conforme o que ela deve guardar.
- Como cuidado adicional, confira os retornos de `scanf`.

**Testes:** `(10, 20)` vira `(20, 10)`; `(-3, 8)` vira `(8, -3)`; `(5, 5)` permanece `(5, 5)`.

## Exercício: vetor dinâmico com redimensionamento (p. 36-37)

**Enunciado:** implemente um vetor dinâmico de inteiros com redimensionamento automático. Permita inserir no final, remover a primeira ocorrência de um valor, buscar um elemento e exibir o conteúdo com seus metadados.

| Estado | Significado |
| --- | --- |
| `tam` | Tamanho lógico: quantidade de elementos ativos |
| `max_tam` | Capacidade: quantidade de posições alocadas no heap |

**Regras do professor:**

1. Capacidade inicial e mínima: **4**.
2. Antes de inserir com `tam == max_tam`, duplique a capacidade.
3. Remova apenas a **primeira ocorrência** do valor.
4. Após a remoção, se `tam < max_tam / 4` e `max_tam > 4`, reduza a capacidade à metade, respeitando o mínimo de 4. A desigualdade é estrita: um quarto exato não provoca redução.
5. Exiba somente os `tam` elementos ativos, além do tamanho e da capacidade.

Implemente as funções propostas na p. 37:

```c
int *inicializaVetor(int *tam_ptr, int *max_tam_ptr);
void imprimeVetor(int *elementos, int tam, int max_tam);
int *adicionaElemento(int *elementos, int *tam_ptr,
                     int *max_tam_ptr, int elem);
int buscaElemento(int *elementos, int tam, int elem);
int *removeElemento(int *elementos, int *tam_ptr,
                   int *max_tam_ptr, int elem);
```

`buscaElemento` devolve o índice da primeira ocorrência ou `-1`. A solução suplementar usa `const` nos parâmetros de leitura de `imprimeVetor` e `buscaElemento`; você também pode fazê-lo, mantendo protótipos e definições compatíveis.

**Dicas de implementação:**

- Preserve `0 <= tam <= max_tam`.
- Para redimensionar como nos slides, aloque outro bloco, copie os elementos ativos e libere o antigo após o sucesso da alocação.
- O endereço pode mudar: observe por que inserção e remoção retornam `int *`, além de alterarem os metadados por ponteiros.
- Depois de remover, desloque os elementos posteriores para preservar a ordem.
- Se o valor não existir, informe isso e preserve o estado.
- Faça uma redução pela metade por remoção bem-sucedida, conforme o `if` da demonstração, sem um laço de reduções sucessivas.
- Libere a memória ao terminar.

**Cuidados adicionais de robustez:**

- Verifique cada alocação antes de usar o bloco.
- Não sobrescreva o único ponteiro válido com `NULL`: use um temporário no chamador ou documente outra política de falha que preserve o bloco antigo.
- Uma falha ao expandir não deve inserir nem alterar metadados. Se a remoção já ocorreu e o encolhimento falhar, é possível manter o bloco maior com o novo tamanho lógico; documente essa escolha.
- Confira os limites numéricos ao dobrar a capacidade e calcular bytes.
- `realloc` é alternativa de estudo; o professor usa alocar, copiar e liberar, sem exigir `realloc`.

**Roteiro de teste baseado nas p. 48-49:**

| Operação | Elementos | `tam` | `max_tam` |
| --- | --- | --- | --- |
| Inicializar | `[]` | 0 | 4 |
| Inserir 10, 20, 30, 40 | `[10, 20, 30, 40]` | 4 | 4 |
| Inserir 50 | `[10, 20, 30, 40, 50]` | 5 | 8 |
| Inserir 60 | `[10, 20, 30, 40, 50, 60]` | 6 | 8 |
| Remover 20 | `[10, 30, 40, 50, 60]` | 5 | 8 |
| Remover 10 | `[30, 40, 50, 60]` | 4 | 8 |
| Remover 30 | `[40, 50, 60]` | 3 | 8 |
| Remover 40 | `[50, 60]` | 2 | 8 |
| Remover 50 | `[60]` | 1 | 4 |
| Remover 60 | `[]` | 0 | 4 |

**Outros casos:** buscar/remover em vetor vazio; remover valor inexistente; inserir `[7, 2, 7]` e remover `7` uma vez, restando `[2, 7]`; inserir o nono elemento para expandir de 8 para 16. Com capacidade 16, tamanho 4 não contrai e tamanho 3 contrai para 8. Confira também os caminhos de falha de alocação.

## Perguntas de revisão do professor

### Tamanho e diferença entre endereços (p. 16)

Considere `int arr[5] = {10, 20, 30, 40, 50};`.

1. **Qual é o tamanho de um `int` em bytes?** Dica: investigue seu ambiente com `sizeof`; o tamanho mostrado no slide não é uma regra universal.
2. **Qual é o valor de `&arr[1] - &arr[0]`?** Dica: diferencie distância em bytes de distância em elementos; ambos os ponteiros pertencem ao mesmo vetor.

### Ponteiros para funções (p. 59)

**Dado que funções em C residem em endereços de memória, é possível declarar um ponteiro para uma função?**

Dica: investigue como indicar retorno e parâmetros da função apontada. Distinga uma função que retorna um ponteiro de um ponteiro para função; não confunda com `int *` ou `int **`.

[Voltar ao índice](../README.md)
