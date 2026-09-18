# Aula prática 01 — Paridade

Fonte: `PE/Aulas/01_PRATICA.pdf`, imagem de código da p. 6 e execução da p. 12. A [transcrição da aula](../../aulas_praticas/conteudo_teorico/01_linguagem_c.md) inclui o código original.

[paridade.c](paridade.c) lê N e classifica cada número de 1 até N como par ou ímpar. É uma demonstração dos slides, não uma solução de atividade do Moodle.

Adaptações em relação à imagem: `int main(void)`, conferência do retorno de `scanf` e rejeição de N não positivo. O contador vai de 0 até N−1 e o número exibido é `i + 1`, evitando incrementar um `int` além do seu limite na última iteração. Informe números representáveis por `int`; a leitura com `%d` não é uma validação de inteiros arbitrariamente grandes.

Entrada da demonstração: `5`. Saída no terminal interativo:

```text
Digite um numero inteiro positivo: 5
1 eh impar
2 eh par
3 eh impar
4 eh par
5 eh impar
```

O `5` na primeira linha é a entrada digitada, não uma segunda impressão do programa. Também teste `1` e `2`. Entradas `0`, `-1` e `abc` devem ser rejeitadas com retorno 1.

No VS Code, abra `paridade.c` e use a tarefa **C: compilar e executar arquivo ativo**. O arquivo também é compatível com o modo C90 usado na demonstração do PDF. Para compilar a partir da raiz do repositório:

```sh
gcc -ansi -pedantic -Wall -Werror aulas_exemplos/aula_pratica_01/paridade.c -o aulas_exemplos/aula_pratica_01/paridade.out
./aulas_exemplos/aula_pratica_01/paridade.out
```

No Windows, troque a saída por `paridade.exe` e execute `.\aulas_exemplos\aula_pratica_01\paridade.exe` no PowerShell. As tarefas padrão do projeto continuam usando C17.
