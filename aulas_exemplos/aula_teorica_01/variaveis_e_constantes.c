/* Exemplo 2 - Calcula a area do círculo*/
#include <stdio.h>
#include <windows.h>
#define Pi 3.14

int main(void)
{
    //Configuração para que o output no terminal exiba acentos de caracteres corretamente.
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int raio;

    printf("Informe a área: ");
    scanf("%d", &raio);

    float area;
    area = Pi * raio * raio;

    printf("A área do círculo de raio %d é: %.2f\n", raio, area);

    return 0;

}
