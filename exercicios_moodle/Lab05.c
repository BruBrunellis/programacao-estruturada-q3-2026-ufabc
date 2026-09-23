/*
Exercicio de Compilacao e Correcao de Codigo
O programa deve sortear 20x, dois operandos
inteiros no intervalo [-10,10] e um operador
aritimetico: `+`, `-`, `*`, `/` e `%`
Imprimir a saida ex: -10 + 9 = -1 */

#include <stdio.h>
#include <stdlib.h>

int main() {

        int op1, op2, seed, operador;

    	scanf("%d", &seed);
        srand(seed);

        for (int i = 1; i <= 20; i++){
            op1 = (rand()% (20 + 1)) - 10;
            op2 = (rand()% (20 + 1)) - 10;
            operador = rand()% 5 + 1;

            while((operador == 4 || operador == 5) && op2 == 0)
                { op2 = (rand()% (20 + 1)) - 10; }

            switch (operador){
                case 1:
                    printf("%d) %3d + %3d = %d\n", i, op1, op2, op1+op2);
                    break;
                case 2:
                    printf("%d) %3d - %3d = %d\n", i, op1, op2, op1-op2);
                    break;
                case 3:
                    printf("%d) %3d * %3d = %d\n", i, op1, op2, op1*op2);
                    break;
                case 4:
                    printf("%d) %3d / %3d = %.2f\n", i, op1, op2, (float)op1/op2);
                    break;
                case 5:
                    printf("%d) %3d %% %3d = %d\n", i, op1, op2, op1%op2);
                    break;
            }
          }
        return 0;
        }
