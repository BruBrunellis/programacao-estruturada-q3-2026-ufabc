/*Enunciado: escreva a função menorBase, que recebe um inteiro positivo n e retorna o menor inteiro positivo b tal que b^k = n
para algum inteiro k. Não utilize a biblioteca math.h.

Convenção para praticar: adote k >= 1, como na interpretação da demonstração suplementar.
Assim, todo n positivo admite pelo menos a representação n^1, inclusive 1 = 1^1.

Dicas:

Teste bases em ordem crescente; a primeira que funcionar será a menor.
Construa potências por multiplicações sucessivas, sem pow.
Para base maior que 1, pare quando a potência alcançar ou ultrapassar n.
Trate n = 1 separadamente para não multiplicar por 1 indefinidamente.
Antes de multiplicar, pense no teste potencia > n / base para evitar ultrapassar n e prevenir estouro.

n	Menor base
1	1
9	3
16	2
17	17
64	2
*/

#include <stdio.h>

long long potencia(int base, int expoente);

int menorbase(int n);

int main(void){

    int n;

    scanf("%d", &n);

    int base = menorbase(n);

    printf("%d", base);

    return 0;
}

long long potencia(int base, int expoente){

    if(expoente == 0){
        return 1;
    }

    long long aux = potencia(base, expoente / 2);

    if(expoente % 2 == 0){
        return aux * aux;
    }

    return aux * aux * base;

}

int menorbase(int n){

    if (n == 1){return 1;}

    int base = 2;

    while(1){

        int resultado = 1;

        for(int k = 1; resultado <= n; k++){

            resultado = potencia(base, k);

            if(resultado == n)
                return base;
        }

        base++;
    }
}
