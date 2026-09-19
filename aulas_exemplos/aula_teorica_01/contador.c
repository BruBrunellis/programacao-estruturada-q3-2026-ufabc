#include <stdio.h>
#include <windows.h>
#define MAX 100 //constante inteira

int contador = MAX; //variavel global

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    contador = contador - 1;  //Modificando a variavel global
    int minimo = -MAX;

    printf("Contador = %d\nMínimo = %d\nMáximo = %d\n",
        contador,
        minimo,
        MAX
    );
    return 0;
}
