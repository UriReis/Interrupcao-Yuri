#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h"


#define WS2812_PIN 7
#define tempo 200




// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 200; // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 0;   // Intensidade do azul

bool led_on = false;

const uint botao_pinA = 5;
const uint botao_pinB = 6;
int iterador = 0;
static volatile uint a = 1;

bool repeating_timer_callback(struct repeating_timer *t)
{

    led_on = !led_on;
    gpio_put(13, led_on);

    return true;
}
// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    static volatile uint32_t last_timeA = 0; // Armazena o tempo do último evento (em microssegundos)
    static volatile uint32_t last_timeB = 0; // Armazena o tempo do último evento (em microssegundos)



    // Verifica se passou tempo suficiente desde o último evento

    if (gpio == botao_pinA)
    {
        if (current_time - last_timeA > 200000)
        { // Debouncing de 200ms
            last_timeA = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            if (iterador != 9)
            {
                iterador = iterador + 1;
                

                set_one_led(led_r, led_g, led_b, iterador);
            }
            else
            {
                printf("Ai não meu patrão");
            }
        }
    }
    else if (gpio == botao_pinB)
    {
        if (current_time - last_timeB > 200000)
        {
            last_timeB = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            // Debouncing de 200ms
            if (iterador != 0)
            {
                iterador = iterador - 1;
                set_one_led(led_r, led_g, led_b, iterador);
            }
            else{
                printf("Ai não meu nobre");
            }
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

    set_one_led(led_r, led_g, led_b, iterador);

    gpio_set_irq_enabled_with_callback(botao_pinA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_pinB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    

    while (true)
    {

        
    }

    return 0;
}


