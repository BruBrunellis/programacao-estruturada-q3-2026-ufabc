//Conversor de celcius em fahrenheit

#include <stdio.h>

int main(void)
{
    float celcius = 0, fahrht = 0;

    scanf("%f", &celcius);

    fahrht = (celcius*(9/5.0)) + 32.0;

    printf("%.2f graus Celsius corresponde a %.2f graus Fahrenheit", celcius, fahrht);

    return 0;
}

