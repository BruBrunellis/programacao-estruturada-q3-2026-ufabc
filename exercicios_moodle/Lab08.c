/*
Laboratório 02 - Modularização
L02_03 - Encontrar Primos de Mersenne

Um primo de Mersenne é um número primo da forma M_i = 2^i - 1,
em que i também é primo. Nem todo 2^i - 1 é primo quando i é primo:
2^11 - 1 = 2047 = 23 * 89. Os primeiros primos de Mersenne são
3, 7, 31, 127 e 8191 (para i = 2, 3, 5, 7 e 13).

Escreva um programa que implemente a função em C encontrarPrimosMersenne.
Ela deve receber um número inteiro n e imprimir todos os primos de
Mersenne menores que n.

Assinatura da função:
    void encontrarPrimosMersenne(int limite_n);

Dicas do enunciado:
    - Os números de Mersenne crescem rapidamente. Garanta que o tipo de
      dados usado, por exemplo long long, comporte os valores calculados
      antes de atingir o limite.
    - A formatação faz parte do exercício: separe os números por vírgula
      e encerre a frase com ponto final.

Exemplos (texto de saída conforme o Moodle):
    Entrada: 1
    Saída:   Nenhum primo de Mersenne encontrado.

    Entrada: 10
    Saída:   Os primos de Mersenne menores que 10 sao: 3, 7.

    Entrada: 40
    Saída:   Os primos de Mersenne menores que 40 sao: 3, 7, 31.

    Entrada: 150
    Saída:   Os primos de Mersenne menores que 150 sao: 3, 7, 31, 127.
*/

#include <stdio.h>

void encontrarPrimosMersenne(int limite_n) {
    int encontrou = 0;

    for (int i = 2; ; i++) {
        long long mersenne = (1LL << i) - 1;
        if (mersenne >= limite_n) {
            break;
        }

        // O expoente primo não garante que o número de Mersenne seja primo.
        int primo = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                primo = 0;
                break;
            }
        }
        if (!primo) {
            continue;
        }

        for (long long j = 2; j * j <= mersenne; j++) {
            if (mersenne % j == 0) {
                primo = 0;
                break;
            }
        }
        if (!primo) {
            continue;
        }

        if (encontrou) {
            printf(", ");
        } else {
            printf("Os primos de Mersenne menores que %d sao: ", limite_n);
        }
        printf("%lld", mersenne);
        encontrou = 1;
    }

    if (!encontrou) {
        printf("Nenhum primo de Mersenne encontrado.");
    } else {
        printf(".");
    }
}

int main() {
    int limite_n;

    scanf("%d", &limite_n);

    encontrarPrimosMersenne(limite_n);

    return 0;
}
