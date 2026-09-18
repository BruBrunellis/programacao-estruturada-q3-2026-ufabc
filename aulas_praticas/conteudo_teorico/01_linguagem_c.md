# Aula prática 01 — Linguagem C

Transcrição organizada pelo Codex de `PE/Aulas/01_PRATICA.pdf` (16 páginas), consultado em 18/09/2026. Acentuação e formatação foram normalizadas; cabeçalhos repetidos, nomes e contatos dos docentes foram omitidos. Os códigos e figuras relevantes também foram lidos nas imagens do PDF. Complementos técnicos aparecem em uma seção própria, sem serem atribuídos aos slides.

## Apresentação e roteiro (p. 1–3)

Disciplina: Programação Estruturada, UFABC, MCTA028-15. Aula 01 — Linguagem C, prática.

Roteiro do material: editor de código, compilação, execução e contatos. A seção de contatos pessoais (p. 16) foi omitida desta versão de estudo.

## Editor de código (p. 4)

A disciplina permite usar o editor de preferência do aluno. Exemplos citados no PDF:

- Ambientes de programação: VS Code, Dev-C++, Code::Blocks, Eclipse e NetBeans.
- Editores de texto sem formatação: Gedit, Notepad++, Vim, Bloco de Notas e Emacs.
- Editores online: [JDoodle para C](https://www.jdoodle.com/c-online-compiler) e [OneCompiler para C](https://onecompiler.com/c).

Segundo o material, projetos com vários fontes `.c` e cabeçalhos `.h` são normalmente mais bem gerenciados com uma IDE. Neste repositório, o ambiente escolhido é o VS Code; veja o [tutorial de configuração](../../README.md#preparar-outra-máquina).

## Criando um código-fonte C (p. 5)

Arquivos-fonte em C devem ter extensão `.c`. A orientação da aula é evitar acentos, espaços, caracteres especiais e cedilha em nomes de arquivos e pastas. O material lembra que o Linux diferencia maiúsculas de minúsculas.

Exemplo com Vim:

1. Abra um terminal Linux na pasta de trabalho e execute `vim codigo_exemplo.c`.
2. Pressione `i` ou `Insert` para começar a editar.
3. Ao terminar, pressione `Esc`, digite `:wq` e pressione `Enter` para salvar e sair.

O caractere `$` mostrado antes dos comandos nos slides representa o prompt do terminal; ele não deve ser digitado como parte do comando.

## Demonstração no editor Vim (p. 6)

A figura apresenta um programa que lê um inteiro N e informa a paridade dos números de 1 até N. Transcrição do código visível, com indentação normalizada:

```c
#include <stdio.h>

int main() {
    int N, i;

    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        if (i % 2 == 0) {
            printf("%d eh par\n", i);
        } else {
            printf("%d eh impar\n", i);
        }
    }

    return 0;
}
```

O exemplo executável está em [paridade.c](../../aulas_exemplos/aula_pratica_01/paridade.c), com adaptações explicitadas no [README da demonstração](../../aulas_exemplos/aula_pratica_01/README.md). O bloco acima preserva o exemplo da imagem; não inclui essas adaptações.

## Compilação e etapas do programa (p. 7–8)

O material define compilador como um programa que transforma código-fonte em linguagem de máquina, permitindo gerar um executável.

A figura da p. 7 detalha o percurso:

1. **Editor:** criação do programa e gravação em disco.
2. **Pré-processador:** tratamento das diretivas de pré-processamento.
3. **Compilador:** tradução para código objeto, armazenado em disco.
4. **Editor de ligação:** combinação do código objeto com bibliotecas para gerar o executável.
5. **Carregador:** carregamento do programa na memória.
6. **CPU:** execução das instruções, com armazenamento de resultados durante o processamento.

O slide apresenta o GCC como lançado em março de 1987, originalmente chamado GNU C Compiler e posteriormente GNU Compiler Collection, com suporte a diferentes arquiteturas.

No terminal Linux, dentro da pasta do código-fonte:

```sh
gcc -Wall codigofonte.c -o nomedoprograma
```

## Parâmetros do GCC apresentados no material (p. 9)

As descrições abaixo reproduzem o sentido apresentado no slide; as ressalvas técnicas estão ao final.

| Opção | Descrição no material |
| --- | --- |
| `-o` | Especifica o nome do arquivo de saída |
| `-ansi` | Ignora características não compatíveis com ISO C90 |
| `-std=c99` | Ignora características não compatíveis com ISO C99 |
| `-pedantic` | Mostra os avisos exigidos pelo ISO C |
| `-Wall` | Apresentado como habilitando todos os possíveis avisos |
| `-Werror` | Transforma avisos em erros |
| `-lm` | Adiciona suporte à biblioteca matemática |

Comando demonstrado:

```sh
gcc -ansi -pedantic -Wall -Werror codigo.c -o programa
```

O material observa que há outros parâmetros e orienta usar `-lm` ao utilizar `math.h`. As configurações deste repositório usam C17; o comando acima foi mantido por fazer parte da aula, não como uma alteração do padrão do projeto.

## Erros de compilação (p. 10–11)

Erros de compilação impedem a geração de um novo executável. Leia a mensagem emitida: ela costuma informar arquivo, linha, coluna e uma descrição do problema.

Na demonstração, foi retirado o ponto e vírgula após `printf("%d eh par\n", i)`. O compilador indica a falta de `;` antes de `}`, na linha 8, coluna 37 da versão mostrada na imagem. A numeração muda se o arquivo for reformatado.

Comando usado na demonstração:

```sh
gcc -ansi -pedantic -Wall -Werror codigo_exemplo.c -o programa
```

Situações listadas nos slides:

- Ponto e vírgula ausente ou em excesso.
- Parênteses, colchetes ou chaves não fechados.
- Variáveis não declaradas.
- Erros de digitação em palavras-chave ou identificadores.
- Confusão entre `=` e `==`.
- Tipos de dados incompatíveis.
- Cabeçalhos necessários não incluídos.

Algumas dessas situações também podem resultar em avisos ou erros de lógica, conforme esclarecido nos complementos.

## Executar o programa (p. 12)

No terminal Linux, use `./` antes do nome do executável:

```sh
./nomedoprograma
```

A imagem mostra a compilação e a execução:

```sh
gcc -Wall codigo_exemplo.c -o programa
./programa
```

Com entrada `5`, a sessão exibida é:

```text
Digite um numero inteiro positivo: 5
1 eh impar
2 eh par
3 eh impar
4 eh par
5 eh impar
```

O número 5 na primeira linha é digitado pelo usuário. Para listar arquivos e pastas, use `ls -la`. Se o programa ficar em repetição infinita ou precisar ser interrompido, use `Ctrl+C`.

## Manual do Linux (p. 13)

O manual é dividido em seções. A aula apresenta a seção 3 para consultar funções de bibliotecas, exemplificando a consulta à documentação de `scanf`:

```sh
man 3 scanf
```

Pressione `q` para sair do visualizador do manual.

## Comandos do Linux (p. 14)

A seção 1 trata de comandos. O exemplo do slide é `man ls` para consultar as opções de `ls`.

| Comando | Finalidade apresentada |
| --- | --- |
| `ls` | Listar arquivos e diretórios |
| `cd` | Navegar entre diretórios; `cd ..` retorna ao diretório pai |
| `cp` | Copiar arquivos ou diretórios, conforme as opções utilizadas |
| `mv` | Mover ou renomear arquivos e pastas |
| `rm` | Apagar arquivos ou pastas, conforme as opções utilizadas |

O material alerta que `rm` não oferece desfazer; confira o caminho antes de usá-lo. Consulte o manual para as opções de cada comando.

## Orientações das práticas e entrega (p. 15)

Resolva em C os exercícios propostos no Moodle a cada aula. O material permite realizar a resolução individualmente, em duplas ou em grupos, mas **o envio e a avaliação são individuais**, com correção automática por casos de teste.

O prazo é normalmente de uma semana. Após enviar, verifique o resultado da avaliação e se a solução foi aprovada em todos os casos de teste. Confirme o prazo específico no Moodle.

O PDF não apresenta uma lista de enunciados de atividades: a paridade é uma demonstração. Escreva suas soluções em [exercicios_aulas_praticas/aula_01](../exercicios_aulas_praticas/aula_01/README.md). O push para o GitHub não substitui o envio ao Moodle.

## Complementos e precisões técnicas do resumo

Estes esclarecimentos são adicionais à transcrição:

- `-Wall` habilita um conjunto amplo de avisos, mas não todos. `-Wextra` acrescenta outros diagnósticos. `-Werror` transforma os avisos emitidos em erros. `-pedantic`/`-Wpedantic` solicita diagnósticos relativos ao padrão selecionado; não é uma prova completa de conformidade. Referência: [opções de avisos do GCC](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html).
- Em C, `-ansi` equivale a `-std=c90`. `-std=c99` seleciona C99; selecionar o padrão não significa simplesmente descartar trechos incompatíveis. O projeto usa `-std=c17`; siga a exigência de cada atividade. Referência: [dialetos de C no GCC](https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html).
- `#include <math.h>` fornece declarações; `-lm` solicita a ligação com a biblioteca matemática quando necessária no ambiente. Apenas incluir o cabeçalho não implica que o programa precise efetivamente de símbolos dessa biblioteca. Na linha de compilação, coloque `-lm` depois dos fontes/objetos.
- `=` em lugar de `==` e um `;` extra podem formar código válido com comportamento errado. Nem todo erro de lógica é detectado pelo compilador. Sempre teste os resultados.
- Um erro de compilação não apaga necessariamente um executável antigo. Não confunda a execução desse arquivo com a versão recém-editada; execute depois de compilar com sucesso.
- No Windows/PowerShell, o exemplo deste repositório usa `.exe` e é iniciado com `.\paridade.exe` dentro da pasta correspondente. Os comandos e o manual descritos nos slides são do ambiente Linux; não se presume que `man` esteja instalado no Windows.
- O exemplo original não verifica o resultado de `scanf` e seu contador poderia ultrapassar o limite de `int` para N máximo. O arquivo executável acrescenta validação básica e adapta a contagem, mantendo a saída da demonstração para entradas positivas usuais. Para entradas fora da faixa de `int`, seria necessário um método de leitura com validação de faixa.
