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

extern bool led_buffer[10][25];

// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 200; // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 0;   // Intensidade do azul

bool led_on = false;

const uint botao_pinA = 5;
const uint botao_pinB = 6;

bool repeating_timer_callback(struct repeating_timer *t)
{

    led_on = !led_on;
    gpio_put(13, led_on);

    return true;
}

void display_number(int iterador)
{

    // Itera sobre cada LED na matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[iterador][i] == 1)
        {
            set_one_led(led_r, led_g, led_b, iterador); // Liga o LED com a cor definida
        }
        else
        {
            set_one_led(0, 0, 0, iterador); // Desliga o LED
        }
    }
}

void desplay_number(int iterador)
{

    // Itera sobre cada LED na matriz
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (led_buffer[iterador][i] == 1)
        {
            set_one_led(led_r, led_g, led_b, iterador); // Liga o LED com a cor definida
        }
        else
        {
            set_one_led(0, 0, 0, iterador); // Desliga o LED
        }
    }
}

int main()
{
    stdio_init_all();

    pio();

    gpio_init(13);
    gpio_set_dir(13, GPIO_OUT);

    struct repeating_timer timer;

    add_repeating_timer_ms(tempo / 2, repeating_timer_callback, NULL, &timer);

    gpio_init(botao_pinA);
    gpio_set_dir(botao_pinA, GPIO_IN);
    gpio_pull_up(botao_pinA);

    gpio_init(botao_pinB);
    gpio_set_dir(botao_pinB, GPIO_IN);
    gpio_pull_up(botao_pinB);

    bool ultimo_estado_botao = true;
    int iterador = 0;

    while (true)
    {
        
        set_one_led( led_r, led_g, led_b, iterador);
        
        

        bool estado_atual_botaoA = gpio_get(botao_pinA);
        bool estado_atual_botaoB = gpio_get(botao_pinB);

        if (estado_atual_botaoA == false && ultimo_estado_botao == true){

            
            

            if (iterador != 9)
            {
                iterador = iterador + 1;
                //display_number(iterador);
                set_one_led( led_r, led_g, led_b, iterador);
            }
            else
            {
                printf("Ai não meu patrão");
            }
        }
        if (estado_atual_botaoB == false && ultimo_estado_botao == true)
        {
            
            if (iterador != 0)
            {
                iterador = iterador - 1;
                set_one_led( led_r, led_g, led_b, iterador);
            }
        }
        

        ultimo_estado_botao = estado_atual_botaoA;
        ultimo_estado_botao = estado_atual_botaoB;
        sleep_ms(1000);

    }
    
    return 0;
}
