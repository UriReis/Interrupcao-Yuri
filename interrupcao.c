#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "bibliopio.h" // chamada da biblioteca


#define WS2812_PIN 7
#define tempo 200




// Variável global para armazenar a cor (Entre 0 e 255 para intensidade)
uint8_t led_r = 200; // Intensidade do vermelho
uint8_t led_g = 0;   // Intensidade do verde
uint8_t led_b = 0;   // Intensidade do azul

bool led_on = false; //Inicilização do led desligado

const uint botao_pinA = 5; //Pino respectivo ao botão
const uint botao_pinB = 6; //Pino respectivo ao botão
int iterador = 0;
static volatile uint a = 1;

// Função de clock para uma repetição a cada 100 ms
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

    if (gpio == botao_pinA) // Verifica se o botão A foi apertado
    {
        if (current_time - last_timeA > 200000)
        { // Debouncing de 200ms
            last_timeA = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            if (iterador != 9) // Verifica se o iterador corresponde a um número menor que 9
            {
                iterador = iterador + 1; // Incrementa um número do iterador
                

                set_one_led(led_r, led_g, led_b, iterador); // Chama da função set_one_led presente na biblioteca biblio
            }
            else
            {
                printf("Ai não meu patrão\n");
            }
        }
    }
    else if (gpio == botao_pinB) // Verifica se o botão B foi apertado
    {
        if (current_time - last_timeB > 200000)
        {
            last_timeB = current_time;
            printf("A: %d\n", a); // Para controle quando se usa o monitor serial para verificar se há bouncing
            a++;
            // Debouncing de 200ms
            if (iterador != 0) // Verifica se o iterador corresponde a um número maior que 0
            {
                iterador = iterador - 1; // Decrementa um número do iterador 
                set_one_led(led_r, led_g, led_b, iterador); // Chama da função set_one_led presente na biblioteca biblio
            }
            else{
                printf("Ai não meu nobre\n");
            }
        }
    
    }
}

int main()
{
    stdio_init_all();

    pio(); // Inicialização da função pio presenta na biblioteca biblio

    gpio_init(13);
    gpio_set_dir(13, true);

    struct repeating_timer timer; // Struct declarada para o uso do Clock

    add_repeating_timer_ms(tempo / 2, repeating_timer_callback, NULL, &timer);

    //Inicializações:
    gpio_init(botao_pinA);
    gpio_set_dir(botao_pinA, GPIO_IN);
    gpio_pull_up(botao_pinA);

    gpio_init(botao_pinB);
    gpio_set_dir(botao_pinB, GPIO_IN);
    gpio_pull_up(botao_pinB);

    set_one_led(led_r, led_g, led_b, iterador); // Chamada da função set_one_led para o primeiro número ( 0 )

    // Chamada da interrupção para os dois botões:
    gpio_set_irq_enabled_with_callback(botao_pinA, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(botao_pinB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    

    while (true)
    {

        sleep_ms(1000);
    }

    return 0;
}