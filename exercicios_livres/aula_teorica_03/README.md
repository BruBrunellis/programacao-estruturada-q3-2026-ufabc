# Aula teórica 03 - Vetores, matrizes e strings

Enunciados do professor em `PE/Aulas/03_Teoria_Arranjos.pdf` (76 páginas), conferidos em 18/10/2026. Numeração e restrições dos seis exercícios foram preservadas. **Dicas, testes e convenções de prática indicadas abaixo são complementos do Codex.** Esta lista não contém soluções.

Consulte a [transcrição da aula 03](../../aulas_teoricas/03_arranjos.md). Crie programas independentes nesta pasta, como `exercicio_01.c`. O material suplementar da transcrição contém as soluções do professor; tente resolver antes de consultá-lo.

## 1. Produto interno de dois vetores (p. 15)

**Enunciado:** leia dois vetores de tamanho `n` e compute seu produto interno (produto escalar).

```text
A · B = A[0] * B[0] + A[1] * B[1] + ... + A[n-1] * B[n-1]
```

**Convenção para praticar:** leia `n` e os valores dos vetores; aceite valores reais, como na demonstração suplementar. Se usar capacidade fixa, valide `1 <= n <= capacidade`.

**Dicas:** passe às funções o vetor e seu tamanho utilizado; inicialize o acumulador; multiplique posições correspondentes. Para ler um `double` com `scanf`, use `%lf`.

| A | B | Produto |
| --- | --- | --- |
| `[1, 2, 3]` | `[4, 5, 6]` | 32 |
| `[1, -1]` | `[1, 1]` | 0 |
| `[2.5]` | `[4]` | 10 |

## 2. Elementos em comum (p. 15)

**Enunciado:** leia dois vetores com `n` inteiros cada. Verifique quais elementos do segundo vetor são iguais a algum elemento do primeiro. Se não houver elementos em comum, informe isso.

**Convenção para praticar:** mantenha o mesmo `n` nos dois vetores. Informe cada índice do segundo vetor que tenha correspondência e seu valor, na ordem desse vetor. Ocorrências repetidas nele podem aparecer separadamente. O professor não fixa esse formato. A demonstração suplementar permite tamanhos independentes e imprime todos os pares de índices correspondentes, uma variação do enunciado.

**Dicas:**

- Para cada elemento do segundo vetor, faça uma busca no primeiro.
- Diferencie “encontrei este elemento” de “encontrei algum elemento em toda a execução”.
- Se não precisar imprimir todos os pares, a busca pode terminar na primeira correspondência.
- Considere números negativos e valores repetidos.

| A | B | Resultado pela convenção acima |
| --- | --- | --- |
| `[1, 3, 5]` | `[5, 2, 3]` | `B[0] = 5` e `B[2] = 3` |
| `[1, 2]` | `[3, 4]` | Informar ausência de elementos em comum |
| `[2, 2, 7]` | `[2, 2, 9]` | `B[0] = 2` e `B[1] = 2` |

## 3. Maior elemento com recursão (p. 15)

**Enunciado:** escreva um programa com uma **função recursiva** que encontre o maior elemento de um vetor de inteiros.

**Convenção para praticar:** leia um vetor não vazio e imprima seu maior valor.

**Dicas:**

- Um vetor de um elemento tem máximo conhecido.
- Relacione o máximo atual ao máximo de um trecho menor.
- Defina se o parâmetro representa tamanho ou último índice.
- Não inicialize o máximo com zero: todos os valores podem ser negativos.
- Guarde o resultado da chamada menor para evitar repeti-la.

| Vetor | Máximo |
| --- | --- |
| `[1, 4, 5, 8, 2, 3]` | 8 |
| `[-8, -2, -10]` | -2 |
| `[7]` | 7 |
| `[5, 5, 5]` | 5 |

## 4. Multiplicação de matrizes (p. 20)

**Enunciado:** escreva um programa para multiplicar `A`, de dimensões `m × n`, por `B`, de dimensões `n × p`. O resultado `C = A · B` tem dimensões `m × p`.

Na notação do professor:

```text
c[i,j] = soma de a[i,k] * b[k,j], para k de 1 até n
1 <= i <= m; 1 <= j <= p
```

Em C, adapte os índices para começarem em zero.

**Dicas:**

- Confira se o número de colunas de `A` é igual ao número de linhas de `B`.
- Cada elemento de `C` combina uma linha de `A` com uma coluna de `B`.
- Pense em dois laços para a posição de saída e um terceiro para a soma dos produtos.
- Reinicie a soma em cada posição de `C`.
- Valide dimensões e capacidades; não imprima resultado não inicializado se a multiplicação for impossível.

**Exemplo do material suplementar (p. 59):**

```text
A (3 × 2):      B (2 × 3):      C (3 × 3):
 2  3           1  2  3         -4   4  18
 0  1          -2  0  4         -2   0   4
-1  4                          -9  -2  13
```

Confira também matriz `1 × 1`, multiplicação pela identidade e dimensões incompatíveis. Não se trata de multiplicar posição a posição.

## 5. Transposição de matriz quadrada in-place (p. 21)

**Enunciado:** transforme uma matriz quadrada `n × n` em sua transposta. Faça a transformação **in-place, sem criar uma segunda matriz auxiliar**.

```text
Original:      Transposta:
1 2 3          1 4 7
4 5 6          2 5 8
7 8 9          3 6 9
```

**Dicas:** o valor de `[i][j]` vai para `[j][i]`; a diagonal permanece igual. Visite apenas um dos lados da diagonal para não desfazer as trocas. Uma variável escalar temporária é compatível com a restrição; uma segunda matriz não é.

Confira uma matriz `1 × 1`, uma matriz simétrica e duas transposições consecutivas, que devem recuperar a original.

## 6. Contagem de palavras (p. 28)

**Enunciado:** faça um programa que conte o número de palavras em um texto de tamanho no máximo 100. Lembretes do professor: `\0` indica fim da string e `\n` representa quebra de linha.

**Convenção para praticar:** palavra é uma sequência não vazia separada por espaços; `\n` encerra a linha e `\0` encerra a string, como na solução suplementar. Espaços repetidos não criam palavras vazias. Tabulações como separadores são uma extensão opcional.

**Dicas:**

- Use leitura que aceite espaços, como `fgets`.
- Para 100 caracteres de conteúdo, reserve espaço extra para `\0` e, se for armazenado, para `\n`.
- A demonstração usa `char texto[100]`, que comporta no máximo 99 caracteres antes do terminador; diferencie capacidade de comprimento.
- Conte começos de palavras ou mantenha um indicador de que está dentro de uma palavra.
- Trate linha vazia e espaços no começo e no final.

| Texto | Palavras |
| --- | --- |
| `ola mundo` | 2 |
| `  C   e legal  ` | 3 |
| `programacao` | 1 |
| Apenas espaços ou linha vazia | 0 |

## Pergunta de revisão do professor (p. 75)

**Como se cria um vetor de strings ou um vetor de vetores em C?**

Dica: pense em uma dimensão para a quantidade de strings e outra para a capacidade de cada uma, incluindo `\0`. Ao estudar a aula 04, compare com um vetor de ponteiros.

## Exemplo suplementar para praticar (p. 65-67)

O professor apresenta como **exemplo**, fora dos seis exercícios numerados: encontrar todas as posições iniciais de uma palavra em um texto de tamanho no máximo 100. Para texto `a lala lalaland` e palavra `lala`, a saída é `2 7 9`.

Dicas: é uma busca por substring, inclusive dentro de palavras maiores e com sobreposição. Confira a última posição possível; remova `\n` apenas se estiver presente. Para este treino opcional, considere a palavra não vazia.

[Voltar ao índice](../README.md)
