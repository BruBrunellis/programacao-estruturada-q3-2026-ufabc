# Programação Estruturada — UFABC · Q3/2026

Repositório de estudo e prática em **C** da disciplina **MCTA028-15**. O GitHub guarda o histórico dos códigos para continuar as atividades em diferentes computadores.

**Remoto:** [BruBrunellis/programacao-estruturada-q3-2026-ufabc](https://github.com/BruBrunellis/programacao-estruturada-q3-2026-ufabc).

## Estrutura

```text
.
├── aulas_teoricas/        # Resumos em Markdown das aulas disponíveis em PE/Aulas
├── aulas_praticas/        # Exercícios realizados nas aulas práticas
│   └── aula_01/ola_mundo.c
├── exercicios_moodle/    # Atividades e soluções destinadas ao Moodle
├── exercicios_livres/    # Treino independente e exercícios solicitados ao Codex
├── .vscode/             # Compilação, execução, depuração e extensão recomendada
├── .editorconfig        # Convenções de edição
├── .gitattributes       # Tratamento de arquivos texto entre sistemas
├── .gitignore           # Binários, temporários e configurações locais
└── requirements.md      # Ferramentas necessárias
```

Use nomes sem espaços e sem acentos nos arquivos de código, por exemplo `aula_03/exercicio_01.c`. Um exercício independente corresponde a um programa com seu próprio `main`. As tarefas do VS Code compilam **somente o arquivo `.c` ativo e salvo**, sem juntar todos os exercícios.

## Preparar outra máquina

### 1. Conferir as ferramentas

No terminal do computador da faculdade, execute:

```text
git --version
gcc --version
gdb --version
```

Se já funcionarem, use o ambiente instalado. Você precisa também do [VS Code](https://code.visualstudio.com/) e da extensão **C/C++**, da Microsoft (`ms-vscode.cpptools`). O editor e a extensão não incluem o compilador. Os requisitos estão em [requirements.md](requirements.md).

**Windows:** instale o [Git for Windows](https://git-scm.com/downloads/win) e o [MSYS2](https://www.msys2.org/), se faltarem. Abra o terminal **MSYS2 UCRT64** e instale as ferramentas:

```sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb
```

Adicione `C:\msys64\ucrt64\bin` ao `Path` do seu usuário (ajuste se escolheu outro local). Feche e reabra o VS Code e o terminal; confira `gcc --version` e `gdb --version` novamente. Utilize o GCC do UCRT64, não o GCC do ambiente MSYS. Em máquinas da faculdade sem permissão de instalação, solicite o ambiente ao suporte do laboratório.

**Linux Ubuntu/Debian:** se você administra a máquina, instale:

```sh
sudo apt update
sudo apt install git build-essential gdb
```

### 2. Clonar o repositório

Escolha uma pasta de trabalho no seu perfil de usuário. Abra um terminal nela e execute:

```sh
git clone https://github.com/BruBrunellis/programacao-estruturada-q3-2026-ufabc.git
cd programacao-estruturada-q3-2026-ufabc
code .
```

Se `code` não for reconhecido, abra o VS Code pelo menu e escolha **Arquivo → Abrir Pasta**, selecionando a pasta clonada. Aceite a confiança no seu próprio repositório e instale a extensão recomendada quando solicitado, ou procure `ms-vscode.cpptools` em **Extensões** (`Ctrl+Shift+X`).

Configure a autoria **dentro do repositório**. Substitua os valores abaixo pelo seu nome e pelo endereço `noreply` exibido em [GitHub → Settings → Emails](https://github.com/settings/emails):

```sh
git config user.name "SEU NOME"
git config user.email "SEU EMAIL NOREPLY DO GITHUB"
```

Essas configurações são locais ao clone; precisam ser repetidas em outra máquina. Elas identificam os commits, mas não autenticam o envio.

### 3. Compilar, executar e depurar

1. Abra `aulas_praticas/aula_01/ola_mundo.c` e salve com `Ctrl+S`.
2. Use `Ctrl+Shift+B` para compilar. Os avisos e erros aparecem no terminal e no painel **Problemas**.
3. Em **Terminal → Executar Tarefa**, selecione **C: compilar e executar arquivo ativo**. A saída esperada é `Ola, mundo! Ambiente C pronto para as aulas de PE.`
4. Para depurar, clique na margem de uma linha de código para marcar um ponto de parada, pressione `F5` e escolha **C: depurar arquivo ativo (GDB)**. Inspecione as variáveis e avance com `F10`.
5. Quando usar `scanf`, digite as entradas no terminal da execução, não no Console de Depuração.

O compilador usa C17, avisos (`-Wall -Wextra -Wpedantic`), informações de depuração (`-g`) e otimização desativada (`-O0`). Os executáveis ficam ao lado do fonte, com extensão `.exe` no Windows e `.out` no Linux, e são ignorados pelo Git. O diretório de trabalho nas tarefas é a pasta do arquivo ativo, o que também determina onde arquivos de entrada e saída relativos são procurados.

Também é possível compilar pelo terminal, a partir da raiz do repositório:

```powershell
# Windows / PowerShell
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 aulas_praticas/aula_01/ola_mundo.c -o aulas_praticas/aula_01/ola_mundo.exe -lm
.\aulas_praticas\aula_01\ola_mundo.exe
```

```sh
# Linux
gcc -std=c17 -Wall -Wextra -Wpedantic -g -O0 aulas_praticas/aula_01/ola_mundo.c -o aulas_praticas/aula_01/ola_mundo.out -lm
./aulas_praticas/aula_01/ola_mundo.out
```

Para um programa dividido em arquivos, liste apenas os fontes desse programa no comando, por exemplo `gcc -std=c17 -Wall -Wextra -Wpedantic main.c funcoes.c -o programa.out -lm` (no Windows, use `programa.exe`). Adapte a tarefa quando chegar à modularização; não compile juntos arquivos de exercícios distintos com vários `main`.

### 4. Autenticar para enviar ao GitHub

Como o repositório é público, baixar dispensa login. Para enviar alterações, autentique sua conta. No Windows, o Git Credential Manager incluído no Git for Windows pode abrir o navegador no primeiro `git push`.

Uma alternativa, com [GitHub CLI](https://cli.github.com/) instalado, é:

```sh
gh auth login
# Escolha GitHub.com, HTTPS e autenticação pelo navegador.
gh auth setup-git
```

Não use a senha da conta como senha do Git por HTTPS. Prefira o fluxo pelo navegador; nunca coloque tokens em arquivos ou na URL do remoto.

### 5. Rotina de cada aula

**Ao chegar**, abra seu clone existente e confira se há alterações locais antes de atualizar:

```sh
git status
git pull --ff-only
```

Se ainda não houver clone nesse computador, faça a clonagem da etapa 2. Se houver alterações pendentes, registre-as ou resolva-as antes de atualizar. A opção `--ff-only` interrompe a atualização quando as linhas de histórico divergirem.

**Ao terminar**, salve, compile, execute e confira o que será enviado:

```sh
git status
git diff
git add aulas_praticas/aula_01/ola_mundo.c
# Troque o caminho acima pelos arquivos que você criou ou alterou.
git diff --cached
git commit -m "Resolve exercicio da aula 01"
git push origin main
git status
```

Abra o repositório no GitHub e confira o commit. **Salvar no editor não faz commit; commit não faz push.** Só o push disponibiliza o trabalho na próxima máquina. Não use download ZIP para esse fluxo, pois ele não inclui o histórico e a configuração Git.

Se o push for rejeitado porque o remoto avançou, deixe seu trabalho salvo em commit e execute `git pull --rebase`. Em caso de conflito, revise os trechos indicados, remova os marcadores, execute `git add caminho/do/arquivo` e `git rebase --continue`. Para desistir dessa integração, use `git rebase --abort`. Depois, teste e repita o push; evite `push --force` neste fluxo.

### 6. Antes de sair de um computador compartilhado

Confirme o push e encerre a sessão do GitHub no navegador e no menu **Contas** do VS Code, se fez login. Se usou `gh`, execute `gh auth logout --hostname github.com`. Se o Git Credential Manager guardou acesso no Windows, remova a entrada do GitHub no **Gerenciador de Credenciais**. O logout do navegador, sozinho, não remove credenciais salvas pelo Git.

### Problemas comuns

| Sintoma | O que conferir |
| --- | --- |
| `gcc` ou `gdb` não reconhecido | Instalação, `PATH` e reinício completo do VS Code |
| `stdio.h` sublinhado | Extensão C/C++ instalada e **C/C++: Select IntelliSense Configuration** apontando para o GCC correto |
| Tentativa de compilar README ou outro arquivo | Deixe o `.c` desejado ativo e salve antes de executar |
| `multiple definition of main` | Compile um exercício por vez |
| Programa esperando sem mostrar resultado | Verifique se ele aguarda entrada no terminal |
| Executável antigo após erro | Corrija os erros e compile novamente; a configuração aborta a depuração quando a tarefa falha |
| Arquivo de dados não encontrado | Nas tarefas, caminhos relativos partem da pasta do `.c` |
| Erro de autenticação no push | Confira a conta autenticada e seu acesso ao remoto |

Referências do tutorial: [VS Code com GCC no Windows](https://code.visualstudio.com/docs/cpp/config-mingw), [extensão C/C++](https://code.visualstudio.com/docs/languages/cpp), [clonagem](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository), [atualização de um clone](https://docs.github.com/en/get-started/using-git/getting-changes-from-a-remote-repository) e [envio de commits](https://docs.github.com/en/get-started/using-git/pushing-commits-to-a-remote-repository).

## Plano de ensino

Síntese do arquivo local `PE/PLANO_DE_ENSINO_PROGRAMACAO_ESTRUTURADA_Q3_2026.pdf`, páginas 1–4, consultado em 17/09/2026. Identificação e contatos dos docentes foram omitidos. O planejamento é preliminar; acompanhe as atualizações no [Moodle UFABC](https://moodle.ufabc.edu.br/).

### Identificação e organização

- **Disciplina:** Programação Estruturada — MCTA028-15.
- **Instituição:** Universidade Federal do ABC, Centro de Engenharia, Modelagem e Ciências Sociais Aplicadas.
- **Período:** 2026, terceiro quadrimestre; turno diurno; campus Santo André.
- **Recomendação:** Processamento da Informação.
- **Teoria:** terça-feira, 10h–12h, sala A101-0.
- **Prática:** sexta-feira, 8h–10h, laboratórios L404-2 e L407-2, conforme a turma.
- **Atendimento previsto:** quintas e sextas, 10h–12h, sala 650-1, Bloco A; outros horários conforme disponibilidade e agendamento.
- **Ambiente da disciplina:** Moodle para materiais, comunicados e atividades. A primeira aula descreve aulas expositivas com resolução de exercícios e práticas de programação com VPL Moodle.

### Ementa

Algoritmos em níveis básico e intermediário; linguagens compiladas e compilação; programas em execução (processos); ponteiros; alocação estática e dinâmica de memória; vetores e matrizes; funções e passagem de parâmetros; registros; arquivos; recursividade. Aplicação dos conceitos à resolução de problemas clássicos e novos de computação.

### Objetivos

Compreender e desenvolver códigos em C; consolidar a lógica de programação; desenvolver algoritmos para modelar e resolver problemas técnico-científicos usando a linguagem C e o paradigma estruturado.

### Cronograma preliminar de 2026

| Semana | Teoria — terça-feira | Prática — sexta-feira |
| --- | --- | --- |
| 1 | **15/09:** linguagem C, operadores, condicionais e laços | **18/09:** compilação e exercícios de C |
| 2 | **22/09:** Semana das Engenharias / UFABC para todos | **25/09:** Semana das Engenharias / UFABC para todos |
| 3 | **29/09:** funções e recursividade | **02/10:** exercícios de funções e recursividade |
| 4 | **06/10:** vetores, matrizes e strings | **09/10:** exercícios de vetores e matrizes |
| 5 | **13/10:** ponteiros e alocação dinâmica | **16/10:** exercícios de alocação dinâmica |
| 6 | **20/10:** arquivos, estruturas e registros | **23/10:** exercícios de arquivos e registros |
| 7 | **27/10:** dúvidas sobre o trabalho | **30/10:** apresentação do trabalho, demonstração e arguição |
| 8 | **03/11:** tipos abstratos de dados — listas, pilhas e filas | **06/11:** apresentação do trabalho, demonstração e arguição |
| 9 | **10/11:** tipos abstratos de dados — listas, pilhas e filas | **13/11:** exercícios de listas, pilhas e filas |
| 10 | **17/11:** avaliação teórica de todo o conteúdo | **20/11:** Dia Nacional de Zumbi e da Consciência Negra |
| 11 | **24/11:** substitutiva da avaliação teórica | **27/11:** exercícios de listas, pilhas e filas |
| 12 | **01/12:** vista da avaliação | **04/12:** recuperação |
| Reposição | — | **11/12:** fechamento dos conceitos |

**Divergências entre os materiais:** os slides da aula 01, p. 6, indicam `20/10 e 06/11` para o trabalho; o plano indica `30/10 e 06/11`, datas adotadas acima. A p. 4 dos slides menciona quinta-feira para uma das práticas, enquanto o plano prevê sexta-feira. Confirme eventuais alterações no Moodle. Os slides também indicam uma semana para entrega dos EP; confira o prazo específico de cada atividade.

### Avaliações e conceitos

- **TR — Trabalho de Implementação:** em grupo, com apresentação obrigatória de todos os integrantes em 30/10 e 06/11.
- **AT — Avaliação Teórica:** individual e presencial, em 17/11.
- **EP — Exercícios de Programação:** realizados nas práticas, com entrega exclusivamente pelo Moodle e sem avaliação substitutiva. Fazer push não equivale a entregar a atividade.

O plano estabelece a ordem de importância **AT, TR e EP**, sem informar uma fórmula numérica de pesos. Em um trecho usa a sigla `AP`; aqui foi uniformizada para `AT`, conforme a descrição da avaliação e a tabela de exemplos do próprio documento.

| Conceito | Descrição resumida |
| --- | --- |
| A | Desempenho excepcional e excelente compreensão e uso da matéria |
| B | Bom desempenho e boa aplicação dos conceitos |
| C | Mínimo satisfatório, uso adequado e condições de prosseguir nos estudos |
| D | Mínimo não satisfatório, domínio parcial e necessidade de trabalho adicional |
| F | Reprovado |
| O | Reprovado por falta |

Exemplos apresentados no plano, com conceitos na ordem **AT/TR/EP**: `AAB` ou `BAA` resultam em A; `BBC` ou `CBB`, em B; `BCC` ou `CBC`, em C. Qualquer D, com os demais acima de D, resulta em D; qualquer F resulta em F. São os exemplos e regras descritos no documento, não uma tabela completa de todas as combinações.

**Substitutiva — 24/11:** segundo o plano, destina-se a quem faltou a uma avaliação regular e se enquadra na Resolução CONSEPE nº 227, de 23/04/2018. A justificativa válida e original deve ser enviada ao docente até 72 horas antes da substitutiva. Quem realizou todas as avaliações não tem direito à substitutiva.

**Recuperação — 04/12:** segundo o plano, para estudantes com conceito D ou F que concluíram e realizaram todas as atividades e avaliações regulares, conforme a Resolução CONSEPE nº 182, de 23/10/2014. Prova individual, sem consulta, sobre todo o conteúdo. O conceito máximo após a recuperação é C.

**Frequência:** inferior a 75% implica conceito O, conforme a regra do plano, que cita a Resolução CONSEPE nº 139. O estudante deve acompanhar suas faltas. As referências normativas acima são as citadas no material fornecido.

### Bibliografia básica

1. CORMEN, T. H.; LEISERSON, C. E.; RIVEST, R. L.; STEIN, C. **Algoritmos: teoria e prática**. 2. ed. Rio de Janeiro: Campus, 2002.
2. FORBELLONE, A. L. V.; EBERSPACHER, H. F. **Lógica de programação: a construção de algoritmos e estruturas de dados**. 3. ed. São Paulo: Prentice Hall, 2005.
3. PINHEIRO, F. A. C. **Elementos de programação em C**. Porto Alegre: Bookman, 2012.

### Bibliografia complementar

1. AGUILAR, L. J. **Programação em C++: algoritmos, estruturas de dados e objetos**. São Paulo: McGraw-Hill, 2008.
2. DROZDEK, A. **Estrutura de dados e algoritmos em C++**. São Paulo: Cengage Learning, 2009.
3. KNUTH, D. E. **The art of computer programming**. Upper Saddle River: Addison-Wesley, 2005.
4. SEDGEWICK, R. **Algorithms in C++: parts 1–4: fundamentals, data structures, sorting, searching**. Reading: Addison-Wesley, 1998.
5. SZWARCFITER, J. L.; MARKENZON, L. **Estruturas de dados e seus algoritmos**. 3. ed. Rio de Janeiro: LTC, 1994.
6. TENENBAUM, A. M.; LANGSAM, Y.; AUGENSTEIN, M. J. **Estruturas de dados usando C**. São Paulo: Pearson Makron Books, 1995.
7. FLANAGAN, D. **Java, o guia essencial**. 5. ed. Série O'Reilly. Bookman, 2006. ISBN 8560031073, 1099 p.
8. SEDGEWICK, R.; WAYNE, K. D. **Introduction to programming in Java: an interdisciplinary approach**. Boston: Pearson Addison-Wesley, 2007. 723 p.

Referências preservadas conforme o plano de ensino, sem revisão de edições ou datas. No original, a obra de Flanagan aparece concatenada ao item de Tenenbaum; foi separada aqui para facilitar a leitura.

## Materiais de estudo

O [índice de aulas teóricas](aulas_teoricas/README.md) lista os resumos disponíveis. Na preparação inicial havia apenas `01_TEORIA.pdf`; seu [resumo de linguagem C](aulas_teoricas/01_linguagem_c.md) identifica as páginas utilizadas e sinaliza correções técnicas. Os PDFs originais permanecem na pasta local PE e não integram este repositório.
