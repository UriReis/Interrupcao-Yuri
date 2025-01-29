#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "bibliopio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 400
// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0; // Intensidade do vermelho
uint8_t led_g = 0; // Intensidade do verde
uint8_t led_b = 200; // Intensidade do azul





int main()
{
    pio();

    

    while (1)
    {
        set_one_led(led_r, led_g, led_b);
        sleep_ms(tempo);
        set_one_led(0, 0, 0);
        sleep_ms(tempo);
    }

    return 0;
}
