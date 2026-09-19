/*Laços executam um bloco várias vezes para obter o resultado esperado.
Comando for:
Início: uma ou mais atribuições, separador ','
Condição: os comandos são executados enquanto a condição for verdadeira
Passo: um ou mais comandos separador por ','. Os comandos do passo sempre são executados após os comandos do bloco.

for ( inicio ; condicao ; passo)
{
//comandos
}

*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Lançamentos e frequencia das faces ímpares

    int face, jogada, face1 = 0, face3 = 0, face5 = 0;

    for(jogada = 1; jogada <= 6000; jogada++)
    {
        face = 1 + rand() % 6;

        switch(face)
        {
            case 1:
                ++face1;
                break;
            case 3:
                ++face3;
                break;
            case 5:
                ++face5;
                break;
        }
    }

    printf("Face 1: %d\n", face1);
    printf("Face 3: %d\n", face3);
    printf("Face 5: %d\n", face5);
    return 0;
}


