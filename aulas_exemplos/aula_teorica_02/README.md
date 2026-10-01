# Aula teórica 02 — Modularização

Demonstrações adaptadas de `PE/Aulas/02_Teoria.pdf` (56 páginas), consultado em 01/10/2026. Consulte o [resumo da aula](../../aulas_teoricas/02_modularizacao.md) para conceitos, referências e correções dos slides. Cada `.c` é um programa independente com seu próprio `main`.

## Funções e recursão

| Arquivo | Origem | O que observar | Entrada → resultado |
| --- | --- | --- | --- |
| [soma.c](soma.c) | P. 7–8 | Parâmetros, retorno e protótipo | Sem entrada → `21` |
| [fluxo_execucao.c](fluxo_execucao.c) | P. 14–30 | Chamadas `main`, `f2` e `f1`; locais de cada função | Sem entrada → `x = 7` |
| [fatorial_recursivo.c](fatorial_recursivo.c) | P. 33–34 | Caso base e retorno das chamadas | `5` → `5! = 120`; `0` → `0! = 1` |
| [fibonacci_recursivo.c](fibonacci_recursivo.c) | P. 35–36 | Duas chamadas recursivas e cálculos repetidos | `6` → `F(6) = 8`; `0` → `F(0) = 0` |

## Material suplementar

Os cinco primeiros arquivos abaixo adaptam as soluções que já constam no PDF. Tente os enunciados das p. 13 e 37–38 antes de consultá-los.

| Arquivo | Origem | O que observar | Entrada → resultado |
| --- | --- | --- | --- |
| [serie_euler.c](serie_euler.c) | P. 41–42 | `main` chama `euler`, que chama `fatorial` | `3` → `n = 3, e = 2.5000000000` |
| [menor_base.c](menor_base.c) | P. 43–45 | Potências inteiras sem `math.h` | `9 → 3`, `16 → 2`, `17 → 17` |
| [potencia_recursiva.c](potencia_recursiva.c) | P. 46 | Expoente reduzido de um em um | `2 5` → `2^5 = 32` |
| [digitos_invertidos.c](digitos_invertidos.c) | P. 47 | Função `void` com impressão e recursão | `7631 → 1367`; `1200 → 0021` |
| [mdc_recursivo.c](mdc_recursivo.c) | P. 48 | Algoritmo de Euclides | `18 12` → `mdc(18, 12) = 6` |
| [escopo_variaveis.c](escopo_variaveis.c) | P. 51–53 | Globais, parâmetros e passagem por valor | Sem entrada; última linha: `7 - main: x_global = 500, x_local_main = 500, y = 400` |
| [potencia_rapida.c](potencia_rapida.c) | P. 54 | Expoente dividido por 2 e resultado intermediário reutilizado | `2 5` → `2^5 = 32` |

## Adaptações e limites

- Todos os programas usam C17, `main(void)` e formatos de saída compatíveis com os tipos. Os programas interativos verificam o retorno de `scanf` e o domínio esperado. Digite valores representáveis pelo tipo lido.
- O fluxo de execução imprime `x`, permitindo conferir o resultado que os slides mostram na pilha.
- O fatorial aceita `0 <= n <= 20` e usa `unsigned long long`, evitando estouro nesse intervalo.
- Fibonacci usa `F(0) = 0` e `F(1) = 1`, corrigindo o código da p. 35 conforme a fórmula. O índice vai de 0 a 30 para limitar o tempo da recursão ingênua; o retorno usa `unsigned long`.
- Euler mantém o limite de 10 termos e passa a exigir pelo menos 1. O fatorial iterativo usa `unsigned long`, suficiente para os fatoriais até `9!` usados nessa soma.
- A menor base aceita um `int` positivo. A busca foi reformulada: testa limites por divisão antes de multiplicar e retorna `n` quando a representação mínima usa expoente 1.
- As duas potências aceitam bases de −10 a 10 e expoentes de 0 a 18, mantendo os resultados em `long long`. O caso de expoente 0 segue o suplemento, inclusive a convenção `0^0 = 1`. Na potência rápida, foi corrigido o ramo ímpar para multiplicar por `base`, em vez de multiplicar por `aux` uma terceira vez.
- A inversão aceita `long long` não negativo e imprime os dígitos; não devolve um inteiro invertido. O zero foi incluído como extensão.
- O MDC aceita dois `int` não negativos, com pelo menos um positivo. O par `(0, 0)` é rejeitado.
- No exemplo de escopo, `funB` passou a ter retorno `void`. As globais e o parâmetro `y` com o mesmo nome da global foram mantidos intencionalmente para reproduzir a explicação dos slides.

Esses arquivos são referências de estudo. As soluções do aluno continuam nas pastas de exercícios apropriadas; os programas aqui incluem mensagens interativas e não devem ser enviados ao Moodle sem conferir o formato exigido.

## Compilar e executar

No VS Code, abra um `.c`, salve e use **C: compilar e executar arquivo ativo**. Para acompanhar as chamadas, marque pontos de parada nas funções e pressione `F5`.

No terminal, a partir da raiz do repositório:

```powershell
# Windows / PowerShell
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 aulas_exemplos/aula_teorica_02/fatorial_recursivo.c -o aulas_exemplos/aula_teorica_02/fatorial_recursivo.exe
.\aulas_exemplos\aula_teorica_02\fatorial_recursivo.exe
```

```sh
# Linux
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 aulas_exemplos/aula_teorica_02/fatorial_recursivo.c -o aulas_exemplos/aula_teorica_02/fatorial_recursivo.out
./aulas_exemplos/aula_teorica_02/fatorial_recursivo.out
```

Compile somente um desses arquivos por vez: eles têm funções e `main` independentes. Os binários são ignorados pelo Git.
