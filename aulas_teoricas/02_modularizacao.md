# Aula 02 — Modularização

Resumo de estudo preparado pelo Codex a partir de `PE/Aulas/02_Teoria.pdf` (56 páginas), consultado em 01/10/2026. Os [exemplos em C](../aulas_exemplos/aula_teorica_02/README.md) são adaptações didáticas, com correções e limites explicitados. O PDF original permanece na pasta local PE.

## 1. Por que usar funções? (p. 4–5)

Modularizar é dividir um problema em partes menores, com responsabilidades que possam ser compreendidas separadamente. Uma função reúne comandos e os executa quando é chamada. `printf` e `scanf` são funções que já usamos por meio da biblioteca padrão.

Funções permitem reaproveitar código, reduzir repetições e manter trechos menores. Uma alteração em um cálculo compartilhado pode ser feita em um único lugar. Prefira nomes que expressem a tarefa, como `soma`, `fatorial` ou `mdc`.

## 2. Definição, parâmetros e retorno (p. 6–10)

```c
int soma(int a, int b)
{
    int resultado = a + b;
    return resultado;
}
```

- `int` antes do nome é o tipo do valor retornado.
- `a` e `b` são parâmetros: variáveis locais inicializadas pelos valores recebidos na chamada.
- Em `soma(8, 13)`, `8` e `13` são argumentos. A chamada produz `21`.
- `return` encerra a execução daquela chamada e devolve o resultado a quem chamou.

No ambiente usual das aulas, a execução do programa começa em `main`. Ao chamar `soma`, o fluxo passa para ela e depois continua em `main`, usando o valor retornado. Veja [soma.c](../aulas_exemplos/aula_teorica_02/soma.c).

Uma função sem parâmetros deve usar `(void)` no C17 adotado pelo repositório. Uma função que não devolve valor usa retorno `void`:

```c
void imprimeMensagem(int resultado)
{
    printf("O resultado foi %d\n", resultado);
}
```

Esse trecho pressupõe `#include <stdio.h>`. Uma função `void` pode terminar ao alcançar a chave final ou usar `return;` para sair antecipadamente. Imprimir uma mensagem e retornar um valor são operações diferentes: a saída de `printf` aparece no terminal; o retorno de `soma` pode ser armazenado e usado em outra expressão.

## 3. Passagem por valor e protótipos (p. 10–12)

Em C, os argumentos são passados **por valor**. Alterar um parâmetro inteiro modifica a cópia local e não a variável usada na chamada.

```c
int incrementa(int numero)
{
    numero++;
    return numero;
}

/* Dentro de main: */
int original = 5;
int novo = incrementa(original); /* original = 5; novo = 6 */
```

Quando estudarmos ponteiros, uma função poderá alterar um objeto por meio de seu endereço; o próprio ponteiro também será passado por valor.

Um **protótipo** declara o tipo de retorno e os tipos dos parâmetros antes de a função ser usada:

```c
int soma(int a, int b);
```

A definição inclui o corpo entre chaves. Uma organização possível é: `#include` e constantes, protótipos, `main` e definições das demais funções. Se a definição completa já aparece antes da chamada, um protótipo separado não é necessário. Declaração, definição e chamada devem ser compatíveis.

## 4. Pilha de chamadas e variáveis locais (p. 14–30)

A aula representa chamadas por uma pilha: a última função chamada é a primeira a retornar, seguindo a ordem LIFO. Cada chamada tem seus próprios parâmetros e variáveis locais automáticas, mesmo que os nomes se repitam.

No exemplo de [fluxo_execucao.c](../aulas_exemplos/aula_teorica_02/fluxo_execucao.c), o percurso é:

```text
main: x = f2(2, 3)
  f2: a = 2, b = 3; aguarda c = f1(b, a)
    f1: a = 3, b = 2, c = 1; retorna 3 + 2 + 1 = 6
  f2: c = 6; retorna 3 + 6 - 2 = 7
main: x = 7
```

Use pontos de parada e a pilha de chamadas do depurador para acompanhar esse percurso. Não leia `c` ou `x` antes de sua atribuição terminar. A pilha é um modelo didático usual de implementação: C não exige que toda variável seja armazenada fisicamente nela, e objetos `static` têm duração diferente.

## 5. Recursão e fatorial (p. 31–34)

Uma função recursiva chama a si mesma, diretamente ou por meio de outras funções. Para terminar, precisa de:

1. **Caso base:** situação resolvida sem nova chamada recursiva.
2. **Passo recursivo:** transformação em um problema menor.
3. **Progresso:** cada sequência de chamadas deve alcançar o caso base.

Para inteiros não negativos, `0! = 1`, `1! = 1` e, para `n > 1`, `n! = n × (n − 1)!`.

```c
/* Pre-condicao desta adaptacao: 0 <= n <= 20. */
unsigned long long fatorial(int n)
{
    if (n <= 1) {
        return 1;
    }
    return n * fatorial(n - 1);
}
```

Para `fatorial(5)`, as chamadas descem até `fatorial(1)`. Na volta, os resultados são `1`, `2`, `6`, `24` e `120`. Cada multiplicação aguarda o resultado da chamada menor.

O [programa completo](../aulas_exemplos/aula_teorica_02/fatorial_recursivo.c) rejeita negativos e valores acima de 20. Esse limite permite representar o resultado em `unsigned long long`; apenas trocar o tipo não torna o fatorial ilimitado.

## 6. Fibonacci e chamadas repetidas (p. 35–36)

Adotando a fórmula do slide, `F(0) = 0`, `F(1) = 1` e `F(i) = F(i − 1) + F(i − 2)` para `i >= 2`. Assim, a sequência começa em `0, 1, 1, 2, 3, 5, 8`.

```c
/* Pre-condicao desta demonstracao: 0 <= i <= 30. */
unsigned long fibonacci(int i)
{
    if (i < 2) {
        return (unsigned long) i;
    }
    return fibonacci(i - 1) + fibonacci(i - 2);
}
```

O código da p. 35 diverge da fórmula no caso base e contém uma `/` solta; a versão acima corrige ambos. No cálculo de `F(6)`, por exemplo, `F(4)` é calculado mais de uma vez. A versão ingênua tem custo de tempo exponencial; a profundidade das chamadas cresce linearmente. O [exemplo](../aulas_exemplos/aula_teorica_02/fibonacci_recursivo.c) limita o índice a 30 para manter a execução curta. Uma versão iterativa ou com resultados armazenados evita esse retrabalho.

## 7. Exercícios e material suplementar (p. 13, 37–38 e 41–48)

Tente resolver os enunciados antes de consultar as demonstrações do material suplementar:

| Exercício | Ideia e casos para conferir | Demonstração adaptada |
| --- | --- | --- |
| Série de Euler — p. 13 e 41–42 | Somar os `n` primeiros termos de `1/k!`, de `k = 0` até `n − 1`; `n = 1` dá `1`, `n = 3` dá `2,5` | [serie_euler.c](../aulas_exemplos/aula_teorica_02/serie_euler.c) |
| Menor base — p. 13 e 43–45 | Encontrar o menor inteiro positivo `b` com `b^k = n`, admitindo `k >= 1`, sem `math.h`; `9 → 3`, `16 → 2`, `17 → 17`, `1 → 1` | [menor_base.c](../aulas_exemplos/aula_teorica_02/menor_base.c) |
| Potência recursiva — p. 37 e 46 | Usar `base × power(base, expoente − 1)`; `3^4 = 81` | [potencia_recursiva.c](../aulas_exemplos/aula_teorica_02/potencia_recursiva.c) |
| Dígitos invertidos — p. 37 e 47 | Extrair o último dígito com `% 10` e reduzir com `/ 10`; `7631 → 1367` | [digitos_invertidos.c](../aulas_exemplos/aula_teorica_02/digitos_invertidos.c) |
| MDC — p. 38 e 48 | Algoritmo de Euclides: se `b == 0`, devolver `a`; senão, calcular `mdc(b, a % b)`; `mdc(18, 12) = 6` e `mdc(11, 7) = 1` | [mdc_recursivo.c](../aulas_exemplos/aula_teorica_02/mdc_recursivo.c) |

Na série de Euler, use divisão de ponto flutuante, como `1.0 / fatorial(k)`. A demonstração preserva o limite de 10 termos do material.

Na menor base, as multiplicações do original podem estourar um `int`. A adaptação testa `resultado <= n / base` antes de multiplicar e só procura bases com `base <= n / base`. Se nenhuma potência com expoente pelo menos 2 funcionar, retorna `n`, pois `n^1 = n`.

O enunciado da potência pede expoente pelo menos 1; a solução suplementar também aceita 0, retornando 1. As duas demonstrações do repositório adotam essa extensão e convencionam `0^0 = 1` no programa. As bases ficam entre −10 e 10 e os expoentes entre 0 e 18, para evitar estouro de `long long`.

No exercício de inversão, o enunciado mistura “imprime” e “retorna”. A solução fornecida é `void` e **imprime** os dígitos: para `1200`, a saída é `0021`. O exemplo aceita também zero. Para MDC, a demonstração aceita inteiros não negativos, com pelo menos um positivo; rejeita `(0, 0)`.

## 8. Recursão versus iteração (p. 39)

| Aspecto | Iteração | Recursão |
| --- | --- | --- |
| Como repete | Laços como `for` e `while` | Novas chamadas de função |
| Como termina | Condição de continuação deixa de valer | Caso base é alcançado |
| Estado intermediário | Variáveis atualizadas no laço | Parâmetros e locais de cada chamada |
| Cuidados | Atualizar a condição e evitar laço infinito | Reduzir o problema, evitar chamadas excessivas e profundidade grande |

No modelo usual, o fatorial recursivo usa espaço proporcional a `n` na pilha; a versão iterativa pode usar espaço constante. Ambas realizam uma quantidade linear de multiplicações. Esses custos são complementos para comparar as estratégias, não uma regra de que toda recursão seja pior que qualquer laço.

## 9. Escopo local e global (p. 49–53)

O escopo determina onde um nome é visível. Parâmetros e variáveis locais pertencem à função ou ao bloco em que são declarados. Uma variável declarada fora das funções pode ser acessada pelas funções onde sua declaração estiver visível.

Uma variável local com o mesmo nome de uma global **oculta** a global naquele escopo. Em [escopo_variaveis.c](../aulas_exemplos/aula_teorica_02/escopo_variaveis.c), `y` é global e também é nome de parâmetro de `funA` e `funC`:

| Momento observado em `main` | `x_global` | `x_local_main` | `y` global |
| --- | --- | --- | --- |
| Antes das chamadas | 10 | 100 | 20 |
| Depois de `funA` | 120 | 100 | 20 |
| Depois de `funB` | 300 | 100 | 400 |
| Depois de atribuir o retorno de `funC` | 500 | 500 | 400 |

`funA` altera `x_global`, mas seu parâmetro `y` é uma cópia. `funB` altera as duas globais. `funC` modifica `x_global` e devolve seu `y` local; `main` recebe esse retorno por atribuição. Prefira parâmetros e retornos quando possível, pois globais podem criar dependências difíceis de acompanhar. As globais foram mantidas nesse exemplo para observar o fenômeno mostrado no slide.

## 10. Potência por divisão do expoente (p. 54)

Para reduzir o número de chamadas, calcule uma única vez a potência correspondente à metade inteira do expoente e guarde em `aux`:

- Expoente zero: resultado `1`.
- Expoente par `2k`: resultado `aux × aux`, com `aux = base^k`.
- Expoente ímpar `2k + 1`: resultado `aux × aux × base`.

```c
/* Mesmos limites de entrada de potencia_recursiva.c. */
long long power(int base, int expoente)
{
    if (expoente == 0) {
        return 1;
    }

    long long aux = power(base, expoente / 2);
    if (expoente % 2 == 0) {
        return aux * aux;
    }
    return aux * aux * base;
}
```

O slide usa incorretamente `aux * aux * aux` no ramo ímpar. Para `2^5`, a versão corrigida obtém `aux = 2^2 = 4` e retorna `4 × 4 × 2 = 32`.

A divisão por 2 reduz a profundidade para ordem logarítmica no expoente positivo, em comparação com a ordem linear da versão anterior. Veja [potencia_rapida.c](../aulas_exemplos/aula_teorica_02/potencia_rapida.c). Essa melhoria não elimina os limites numéricos do tipo usado.

## 11. Ajustes técnicos em relação aos slides

- **P. 9:** não se declara uma variável comum de tipo `void`; o tipo expressa ausência de valor de retorno nesse uso. Em C17, `int funcao();` não especifica os parâmetros em uma declaração; prefira `int funcao(void);` quando não há parâmetros.
- **P. 10:** C permite algumas conversões de argumentos para os tipos dos parâmetros. Ainda assim, confira quantidade, ordem e compatibilidade; o protótipo ajuda o compilador a verificar a chamada.
- **P. 14–30:** a pilha é um modelo usual para as chamadas, não uma exigência de armazenamento de todos os objetos da linguagem.
- **P. 34:** o teste `n <= 1` não valida o domínio do fatorial; negativos precisam ser rejeitados antes. O tamanho de `long` varia entre plataformas.
- **P. 35:** o caso base foi ajustado para retornar `i`, conforme a fórmula `F(0) = 0` e `F(1) = 1`; a `/` solta foi removida.
- **P. 41–42:** a leitura e o limite inferior da quantidade de termos foram validados; o fatorial usa `unsigned long` na adaptação.
- **P. 43–44:** a busca de potências foi reformulada para evitar multiplicações que ultrapassem `n` e reduzir as bases examinadas.
- **P. 46–48:** os programas agora leem e validam entradas; domínios e extensões aparecem no índice dos exemplos.
- **P. 51–52:** `funB` foi declarada e definida como `void funB(void)`, pois não devolve valor; o original a declara `int`, mas não retorna um resultado.
- **P. 54:** o ramo ímpar da potência rápida foi corrigido para `aux * aux * base`.

## 12. Perguntas de revisão e checklist (p. 55)

O material propõe investigar o protótipo de `printf` e se `main` pode ser chamada recursivamente. Consulte a declaração em `<stdio.h>` e discuta essas questões em aula; nos exercícios, prefira funções auxiliares para expressar a recursão.

- [ ] Consigo separar um problema em funções com responsabilidades claras.
- [ ] Distingo parâmetro, argumento, protótipo, definição e chamada.
- [ ] Sei explicar por que alterar um parâmetro inteiro não altera a variável original.
- [ ] Distingo imprimir uma saída de retornar um valor.
- [ ] Consigo acompanhar `main → f2 → f1 → f2 → main` no depurador.
- [ ] Identifico o caso base e demonstro que o passo recursivo se aproxima dele.
- [ ] Entendo por que Fibonacci ingênuo repete cálculos.
- [ ] Consigo prever a saída do exemplo de escopo.
- [ ] Testo zero, um, entradas inválidas e limites antes de confiar em resultados numéricos.
- [ ] Compilo cada demonstração separadamente e sem avisos.
