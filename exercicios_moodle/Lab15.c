/*
Laboratório 04 - Alocação Dinâmica
L04_02 - Cifra Monoalfabética

Fonte: https://moodle.ufabc.edu.br/mod/vpl/view.php?id=87373
Consultado em 22/10/2026. Formatação normalizada para comentário em C.

Cifra Monoalfabética

Uma cifra monoalfabética é um método de criptografia por substituição
em que cada letra do alfabeto do texto claro é sempre mapeada para a
mesma letra do alfabeto cifrado, usando uma chave fixa (uma permutação
das 26 letras). Escolhe-se uma chave que define, para cada letra de a-z,
qual letra a substitui; todo "a" vira sempre a mesma letra, todo "b"
vira sempre a mesma letra, e assim por diante.

Importante: não é segura para uso moderno, pois pode ser quebrada
facilmente por análise de frequência e tentativas sistemáticas.

Implemente um programa em C que aplica a cifra monoalfabética em um
texto. Nesta cifra, cada letra de a a z do texto é substituída por outra
letra de a a z definida por uma chave de 26 caracteres (uma permutação
do alfabeto, sem repetição).

Simplificações:
    - O texto de entrada contém apenas letras minúsculas a-z,
      espaço e pontuação.
    - Não há cedilha (ç) nem caracteres acentuados
      (sem acentos ortográficos).
    - A chave possui exatamente 26 caracteres, todos no intervalo a-z,
      sem repetições.
    - Comprimento máximo do texto: 200 caracteres.

Entradas do programa:
    - Uma opção de função: E para encriptação ou D para decriptação.
    - Uma string de até 200 caracteres (apenas a-z, espaço e pontuação).
    - Uma chave de 26 caracteres (apenas a-z, sem repetição).

Saída do programa:
O texto resultante após aplicar a função escolhida:
    - E(texto claro, chave): retorna o texto encriptado.
    - D(texto cifrado, chave): retorna o texto decriptado.

Assinaturas das funções:
    char* encripta(char *texto, char *chave);
    char* decripta(char *cifra, char *chave);

Dicas do enunciado:
    - Detectar pontuação com <ctype.h>:
        isalpha((unsigned char)c)
    - Apenas letras 'a'..'z' são substituídas. Para qualquer outro
      caractere permitido (espaço/pontuação), copie diretamente
      para a saída.
    - Se for usar fgets após um scanf, inserir um getchar. Exemplo:
        scanf("%c", &modo);
        getchar();
        fgets(texto, sizeof(texto), stdin);

Exemplos:
Nos exemplos abaixo, a chave é a permutação:
    zyxwvutsrqponmlkjihgfedcba
em que 'a' -> 'z', 'b' -> 'y', ..., 'z' -> 'a'.

    Exemplo 1 - Entrada:
        E
        ola, mundo!
        zyxwvutsrqponmlkjihgfedcba
    Saída:
        loz, nfmwl!

    Exemplo 2 - Entrada:
        D
        loz, nfmwl!
        zyxwvutsrqponmlkjihgfedcba
    Saída:
        ola, mundo!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *encripta(char *texto, char *chave) {
    size_t tamanho = strlen(texto);
    char *resultado = malloc(tamanho + 1);
    if (resultado == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < tamanho; i++) {
        char c = texto[i];
        resultado[i] = (c >= 'a' && c <= 'z') ? chave[c - 'a'] : c;
    }
    resultado[tamanho] = '\0';
    return resultado;
}

char *decripta(char *cifra, char *chave) {
    char inversa[27];
    for (int i = 0; i < 26; i++) {
        inversa[chave[i] - 'a'] = (char)('a' + i);
    }
    inversa[26] = '\0';
    return encripta(cifra, inversa);
}

int main(void) {
    char modo;
    char texto[203]; // 200 caracteres, CR, LF e terminador nulo.
    char chave[27];

    if (scanf(" %c", &modo) != 1 || (modo != 'E' && modo != 'D')) {
        return 0;
    }

    // Consome apenas o restante da linha da opcao, preservando o texto.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    if (fgets(texto, sizeof(texto), stdin) == NULL) {
        return 0;
    }
    texto[strcspn(texto, "\r\n")] = '\0';
    if (strlen(texto) > 200 || scanf("%26s", chave) != 1 ||
        strlen(chave) != 26) {
        return 0;
    }

    int usadas[26] = {0};
    for (int i = 0; i < 26; i++) {
        if (chave[i] < 'a' || chave[i] > 'z' || usadas[chave[i] - 'a']) {
            return 0;
        }
        usadas[chave[i] - 'a'] = 1;
    }

    char *resultado = modo == 'E' ? encripta(texto, chave)
                                  : decripta(texto, chave);
    if (resultado == NULL) {
        return 1;
    }
    printf("%s\n", resultado);
    free(resultado);
    return 0;
}

