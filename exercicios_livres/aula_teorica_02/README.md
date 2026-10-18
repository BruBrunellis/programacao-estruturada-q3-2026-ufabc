# Aula teórica 02 - Funções e recursão

Enunciados do professor em `PE/Aulas/02_Teoria.pdf` (56 páginas), conferidos em 18/10/2026. A redação foi normalizada. **Dicas adicionais, testes e convenções identificadas abaixo são complementos do Codex**, não exigências extras do professor. Esta lista não contém soluções.

Consulte a [aula 02](../../aulas_teoricas/02_modularizacao.md). Crie um programa independente por exercício nesta pasta, por exemplo `exercicio_01.c`. A aula e seus exemplos de referência contêm resoluções; tente resolver antes de consultá-los.

## 1. Série de Euler (p. 13)

**Enunciado:** o número de Euler, a constante `e`, pode ser representado pela série infinita:

```text
e = 1/0! + 1/1! + 1/2! + 1/3! + ...
```

Faça um programa para calcular a soma dos `n` primeiros termos, com `n > 0`. Discuta como dividir o programa em subproblemas e funções.

**Dicas:**

- Separe leitura, cálculo do fatorial e soma da série.
- `0! = 1`; para `n` termos, o último índice é `n - 1`.
- Use divisão real: dividir dois inteiros trunca o resultado.
- Documente um limite compatível com os tipos numéricos. A demonstração suplementar usa até 10 termos; esse limite não consta do enunciado.

| Entrada `n` | Soma esperada |
| --- | --- |
| 1 | 1 |
| 2 | 2 |
| 3 | 2,5 |
| 5 | Aproximadamente 2,7083333333 |

Teste também a rejeição de zero e de valores negativos.

## 2. Menor base de uma potência (p. 13)

**Enunciado:** escreva a função `menorBase`, que recebe um inteiro positivo `n` e retorna o menor inteiro positivo `b` tal que `b^k = n` para algum inteiro `k`. **Não utilize a biblioteca `math.h`.**

**Convenção para praticar:** adote `k >= 1`, como na interpretação da demonstração suplementar. Assim, todo `n` positivo admite pelo menos a representação `n^1`, inclusive `1 = 1^1`.

**Dicas:**

- Teste bases em ordem crescente; a primeira que funcionar será a menor.
- Construa potências por multiplicações sucessivas, sem `pow`.
- Para base maior que 1, pare quando a potência alcançar ou ultrapassar `n`.
- Trate `n = 1` separadamente para não multiplicar por 1 indefinidamente.
- Antes de multiplicar, pense no teste `potencia > n / base` para evitar ultrapassar `n` e prevenir estouro.

| `n` | Menor base |
| --- | --- |
| 1 | 1 |
| 9 | 3 |
| 16 | 2 |
| 17 | 17 |
| 64 | 2 |

## 3. Exponenciação recursiva (p. 37)

**Enunciado:** escreva uma função recursiva `power(base, expoente)` que retorne `base^expoente`. Considere `expoente` inteiro maior ou igual a 1. Exemplo: `power(3, 4) = 3 * 3 * 3 * 3`.

**Dica do professor:** use `base^expoente = base * base^(expoente - 1)`; a condição de término ocorre quando `expoente == 1`, pois `base^1 = base`.

**Dicas adicionais:**

- Identifique o valor devolvido por cada chamada antes de fazer a multiplicação anterior.
- Preserve a exigência de recursão; não substitua por um laço ou `pow`.
- Para estes testes, use base inteira e limite os valores ao intervalo representável pelo tipo escolhido.
- Aceitar expoente zero é uma extensão, não parte do domínio original.

| Base | Expoente | Resultado |
| --- | --- | --- |
| 3 | 4 | 81 |
| 7 | 1 | 7 |
| -2 | 3 | -8 |
| -2 | 4 | 16 |
| 0 | 2 | 0 |

## 4. Dígitos invertidos (p. 37)

**Enunciado:** escreva uma função que receba um inteiro positivo e imprima seus dígitos na ordem inversa. Exemplo do professor: `7631` deve produzir `1367`.

**Ambiguidade do original:** o texto usa “imprime” e “retornar”. Adote **impressão dos dígitos**, conforme a função `void` da solução suplementar (p. 47). Assim, `1200` produz `0021`.

**Dicas:**

- O resto por 10 identifica o último dígito; a divisão inteira por 10 o remove.
- Aproveite o tema da aula e construa uma versão recursiva, escolhendo um caso base.
- Diferencie imprimir cada dígito de construir um novo valor inteiro.

| Entrada | Dígitos impressos |
| --- | --- |
| 7631 | `1367` |
| 7 | `7` |
| 1200 | `0021` |
| 1001 | `1001` |

Aceitar zero e imprimir `0` é uma extensão opcional ao domínio positivo original.

## 5. Máximo divisor comum (p. 38)

**Enunciado:** escreva a função `mdc`, que retorna o máximo divisor comum de dois inteiros: o maior inteiro que divide ambos sem deixar resto. Use o algoritmo de Euclides apresentado pelo professor:

```text
mdc(a, b) = a,                  se b = 0
mdc(a, b) = mdc(b, a mod b),     se b != 0
```

**Convenção para praticar:** inteiros não negativos, com pelo menos um positivo. O enunciado não define o tratamento de negativos; rejeite `(0, 0)` nesta versão.

**Dicas:** teste o caso base antes de calcular o resto, pois `% 0` é inválido. Rastreie como a chamada troca os argumentos e reduz o segundo até zero.

| `a` | `b` | MDC |
| --- | --- | --- |
| 18 | 12 | 6 |
| 11 | 7 | 1 |
| 12 | 18 | 6 |
| 8 | 8 | 8 |
| 9 | 0 | 9 |
| 0 | 9 | 9 |

## Perguntas de revisão do professor (p. 55)

1. **Qual é o protótipo de `printf`?** Dica: procure a declaração em `stdio.h`; observe retorno, primeiro parâmetro e reticências.
2. **A função `main` pode ser chamada recursivamente?** Dica: investigue as regras de C, distinguindo-as das de C++; considere condição de parada e organização do programa.

[Voltar ao índice](../README.md)
