#ifndef SNAKE_H
#define SNAKE_H

#include <stdint.h>
#include <stdbool.h>

// Declaración de variables globales para la serpiente 1
extern uint64_t snake1_x;
extern uint64_t snake1_y;
extern uint64_t snake1_length;
extern int snake1_direction1;  // FALSE = movimiento en Y (|), TRUE = movimiento en X (----)
extern int snake1_direction2;  // FALSE = decrementa (upwards/izquierda), TRUE = incrementa (downwards/derecha)

// Declaración de variables globales para la serpiente 2
extern uint64_t snake2_x;
extern uint64_t snake2_y;
extern uint64_t snake2_length;
extern int snake2_direction1;  // FALSE = movimiento en Y (|), TRUE = movimiento en X (----)
extern int snake2_direction2;  // FALSE = decrementa (upwards/izquierda), TRUE = incrementa (downwards/derecha)

// Prototipos de funciones
void paint_snake();
void re_paintBackground();
void draw_apple(uint64_t start_x, uint64_t start_y);

#endif // SNAKE_H
