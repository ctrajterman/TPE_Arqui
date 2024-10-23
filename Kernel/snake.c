#include "snake.h"
#include <stdint.h>
#include <time.h>
#include <videoDriver.h>



//Hay que definir el tmamano de las cosas igual (supongo 4 bytes ) 
//Colors de https://htmlcolorcodes.com/
#define BACKGROUND_COLOR 0xB7E5E9 //celeste claro 
#define PRIZE_COLOR 0xA43A53 //bordo
#define TALLO 0X5A3535
#define SNAKE1_COLOR 0x5434B3 //violeta
#define SNAKE2_COLOR 0x89CB95//verde
#define THICKNESS 7

//heathersSN1
uint64_t snake1_x = 300 ;
uint64_t snake1_y=299;
uint64_t snake1_length= 89;
int snake1_direction1= 1;  //FALSE= moviemto en Y(|), TRUE= movimento en x(----)
int snake1_direction2 = 1 ;// FALSE=decrementa (upwards/izquierda)  , TRUE = incrementa  ( downwards/ derecha)


//heathersSN2
uint64_t snake2_x=0;
uint64_t snake2_y=0;
uint64_t snake2_length=0;
int snake2_direction1=0; //FALSE= moviemto en Y(|), TRUE= movimento en x(----)
int snake2_direction2 = 0;// FALSE=decrementa (upwards/izquierda)  , TRUE = incrementa  ( downwards/ derecha)


//IDEA: En cada movimiento hacer un repaint 
void paint_snake( uint64_t snake_x , uint64_t snake_y,uint64_t snake_length,int snake_direction1, int snake_direction2, uint32_t color){
    uint64_t increment = (snake_direction2) ? (1): (-1);

    if (snake_direction2){//Moviento en X
        for (uint64_t i=0 ;i< snake_length; i++){
             putSquarePixel ( color,  snake1_x + (i*increment),  snake_y , THICKNESS);
            
        }
    }
    else {//Moviemiento el Y
        for (uint64_t i=0 ;i< snake1_length; i++){
            putSquarePixel ( color,  snake1_x,  snake_y + (i*increment), THICKNESS);
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
                putPixel(TALLO, start_x +j, start_y - i);
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
                putPixel(PRIZE_COLOR, start_x + j, start_y + i);
            }
        }
    }
     
}



void re_paintBackground( ){//se tiene que llamar ANTES de pintar la snake para "Borrar " lo que habia 
    for(uint64_t x=0;x<1070 ;x++){
        for (uint64_t y=0;y<1000;y++)
            putPixel(BACKGROUND_COLOR, x, y); //pinta el fondo 

    }
}