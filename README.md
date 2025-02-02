# Interrupcao-Yuri
Projeto: Interrupções

Descrição

Este projeto implementa o controle de uma matriz de LEDs WS2812 utilizando a Raspberry Pi Pico. Através de botões físicos, é possível alterar os padrões de iluminação dos LEDs, formando números de 0 a 9.

Funcionalidades

Controle de uma matriz 5x5 de LEDs WS2812.

Alteração dos padrões de iluminação para exibir números de 0 a 9.

Utilização de botões físicos para incrementar ou decrementar os números exibidos.

Implementação de debounce para os botões.

Uso do PIO (Programmable I/O) da Raspberry Pi Pico para comunicação eficiente com os LEDs.

Timer para alternar o estado de um LED indicador a cada 100 ms.

Estrutura do Código

O projeto é dividido em dois arquivos principais:

1. main.c

Este arquivo contém o código principal que inicializa o sistema, configura os botões e LEDs, e gerencia as interrupções e o temporizador.

Principais componentes:

Definição de pinos: Configuração dos pinos GPIO para os botões e LEDs.

Timer de repetição: Alterna o estado do LED indicador em intervalos de 100 ms.

Manipulação de interrupções: Implementa debounce e responde à entrada dos botões.

Chamada da função set_one_led para atualizar a matriz de LEDs conforme a entrada dos botões.

2. bibliopio.c

Este arquivo contém a implementação das funções auxiliares para manipulação dos LEDs WS2812 utilizando o PIO da Raspberry Pi Pico.

Principais componentes:

Matriz de números (0-9): Define quais LEDs devem ser acesos para formar cada número.

Função set_one_led: Atualiza a matriz de LEDs conforme o número desejado.

Função put_pixel: Envia comandos de cor para os LEDs.

Função pio: Inicializa a comunicação PIO para controle dos LEDs WS2812.