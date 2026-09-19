/*Pré e pós incrementos,
Precedência de operadores*/

#include <stdio.h>

int main(void)
{
    int a = 10, b = 0, c = 10, d = 0;
    float div = 0;

    b = ++a; //incrementa 1 em a, b assume 2
    printf("b = ++a: b = %d, a = %d\n", a, b);

    d = c++; //d assume 10, c incrementa 1
    printf("d = c++: d = %d, c = %d\n", d, c);

    div = 35 / 3; // divisão de inteiros
    printf("div = 35/3: %f\n",div);

    div = 35 / 3.0; //divisão com real
    printf("div = 35/3.0: %f\n",div);

    /*Mesmo que div tenha sido definida como float, se dividirmos 2 inteiros, o resultado
    será um inteiro. Para que a saída seja como float, precisamos que pelo menos um dos termos seja em formato float*/

    int e = 0, f = 0;
    float resultado = 0.0f;

    resultado = ++e * (10 + 3) - 8 / 8 % 3 + (f + 5);

    /*
    e incrementa 1, e = 1
    (10+3) = 13, 13*1 = 13
    8 / 8 = 1
    1 % 3 = 1
    (f + 5) = 5
    13 - 1 + 5 = 17
    */

    printf("Resultado: %.2f\n", resultado);
    printf("e: %d\nf: %d\n", e, f);

    /*short-circuit evaluation
    && - and : deixa de avaliar o direito quando o esquerdo é falso
    || - or : deixa de avaliar o direito quando o esquerdo é verdadeiro
    ! - not
    */

    if ( (e++ > 2 && ++f < 1) || (!f++ || (e + f) > 2) )
        printf("Verdadeiro\n");
    else
        printf("Falso\n");

    printf("e = %d, f = %d\n", e, f);

    return 0;
}
