# Requisitos do ambiente

Este projeto usa C e a biblioteca padrão. Não há dependências Python, `pip`, ambiente virtual ou necessidade de um `requirements.txt`.

| Ferramenta | Uso |
| --- | --- |
| Git | Clonar, registrar alterações e sincronizar com o GitHub |
| GCC com suporte a C17 | Compilar os arquivos `.c` |
| GDB | Depurar com pontos de parada no VS Code |
| Visual Studio Code | Editor das aulas práticas |
| Extensão `ms-vscode.cpptools` | IntelliSense e integração com o depurador |
| Conta GitHub e acesso à internet | Baixar e enviar os códigos |

No Windows, use GCC e GDB do MSYS2 UCRT64. No Linux (Ubuntu/Debian), use os pacotes `build-essential` e `gdb`. Os comandos `git`, `gcc` e `gdb` precisam estar no `PATH` do processo que abre o VS Code.

GitHub CLI (`gh`) é opcional e facilita a autenticação. Make e CMake não são necessários para exercícios com um único arquivo.

As configurações incluídas atendem Windows e Linux. No macOS, a compilação pode ser adaptada para Clang, mas a depuração exige uma configuração própria para LLDB; o perfil GDB incluído não foi preparado para esse sistema.

Consulte o [tutorial no README](README.md#preparar-outra-máquina) para instalar, verificar e usar essas ferramentas. O padrão C17 é uma escolha deste repositório; respeite o padrão e os parâmetros exigidos por cada atividade do Moodle.
