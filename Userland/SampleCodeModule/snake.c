#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "stdlib_user.h"


// Definiciones de constantes
#define WIDHT 768
#define HEIGHT 1024
#define DIM_BOARD 760               // Tamano del board
#define DIM_HEADER 80
#define BACKGROUND_COLOR 0x87CEEB   // Color de fondo
#define THICKNESS 40                // Grosor de la serpiente
#define MAX_SNAKE_LENGTH 100        // Longitud máxima de la serpiente
#define PRIZE_COLOR 0xA43A53        // Bordo
#define BLACK_COLOR 0x000000        // Negro
#define APPLE_SIZE 40               // Tamano manzana

//WIDTH ES 768
//HEIGHT ES 1024

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
    int score ; 
    int hasEatenApple;
}typedef Snake ;


struct Apple{
    int x;
    int y;
}typedef Apple;


uint32_t x = 123456789; // Semilla inicial



uint32_t randNum() {
    x = x * 1664525 + 1013904223;
    return x;
}

void drawLines(){
    for (int i = DIM_HEADER; i <= DIM_BOARD; i++){
        for (int j = DIM_HEADER; j <= DIM_BOARD; j+=40)
        {
            drawPixel(BLACK_COLOR, i, j);
            drawPixel(BLACK_COLOR, j, i);
        }
    }
}

void drawBackground(){
    for (int i = DIM_HEADER; i <= DIM_BOARD; i++){
        for (int j = DIM_HEADER; j <= DIM_BOARD; j++)
        {
            drawPixel(BACKGROUND_COLOR, i, j);
        }
    }
}

// Genera un número aleatorio entre 1 y 1000
// uint32_t randPositionx() {
//     return (randNum() % getWidth_vd()) + 1;
// }
// uint32_t randPositiony() {
//     int aux = (randNum() % getHeight_vd()) + 1;
//     if (aux<=MAX_HEIGHT)
//     {
//         return (aux+MAX_HEIGHT);
//     }
//     return aux;
// }

//Genera un número aleatorio entre 1 y 1000
uint32_t randPositionx() {
    int aux1 = (randNum() % DIM_BOARD) + 1;
    if (aux1<DIM_HEADER)
    {
        return ((aux1+DIM_HEADER)/40)*40;
    }
    return (aux1/40)*40;
}
uint32_t randPositiony() {
    int aux2 = (randNum() % DIM_BOARD) + 1;
    if (aux2<DIM_HEADER)
    {
        return ((aux2+DIM_HEADER)/40)*40;
    }
    return (aux2/40)*40;
}


// Función para inicializar la serpiente
void initializeSnake(struct Snake *snake, uint64_t hexcolor) {
    snake->length = 5; // Comienza con 5 segmentos
    //snake->x[0] = getWidth_vd() / 2; // Posición inicial en X
    //nake->y[0] = getHeight_vd() / 2; // Posición inicial en Y

    snake->x[0] = 320;
    snake->y[0] = 320;

    for (int i = 1; i < snake->length; i++) {
        snake->x[i] = snake->x[i - 1] - THICKNESS;  // Segmentos iniciales hacia la izquierda
        snake->y[i] = snake->y[0];                  // Mantener la misma Y
    }

    snake->directionX = 1; // Movimiento inicial en X (derecha)
    snake->directionY = 0; // No hay movimiento inicial en Y
    snake->isDead = false;
    snake->color = hexcolor; // Color de la serpiente
    snake->tailX;
    snake->tailY;
    snake->score = 0;
    snake->hasEatenApple=0;
}

// Dibuja la serpiente
void drawSnake(struct Snake *snake) {
    for (int i = 0; i < snake->length; i++) {
        drawSquare(snake->color, snake->x[i], snake->y[i], THICKNESS);
    }
}


void find_apple(Apple *apple , Snake *snake ){
    
    // Verificar si la cabeza de la serpiente está dentro del área de la manzana
    if (snake->x[0] < apple->x + APPLE_SIZE && snake->x[0] + THICKNESS > apple->x &&
        snake->y[0] < apple->y + APPLE_SIZE && snake->y[0] + THICKNESS > apple->y) {
        

        makeBeep();
        draw_apple(BACKGROUND_COLOR, apple->x, apple->y);   //borro la apple
        
        snake->length++;
        
        snake->score++;

        snake->x[snake->length - 1] = snake->x[snake->length - 2];
        snake->y[snake->length - 1] = snake->y[snake->length - 2];

        snake->hasEatenApple=1;

        apple->x = randPositionx();
        apple->y = randPositiony();

        while (1) {
            int overlaps = 0;
            for (int i = 0; i < snake->length; i++) {
                if (snake->x[i] < apple->x + APPLE_SIZE && snake->x[i] + THICKNESS > apple->x &&
                    snake->y[i] < apple->y + APPLE_SIZE && snake->y[i] + THICKNESS > apple->y) 
                {
                    overlaps = 1; // La nueva manzana se superpone con la serpiente
                    break;
                }
            }
            if (!overlaps){
                break;
            } 
            // Si no hay superposición, sal del bucle
            // Si hay superposición, genera una nueva posición
            apple->x = randPositionx();
            apple->y = randPositiony();
        }

        char buffer[2];

        itoa(snake->score, buffer);
        if(snake->length > 15){
            erraseChar(BLACK_COLOR);
        }
        erraseChar(BLACK_COLOR);
        print(buffer, 2);

        draw_apple(PRIZE_COLOR, apple->x, apple->y);        //dibujo la apple
    }
}

int find_apple2(Apple *apple , Snake *snake ){

    // Verificar si la cabeza de la serpiente está dentro del área de la manzana
    if (snake->x[0] < apple->x + APPLE_SIZE && snake->x[0] + THICKNESS > apple->x &&
        snake->y[0] < apple->y + APPLE_SIZE && snake->y[0] + THICKNESS > apple->y) {

        draw_apple(BACKGROUND_COLOR, apple->x, apple->y);   //borro la apple

        snake->length++;

        snake->score++;

        snake->x[snake->length - 1] = snake->x[snake->length - 2];
        snake->y[snake->length - 1] = snake->y[snake->length - 2];

        snake->hasEatenApple=1;

        apple->x = randPositionx();
        apple->y = randPositiony();

        while (1) {
            int overlaps = 0;
            for (int i = 0; i < snake->length; i++) {
                if (snake->x[i] < apple->x + APPLE_SIZE && snake->x[i] + THICKNESS > apple->x &&
                    snake->y[i] < apple->y + APPLE_SIZE && snake->y[i] + THICKNESS > apple->y) 
                {
                    overlaps = 1; // La nueva manzana se superpone con la serpiente
                    break;
                }
            }
            if (!overlaps){
                break;
            } 
            // Si no hay superposición, sal del bucle
            // Si hay superposición, genera una nueva posición
            apple->x = randPositionx();
            apple->y = randPositiony();
        }

        // char buffer[2];

        // itoa(snake->score, buffer);
        // erraseChar(BLACK_COLOR);
        // print(buffer, 2);

        draw_apple(PRIZE_COLOR, apple->x, apple->y);        //dibujo la apple
    }
    return snake->hasEatenApple;
}


void draw_apple(uint64_t color , uint64_t start_x, uint64_t start_y) {
    
    drawSquare(color, start_x , start_y , APPLE_SIZE);
}

// Mueve la serpiente
void moveSnake(struct Snake *snake) {
    // Borrar la cola de la serpiente antes de moverla
    if (!snake->hasEatenApple) {  // hasEatenApple debe ser una bandera que activas al comer una manzana.
        int tailIndex = snake->length - 1;
        snake->tailX = snake->x[tailIndex]; // Guarda la posición actual de la cola para borrarla después
        snake->tailY = snake->y[tailIndex];
        drawSquare(BACKGROUND_COLOR, snake->tailX, snake->tailY, THICKNESS);
        drawLines();
    }
    
    snake->hasEatenApple=0;

    for (int i = snake->length-1; i > 0; i--) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }

    // Actualiza la posición de la cabeza
    snake->x[0] += snake->directionX * THICKNESS;
    snake->y[0] += snake->directionY * THICKNESS;

    // Restringir los límites de la serpiente
    //if (snake->x[0] < 0) snake->x[0] = 0;
    //if (snake->x[0] > getWidth_vd() - THICKNESS) snake->x[0] = getWidth_vd() - THICKNESS;
    //if (snake->y[0] < MAX_HEIGHT) snake->y[0] = MAX_HEIGHT;
    //if (snake->y[0] > getHeight_vd() - THICKNESS) snake->y[0] = getHeight_vd() - THICKNESS;

    // Marcar como muerta si se sale de los límites
    //if (snake->x[0] < 0 || snake->x[0] >= getWidth_vd() || 
        //snake->y[0] < MAX_HEIGHT || snake->y[0] >= getHeight_vd()) {
        //snake->isDead = true;
    //}

    // Restringir los límites de la serpiente
    if (snake->x[0] < DIM_HEADER) snake->x[0] = DIM_HEADER;
    if (snake->x[0] > DIM_BOARD - THICKNESS) snake->x[0] = DIM_BOARD - THICKNESS;
    if (snake->y[0] < DIM_HEADER) snake->y[0] = DIM_HEADER;
    if (snake->y[0] > DIM_BOARD - THICKNESS) snake->y[0] = DIM_BOARD - THICKNESS;

    // Marcar como muerta si se sale de los límites
    if (snake->x[0] < DIM_HEADER || snake->x[0] >= DIM_BOARD || 
        snake->y[0] < DIM_HEADER || snake->y[0] >= DIM_BOARD) {
        snake->isDead = true;
    }

    // Verifica colisión con ella misma
    for (int i = 1; i < snake->length; i++) {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i]) {
            snake->isDead = true; // La serpiente se ha muerto
            break;
        }
    }
}




void keyboard_managment_snake (char input, Snake *snake,char K1,char K2,char K3,char K4) {
    if (input==K1) {
        if (snake->directionY != 1) { // No permitir el giro en dirección opuesta
            snake->directionX = 0; // Se mantiene en horizontal
            snake->directionY = -1; // Cambiar a dirección vertical
        }
    }
    else if (input==K2) {
        if (snake->directionX != 1) {
            snake->directionX = -1; // Cambiar a dirección horizontal a la izquierda
            snake->directionY = 0; // Se mantiene en horizontal
        }
    }
    else if (input==K3){
        if (snake->directionY != -1) {
            snake->directionX = 0; // Se mantiene en horizontal
            snake->directionY = 1; // Cambiar a dirección vertical hacia abajo
        }
    }
    else if (input==K4){
        if (snake->directionX != -1) {
            snake->directionX = 1; // Cambiar a dirección horizontal a la derecha
            snake->directionY = 0; // Se mantiene en horizontal
        }
    }
}


void exit_snake(){
    
    char input;
    print("\n",2);
    increaseFontSize();
    print("press q to quit", 15);
    while(input!='q'){
        input = getCharUser();
    }
    decreaseFontSize();
    paintAll_vd(BACKGROUND_COLOR);
}

// Función principal del juego



void gameLoop1() {

    struct Snake snake1;


    struct Apple apple;

    apple.x=200;
    apple.y=200;
    
    initializeSnake(&snake1,0x5434B3);

    paintAll_vd(BLACK_COLOR);

    drawBackground();

    drawLines();

    draw_apple(PRIZE_COLOR, apple.x, apple.y);
           
    char *score= "SCORE : 0";

    print(score, 9);
    
    while (!snake1.isDead && snake1.length < 30) {

        nano_sleep(2);

        // Dibujar la serpiente
        drawSnake(&snake1);
        
        // Mover la serpiente
        moveSnake(&snake1);
        
        find_apple(&apple, &snake1);

        // Manejo de entrada
        char input = getCharUser();
        keyboard_managment_snake (input, &snake1, 'w','a','s','d');

    }
    exit_snake();
}










void gameLoop2() {
    struct Snake snake1;
    struct Snake snake2;

    struct Apple apple;

    int points1=0;
    int points2=0;
    apple.x=200;
    apple.y=200;
    
    initializeSnake(&snake1,0x5434B3);
    initializeSnake(&snake2,0x89AAB3);

    paintAll_vd(BLACK_COLOR);

    drawBackground();

    drawLines();

    draw_apple(PRIZE_COLOR, apple.x, apple.y);
           
    char *score1= "SCORE SNAKE1 : ";
    char *score2= "SCORE SNAKE2 : ";
    char buff1[2];
    char buff2[2];

    print(score1, 9);
    itoa(points1, buff1);
    erraseChar(BLACK_COLOR);
    print(buff1, 2);

    print("\n", 2);

    print(score2, 9);
    itoa(points2, buff2);
    erraseChar(BLACK_COLOR);
    print(buff2, 2);

    print("\n", 2);
    
    while (!snake1.isDead && snake1.length < 15 && !snake2.isDead && snake2.length < 15) {

        nano_sleep(2);

        // Dibujar las serpientes
        drawSnake(&snake1);
        drawSnake(&snake2);
        
        // Mover las serpientes
        moveSnake(&snake1);
        moveSnake(&snake2);
        
        // Ver si encuentran la manzana
        if(find_apple2(&apple, &snake1) == 1){
            points1++;

            erraseLine();
            erraseLine();

            print(score1, 9);
            itoa(points1, buff1);
            erraseChar(BLACK_COLOR);
            print(buff1, 2);

            print("\n", 2);

            print(score2, 9);
            itoa(points2, buff2);
            erraseChar(BLACK_COLOR);
            print(buff2, 2);

            print("\n", 2);
        }
        if(find_apple2(&apple, &snake2) == 1){
            points2++;

            erraseLine();
            erraseLine();

            print(score1, 9);
            itoa(points1, buff1);
            erraseChar(BLACK_COLOR);
            print(buff1, 2);

            print("\n", 2);

            print(score2, 9);
            itoa(points2, buff2);
            erraseChar(BLACK_COLOR);
            print(buff2, 2);

            print("\n", 2);
        }

        // Manejo de entrada
        char input = getCharUser();
        keyboard_managment_snake (input, &snake1, 'w','a','s','d');
        keyboard_managment_snake (input, &snake2, 'i','j','k','l');

    }
    exit_snake();
}




