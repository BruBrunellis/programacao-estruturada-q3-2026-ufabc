/*
Laboratório 03 - Arranjos
L03_02 - Palíndromo

Implementação da Função palindromo

Crie um programa que implementa uma função em C que verifica se uma
string é um palíndromo, considerando as regras de normalização abaixo.
Uma string é um palíndromo se pode ser lida da mesma forma da esquerda
para a direita e da direita para a esquerda.

Regras:
    - Ignorar espaços e pontuação: comparar apenas caracteres
      alfanuméricos (letras e dígitos).
    - Ignorar diferenças entre maiúsculas e minúsculas: 'A' e 'a'
      devem ser tratados como equivalentes.
    - Considerar apenas ASCII básico: não é necessário tratar
      acentuação ou diacríticos, como "á" e "ç".
    - Tamanho máximo da string: 99 caracteres, além do terminador '\0'.

Assinatura da função:
    int palindromo(const char s[]);

Retorno:
    1 (true) se s for um palíndromo conforme as regras acima;
    0 (false) caso contrário.

Dicas do enunciado:
    Biblioteca <ctype.h>:
        isalnum(int c): verifica se um caractere é alfanumérico.
        tolower(int c): converte um caractere para sua versão minúscula.
        Ao passar caracteres para essas funções, faça um cast para
        (unsigned char) para evitar comportamento indefinido com
        caracteres que possam ter valores negativos.
        Exemplo: isalnum((unsigned char)s[i]).

    Biblioteca <string.h>:
        strlen(const char *s): retorna o número de caracteres da string.
        O tipo de retorno é size_t.

    Casos especiais:
        Uma string vazia ("") é considerada palíndromo por convenção.
        Strings com apenas um caractere, como "a", também são palíndromos.

Exemplos de entrada e saída:
    Entrada: arara
    Saída:   "arara" é palíndromo

    Entrada: Reviver
    Saída:   "Reviver" é palíndromo

    Entrada: A sacada da casa
    Saída:   "A sacada da casa" é palíndromo

    Entrada: ab
    Saída:   "ab" não é palíndromo

    Entrada: palindromo
    Saída:   "palindromo" não é palíndromo

    Entrada: abc123
    Saída:   "abc123" não é palíndromo
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

int palindromo(const char string[]) {
    // Implementação da função palindromo
    // Esta função deve verificar se a string s é um palíndromo
    // de acordo com as regras especificadas no enunciado.

    // Variáveis para armazenar os índices de início e fim da string
    int left = 0;
    int right = strlen(string) - 1;

    while (left < right) {
        // Ignorar caracteres não alfanuméricos do lado esquerdo
        while (left < right && !isalnum((unsigned char)string[left])) {
            left++;
        }
        // Ignorar caracteres não alfanuméricos do lado direito
        while (left < right && !isalnum((unsigned char)string[right])) {
            right--;
        }

        // Comparar os caracteres em minúsculas
        if (tolower((unsigned char)string[left]) != tolower((unsigned char)string[right])) {
            return 0; // Não é palíndromo
        }

        left++;
        right--;
    }

    return 1; // É palíndromo
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    char input[100];

    // Solicitar entrada do usuário
    printf("Digite uma string (max 99 caracteres): ");
    fgets(input, sizeof(input), stdin);

    // Remover o caractere de nova linha, se presente
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    // Verificar se a string é palíndromo
    if (palindromo(input)) {
        printf("\"%s\" é palíndromo\n", input);
    } else {
        printf("\"%s\" não é palíndromo\n", input);
    }

    return 0;
}
