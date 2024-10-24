
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "stdlib_user.h"

// Definiciones de constantes
#define BACKGROUND_COLOR 0x000000   // Color de fondo
#define THICKNESS 10                // Grosor de la serpiente
#define WIDTH 1000                  // Ancho de la pantalla
#define HEIGHT 1000                 // Alto de la pantalla
#define MAX_SNAKE_LENGTH 100        // Longitud máxima de la serpiente
#define PRIZE_COLOR 0xA43A53 //bordo
#define TALLO 0X5A3535

// Estructura de la serpiente
struct Snake {
    int x[MAX_SNAKE_LENGTH];  // Posiciones en X de la serpiente
    int y[MAX_SNAKE_LENGTH];  // Posiciones en Y de la serpiente
    int length;               // Longitud de la serpiente
    int directionX;          // 1: derecha, -1: izquierda, 0: no se mueve
    int directionY;          // 1: abajo, -1: arriba, 0: no se mueve
    bool isDead;             // Estado de la serpiente (muerta o viva)
    uint32_t color;          // Color de la serpiente
    int tailX;
    int tailY;
};

// Función para inicializar la serpiente
void initializeSnake(struct Snake *snake) {
    snake->length = 5; // Comienza con 5 segmentos
    snake->x[0] = WIDTH / 2; // Posición inicial en X
    snake->y[0] = HEIGHT / 2; // Posición inicial en Y

    // for (int i = 1; i < snake->length; i++) {
    //     snake->x[i] = snake->x[i - 1] - THICKNESS;  // Segmentos iniciales hacia la izquierda
    //     snake->y[i] = snake->y[0];                  // Mantener la misma Y
    // }

    snake->directionX = 1; // Movimiento inicial en X (derecha)
    snake->directionY = 0; // No hay movimiento inicial en Y
    snake->isDead = false;
    snake->color = 0x5434B3; // Color de la serpiente
    snake->tailX = snake->x[snake->length - 1];
    snake->tailY = snake->y[snake->length - 1];
}

// Dibuja la serpiente
void drawSnake(struct Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        drawSquare(snake->color, snake->x[i], snake->y[i], THICKNESS);
    }
}

// Mueve la serpiente
void moveSnake(struct Snake *snake) {
    // Borrar la cola de la serpiente antes de moverla
    int tailIndex = snake->length - 1;
    drawSquare(BACKGROUND_COLOR, snake->x[tailIndex], snake->y[tailIndex], THICKNESS);

    // Mueve los segmentos de la serpiente, de la cola hacia la cabeza
    for (int i = tailIndex; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    // Actualiza la posición de la cabeza
    snake->x[0] += snake->directionX * THICKNESS;
    snake->y[0] += snake->directionY * THICKNESS;

    // Restringir los límites de la serpiente
    if (snake->x[0] < 0) snake->x[0] = 0;
    if (snake->x[0] > WIDTH - THICKNESS) snake->x[0] = WIDTH - THICKNESS;
    if (snake->y[0] < 0) snake->y[0] = 0;
    if (snake->y[0] > HEIGHT - THICKNESS) snake->y[0] = HEIGHT - THICKNESS;

    // Verifica colisión con ella misma
    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            snake->isDead = true; // La serpiente se ha muerto
            break;
        }
    }
}

void eraseTail(struct Snake *snake) {
    drawSquare(BACKGROUND_COLOR, snake->tailX, snake->tailY, THICKNESS);
}

// Repinta el fondo
void repaintBackground() {
    for (uint64_t x = 0; x < WIDTH; x++) {
        for (uint64_t y = 0; y < HEIGHT; y++) {
            drawPixel(BACKGROUND_COLOR, x, y);
        }
    }
}

void draw_apple(uint64_t start_x, uint64_t start_y) {
    int tallo [4][14]={
                {0,0,0,0,0,0,1,1,0,0,0,0,0,0},
                {0,0,0,0,0,1,1,0,0,0,0,0,0,0},
                {0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    };
        for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 14; j++) {
            if (tallo[i][j] == 1) {
                drawSquare(TALLO, start_x +j, start_y - i, 10);
            }
        }
    }
    int apple[12][14] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 14; j++) {
            if (apple[i][j] == 1) {
                drawSquare(PRIZE_COLOR, start_x + j, start_y + i, 10);
            }
        }
    }
     
}

// Función principal del juego
void gameLoop() {
    struct Snake snake;
    initializeSnake(&snake);

    draw_apple(300, 300);

    while (!snake.isDead) {
        //repaintBackground();

        // for (int i = 0; i < 10000; i++)
        // {
        //     for (int j = 0; j < 1000; j++)
        //     {
        //         i+j;
        //     }
            
        // }

        nano_sleep(1);
        
        eraseTail(&snake);

        // Mover la serpiente
        moveSnake(&snake);

        // Dibujar la serpiente
        drawSnake(&snake);

        // Manejo de entrada
        char input = getCharUser();
        switch (input) {
            case 'w': // Arriba
                if (snake.directionY != 1) { // No permitir el giro en dirección opuesta
                    snake.directionX = 0; // Se mantiene en horizontal
                    snake.directionY = -1; // Cambiar a dirección vertical
                }
                break;
            case 'a': // Izquierda
                if (snake.directionX != 1) {
                    snake.directionX = -1; // Cambiar a dirección horizontal a la izquierda
                    snake.directionY = 0; // Se mantiene en horizontal
                }
                break;
            case 's': // Abajo
                if (snake.directionY != -1) {
                    snake.directionX = 0; // Se mantiene en horizontal
                    snake.directionY = 1; // Cambiar a dirección vertical hacia abajo
                }
                break;
            case 'd': // Derecha
                if (snake.directionX != -1) {
                    snake.directionX = 1; // Cambiar a dirección horizontal a la derecha
                    snake.directionY = 0; // Se mantiene en horizontal
                }
                break;
        }
    }
}