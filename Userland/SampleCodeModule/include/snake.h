#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>
#include <stdbool.h>

// Definiciones de constantes
#define BACKGROUND_COLOR 0xB7E5E9  // Color de fondo
#define THICKNESS 7                 // Grosor de la serpiente
#define WIDTH 1000                  // Ancho de la pantalla
#define HEIGHT 1000                 // Alto de la pantalla
#define MAX_SNAKE_LENGTH 100        // Longitud máxima de la serpiente

// Estructura de la serpiente
struct Snake {
    int x[MAX_SNAKE_LENGTH];  // Posiciones en X de la serpiente
    int y[MAX_SNAKE_LENGTH];  // Posiciones en Y de la serpiente
    int length;               // Longitud de la serpiente
    int directionX;           // 1: derecha, -1: izquierda, 0: no se mueve
    int directionY;           // 1: abajo, -1: arriba, 0: no se mueve
    bool isDead;              // Estado de la serpiente (muerta o viva)
    uint32_t color;           // Color de la serpiente
};

// Declaraciones de funciones
void initializeSnake(struct Snake *snake);
void drawSnake(struct Snake *snake);
void moveSnake(struct Snake *snake);
void repaintBackground();
void gameLoop();

#endif // SNAKE_H