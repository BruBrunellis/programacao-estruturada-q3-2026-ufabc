/*
Laboratório 02 - Modularização
L02_02 - Cálculo de sen(x)

A série de Taylor para sen(x), centrada em zero (série de Maclaurin), é:

    sen(x) = x - x^3/3! + x^5/5! - x^7/7! + x^9/9! - ...

ou, em somatório:

    sen(x) = soma, para n de 0 até infinito, de
             (-1)^n * x^(2n+1) / (2n+1)!

Escreva um programa que implemente a função em C calcularSenoTaylor.
Ela deve receber um ângulo x, em radianos, e um número num_termos,
e retornar uma aproximação de sen(x) somando num_termos da série.

Assinatura da função:
    double calcularSenoTaylor(double x, int num_termos);

Especificação:
    Entrada: x real, em radianos, e num_termos >= 1.
    Saída: aproximação de sen(x) com 8 casas decimais.

Dicas do enunciado:
    - Em vez de recalcular potência e fatorial desde o início, cada termo
      pode ser obtido a partir do anterior:
      termo_(k+1) = termo_k * (-1) * x^2 / ((2k+2) * (2k+3)).
    - A entrada x deve estar em radianos.
    - Se a saída estiver arredondando, experimente long double no retorno.

Exemplos:
    Entrada: 1.57079632679 10
    Saída:   sen(1.57079633) = 1.00000000

    Entrada: 0.523598775598 8
    Saída:   sen(0.52359878) = 0.50000000
*/

#include <stdio.h>
#include <math.h>

double calcularSenoTaylor(double x, int num_termos) {
    double termo = x; // Primeiro termo da série, índice 0
    double soma = termo; // Inicializa a soma com o primeiro termo

    for (int n = 1; n < num_termos; n++) {
        // Calcula o próximo termo usando a relação de recorrência
        termo *= (-1) * (x * x) / ((2 * n) * (2 * n + 1));
        soma += termo; // Adiciona o termo à soma
    }

    return soma;
}

int main() {
    double x;
    int num_termos;

    // Lê os valores de x e num_termos
    scanf("%lf", &x);
    scanf("%d", &num_termos);

    // Calcula o seno usando a série de Taylor
    double resultado = calcularSenoTaylor(x, num_termos);

    // Imprime o resultado com 8 casas decimais
    printf("sen(%.8f) = %.8f\n", x, resultado);

    return 0;
}
