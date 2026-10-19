/*
Enunciado: escreva uma função que receba um inteiro positivo e imprima seus dígitos na ordem inversa. Exemplo do professor: 7631 deve produzir 1367.

Ambiguidade do original: o texto usa “imprime” e “retornar”. Adote impressão dos dígitos, conforme a função void da solução suplementar (p. 47). Assim, 1200 produz 0021.

Dicas:

O resto por 10 identifica o último dígito; a divisão inteira por 10 o remove.
Aproveite o tema da aula e construa uma versão recursiva, escolhendo um caso base.
Diferencie imprimir cada dígito de construir um novo valor inteiro.
Entrada	Dígitos impressos
7631	1367
7	7
1200	0021
1001	1001
Aceitar zero e imprimir 0 é uma extensão opcional ao domínio positivo original.
*/

#include <stdio.h>

void digitoinverso(int n);

int main(void){

    int n;

    scanf("%d", &n);

    digitoinverso(n);

    return 0;
}

void digitoinverso(int n){

    if(n == 0 || n < 10){
        printf("%d", n);
    }

    while (n > 0){

        int digito = n % 10;

        printf("%d", digito);

        n = n / 10;

    }

}

