//Programa recebe 2 numeros inteiros e realizar 4 operações aritmeticas distintas

#include <stdio.h>

int main(void)
{
    int num1 = 0, num2 = 0;
    int op1, op2, op3;
    float op4;

    scanf("%d %d", &num1, &num2);

    op1 = num1 + num2;
    op2 = num1 - num2;
    op3 = num1 * num2;
    op4 = (float)num1 / num2;

    printf("%d + %d = %d\n%d - %d = %d\n%d * %d = %d\n", num1, num2, op1, num1, num2, op2, num1, num2, op3);

    if (num2 != 0)
    {
        printf("%d / %d = %.2f\n", num1, num2, op4);
    }
    else
    {
        printf("Erro: divisao por zero\n");
    }

    return 0;
}
