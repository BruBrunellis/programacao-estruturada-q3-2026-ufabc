/*Exercício Aula Teorica 01 - Crie um programa que leia os valores da base e
da altura de um triângulo e imprima o valor de sua área.*/

#include <stdio.h>
#include <windows.h>

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    float base, altura, area;

    printf("Cálculo da área do triângulo...\n");
    printf("Informe a base: ");
    scanf("%f", &base);

    printf("Informe a altura: ");
    scanf("%f", &altura);

    area = (base + altura) / 2;

    printf("A área do triangulo de base %.2f e altura %.2f é: %.2f",
    base, altura, area);

    return 0;

}
