//Programa recebe 2 numeros inteiros e realizar 4 operações aritmeticas distintas

#include <stdio.h>

int main(void)
{
    int num1 = 0, num2 = 0;
    int op1, op2, op3;
    float numfloat, op4;

    scanf("%d %d", &num1, &num2);

    op1 = num1 + num2;
    op2 = num1 - num2;
    op3 = num1 * num2;

    numfloat = num1;
    op4 = numfloat / num2;

    printf("%d + %d = %d\n%d - %d = %d\n%d * %d = %d\n%d / %d = %f\n", num1, num2, op1, num1, num2, op2, num1, num2, op3, num1, num2, op4);

    return 0;
}
