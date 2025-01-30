#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h"

#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define tempo 200

// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 0;   // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 200; // Intensidade do azul

bool led_on = false;

bool repeating_timer_callback (struct repeating_timer *t){

    led_on= !led_on;
    gpio_put(13, led_on);

    return true;
}

int main()
{   
    stdio_init_all();

    pio();

    gpio_init(13);
    gpio_set_dir(13, GPIO_OUT);

    struct repeating_timer timer;

    add_repeating_timer_ms(tempo/2, repeating_timer_callback , NULL, &timer);

    while (1)
    {
       
        sleep_ms(10000);
        printf(" teste ");

        
    }

    return 0;
}
