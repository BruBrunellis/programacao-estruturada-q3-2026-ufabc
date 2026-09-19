#include <stdio.h>

int main(void)
{
    float peso, altura, imc;

    printf("Informe o peso (kg): ");
    scanf("%f", &peso);

    printf("Informe a altura (m): ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);

    printf("IMC: %.2f\n",imc);
    return 0;
}
