# Aula 01 — Linguagem C

Resumo de estudo preparado pelo Codex a partir de `PE/Aulas/01_TEORIA.pdf` (51 páginas), consultado em 17/09/2026. Exemplos abaixo são adaptações didáticas. Os ajustes técnicos estão explicitados ao final; para datas e avaliações, consulte o [plano de ensino no README](../README.md#plano-de-ensino).

## 1. Programação estruturada e compilação (p. 8–12)

O paradigma estruturado organiza algoritmos por sequência, seleção, repetição e modularização. C é uma linguagem de propósito geral, imperativa e procedural, normalmente compilada: o código-fonte é transformado em um programa executável.

Como complemento ao slide, o fluxo usual inclui pré-processamento (`#include`, `#define`), compilação, montagem e ligação com bibliotecas. Depois disso, o sistema operacional executa o programa. Editar o `.c` não altera um executável já compilado: é preciso recompilar.

```c
#include <stdio.h>

int main(void)
{
    printf("Ola, mundo!\n");
    return 0;
}
```

- `#include <stdio.h>` disponibiliza declarações de funções de entrada e saída.
- `main` é a função inicial de um programa no ambiente usual das aulas; `int main(void)` informa que não recebe argumentos.
- As chaves delimitam blocos e o ponto e vírgula encerra instruções.
- `\n` representa uma quebra de linha.
- Retornar zero de `main` indica sucesso; use um valor não zero para sinalizar falha nos exercícios.
- `//` comenta uma linha; `/* ... */` delimita um comentário de bloco.

## 2. Variáveis, constantes e escopo (p. 13–17 e 41–44)

Toda variável tem um tipo, um nome e um valor armazenado. Identificadores diferenciam maiúsculas e minúsculas. Para os exercícios, use letras ASCII, dígitos e `_`, sem iniciar por dígito e sem usar palavras reservadas. Prefira nomes como `quantidade` e `soma`.

```c
int quantidade = 3;
char letra = 'A';
float temperatura = 23.5f;
double media = 0.0;
const double pi = 3.141592653589793;
```

`int` representa inteiros, `char` representa valores de caracteres e `float`/`double` representam valores de ponto flutuante. Strings são sequências de caracteres terminadas por `\0`, frequentemente armazenadas em vetores. `'A'` é um caractere; `"A"` é uma string.

`#define LIMITE 100` define uma macro substituída pelo pré-processador. `const` qualifica um objeto que não deve ser modificado por esse nome; não funciona exatamente como uma macro. `void` é um tipo que representa ausência de valor: por exemplo, uma função sem retorno de valor ou uma lista sem parâmetros escrita `(void)`.

Variáveis declaradas dentro de blocos têm escopo local. As locais automáticas normalmente existem durante a execução do bloco; locais `static` têm duração diferente. Variáveis declaradas fora de funções têm escopo de arquivo, a partir da declaração, e podem ser usadas onde estiverem visíveis. Prefira locais e passagem de parâmetros quando possível.

Inicialize variáveis antes de ler seus valores. Não presuma tamanhos fixos dos tipos: use `sizeof` e os limites de `<limits.h>`/`<float.h>`. `unsigned` também representa zero. Em plataformas usuais com ponto flutuante IEEE 754, `float` oferece aproximadamente 6–7 dígitos significativos e `double`, 15–16; isso não é uma quantidade fixa de casas após a vírgula.

## 3. Entrada e saída (p. 18–21)

`printf` formata a saída; `scanf` lê conforme um formato. Para variáveis escalares, `scanf` normalmente recebe o endereço, indicado por `&`.

| Tipo | Leitura com `scanf` | Saída com `printf` |
| --- | --- | --- |
| `int` | `%d` | `%d` |
| `unsigned int` | `%u` | `%u` |
| `long int` | `%ld` | `%ld` |
| `float` | `%f` | `%f` |
| `double` | `%lf` | `%f` |
| `char` | `%c` | `%c` |
| String em vetor de `char` | `%s`, com limite de largura | `%s` |

Em `printf`, um `float` é promovido a `double`; `%.2f` exibe duas casas decimais. Já `scanf` distingue os ponteiros para `float` e para `double`. O retorno de `scanf` informa quantas conversões foram concluídas.

```c
#include <stdio.h>

int main(void)
{
    double valor;
    if (scanf("%lf", &valor) != 1) {
        fprintf(stderr, "Entrada invalida.\n");
        return 1;
    }
    printf("Valor: %.2f\n", valor);
    return 0;
}
```

Um espaço antes de `%c`, como em `scanf(" %c", &operador)`, ignora espaços e quebras de linha anteriores. Para `char nome[20]`, `%19s` limita a leitura e reserva espaço para `\0`; `%s` para no primeiro espaço em branco. A leitura de linhas completas será estudada com strings.

A aula usa cálculos de área de círculo, IMC e área de triângulo para praticar entrada, expressão e saída. Verifique condições matemáticas como denominadores diferentes de zero. Nos exercícios do Moodle, imprima apenas o formato exigido pelo enunciado.

## 4. Operadores (p. 22–25 e 45–49)

| Grupo | Operadores |
| --- | --- |
| Aritméticos | `+`, `-`, `*`, `/`, `%` |
| Incremento/decremento | `++`, `--` |
| Atribuição | `=`, `+=`, `-=`, `*=`, `/=`, `%=` |
| Relacionais e igualdade | `<`, `<=`, `>`, `>=`, `==`, `!=` |
| Lógicos | `&&`, `||`, `!` |
| Condicional | `condicao ? valor_se_verdadeira : valor_se_falsa` |

- `=` atribui; `==` compara.
- `35 / 3` resulta em `11` porque ambos os operandos são inteiros. Atribuir esse resultado a um `float` depois não recupera a parte fracionária.
- `35 / 3.0` ou `(double) 35 / 3` realiza divisão de ponto flutuante.
- `%` calcula o resto da divisão inteira; divisão por zero é inválida.
- `b = ++a` incrementa `a` antes de fornecer seu valor; `b = a++` fornece o valor anterior e incrementa `a`.
- Zero é falso; valores diferentes de zero são verdadeiros. Comparações e operadores lógicos produzem `0` ou `1`.
- `&&` deixa de avaliar o lado direito quando o esquerdo é falso; `||` deixa de avaliá-lo quando o esquerdo é verdadeiro. Esse curto-circuito permite, por exemplo, `divisor != 0 && numero / divisor > 2`.

Entre os operadores estudados, a precedência decresce aproximadamente nesta sequência: pós-incremento/decremento; unários (`!`, sinais, pré-incremento/decremento); `* / %`; `+ -`; relacionais; igualdade; `&&`; `||`; ternário; atribuições. Use parênteses para tornar a intenção clara. **Precedência não determina, em geral, a ordem de avaliação dos operandos**; evite alterar uma variável várias vezes em uma mesma expressão.

A expressão de curto-circuito das p. 24–25 produz `resultado = 17.00`, inicialmente `a = 1, b = 0`, escolhe o ramo verdadeiro e termina com `a = 2, b = 1`. Faça um teste de mesa observando quais incrementos realmente são executados.

Conversões explícitas usam casts: `(int) 28.99` resulta em `28` quando o valor é representável. Conversões não garantem preservação dos dados: inteiros grandes podem perder precisão ao serem convertidos para `float`.

## 5. Condicionais (p. 26–32 e 47)

Use `if` para uma decisão, `else` para a alternativa e `else if` para condições adicionais. As chaves ajudam a evitar ambiguidades, mesmo em blocos de uma linha.

```c
if (numero > 0) {
    printf("Positivo\n");
} else if (numero < 0) {
    printf("Negativo\n");
} else {
    printf("Zero\n");
}
```

`switch` seleciona ramos a partir de uma expressão de tipo inteiro, incluindo `char`. Os rótulos `case` são constantes inteiras. `break` evita continuar no próximo caso; `default` trata os demais valores. Uma calculadora com `+`, `-`, `*` e `/` é um exemplo de aplicação. Verifique divisão por zero e operador desconhecido.

O ternário permite expressar escolhas curtas: `int maior = (a > b) ? a : b;`.

## 6. Repetições (p. 33–36 e 50–51)

| Estrutura | Quando testa | Uso típico |
| --- | --- | --- |
| `for` | Antes de cada execução do corpo | Contador com inicialização e atualização bem definidas |
| `while` | Antes do corpo | Repetir enquanto uma condição permanecer verdadeira |
| `do ... while` | Depois do corpo | Executar ao menos uma vez |

```c
for (int i = 0; i < 3; i++) {
    printf("%d\n", i);
}
```

A ordem do `for` é: inicialização, teste, corpo, atualização, novo teste. No `do ... while`, há ponto e vírgula após a condição final.

`break` encerra o laço ou `switch` mais interno. `continue` pula o restante da iteração: em `for`, segue para a atualização; em `while`/`do ... while`, para o teste. Garanta que a condição possa mudar, para evitar laços infinitos.

Para procurar maior e menor entre `n > 0` valores, inicialize ambos com o primeiro valor lido. Inicializar o maior com zero falha quando todos os dados são negativos. Valide `n` antes de tentar ler o primeiro elemento.

## 7. Exemplos e exercícios para revisar (p. 21, 27–29, 31–32, 34 e 37–40)

A aula também usa `rand`, `srand` e `<stdlib.h>` em simulações de dados. `1 + rand() % 6` gera valores entre 1 e 6, mas pode ter um pequeno viés; sequências exatas não são portáveis entre implementações. Trata-se de um recurso didático de pseudoaleatoriedade.

Exercícios presentes no material, sem reproduzir os gabaritos:

1. Ler base e altura e calcular a área de um triângulo.
2. Classificar um ano como bissexto: divisível por 4 e não por 100, ou divisível por 400. Testar 2024, 1900 e 2000.
3. Implementar uma calculadora de duas entradas e um operador.
4. Contar algarismos 7 em um inteiro positivo: `7657` contém dois.
5. Converter um inteiro positivo decimal para binário. **999 em decimal é `1111100111` em binário.**

Para extrair algarismos decimais, use resto por 10 e divisão inteira por 10. Para a conversão binária, os restos por 2 aparecem do menos significativo para o mais significativo e precisam ser exibidos na ordem adequada. Guardar os dígitos binários como se fossem um número decimal, como no exemplo dos slides, limita rapidamente a entrada por estouro; posteriormente, prefira vetor de caracteres ou impressão apropriada.

## 8. Ajustes técnicos em relação aos slides

Estas observações são complementos e correções do resumo:

- **P. 13:** `void` é um tipo da linguagem, embora não permita declarar um objeto comum com valor desse tipo.
- **P. 20:** `sizeof(char)` é 1, mas a quantidade de bits por byte e o sinal de `char` dependem da implementação. O intervalo de `char` não é universalmente −128 a 127.
- **P. 22:** o operador de “maior que” é `>`, não `<`.
- **P. 37:** `1100011` corresponde a 99, não a 999; o binário de 999 foi corrigido acima.
- **P. 40:** `unsigned long long` deve ser impresso com `%llu`, não `%lld`. A estratégia de armazenar dígitos binários em um inteiro decimal pode transbordar.
- **P. 41:** os tamanhos de `int` e `long` dependem da implementação e do modelo de dados; `long` não é sempre de 8 bytes, nem mesmo em todos os sistemas de 64 bits.
- **P. 42:** precisão se refere a dígitos significativos, não a um número fixo de casas decimais.
- **P. 45:** a linha de operadores pós-fixos tem indicação inadequada de associatividade no slide; operadores pós-fixos associam da esquerda para a direita. Associatividade e ordem de avaliação são conceitos distintos.
- **P. 48–49:** conversões entre tipos podem perder precisão; converter qualquer `int` para `float` não é sempre exato.

## 9. Checklist de aprendizagem

- [ ] Consigo explicar o que acontece entre salvar um `.c` e executar o programa.
- [ ] Sei escolher tipos e formatos de entrada/saída compatíveis.
- [ ] Distingo atribuição, comparação e divisão inteira.
- [ ] Consigo simular um `if`, um `switch` e um laço no papel.
- [ ] Entendo curto-circuito sem depender de expressões com muitos efeitos colaterais.
- [ ] Valido entradas e evito divisão por zero.
- [ ] Compilo sem avisos e testo exemplos e casos de borda.
- [ ] Consigo fazer commit, push e retomar o exercício em outra máquina.
