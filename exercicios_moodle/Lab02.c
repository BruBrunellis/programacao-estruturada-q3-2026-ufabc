/*Neste laboratório, seu objetivo é ajudar os generais gregos (que não são tão meticulosos com cálculos) durante a greve dos matemáticos impulsionada pela crise. Para tanto, você deve escrever um programa em linguagem C, que avalia se uma determinada cidade deve ou não ser atacada. Seu programa receberá um número inteiro com o valor do perímetro da cidade alvo e deve determinar se seu perímetro é triangular e/ou perfeito.

A entrada consiste de um número inteiro positivo representando o perímetro de uma possível cidade alvo. Todos os números da entrada serão representados com o tipo de dado int

A saída do programa deve ser:

"Paz", quando o perímetro é perfeito e triangular ao mesmo tempo;
"Pensar", quando o perímetro não é perfeito mas é triangular ou quando este perímetro é perfeito mas não é triangular;
"Atacar", quando o perímetro não é triangular, nem perfeito.

Obs. Nomear como cidade.c no moodle*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    int num = 0, check_tri = 0, check_perf = 0, calc = 1, sum_perf = 0;
    float raizt;

    printf("Digite o perimetro: ");
    scanf("%d", &num);

    raizt = sqrt(num * 8 + 1);
    if ((int)raizt * (int)raizt == num * 8 + 1)
        check_tri = 1;

    if (num < 6)
        check_perf = 0;
    else
        for (calc; calc < num; calc++)
        {
            if (num % calc == 0)
                sum_perf += calc;
        }
        if (sum_perf == num)
            check_perf = 1;

    if (check_tri && check_perf == 1)
        printf("Paz");
    else if (check_tri || check_perf == 1)
        printf("Pensar");
    else
        printf("Atacar");

    return 0;
}
