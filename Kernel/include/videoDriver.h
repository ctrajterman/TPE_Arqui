#include <stdint.h>
#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) ;
void putCharacter(uint32_t hexColor, char c, uint64_t x, uint64_t y);
void drawWords(uint32_t hexColor, char* str, uint64_t x, uint64_t y);
void draw_word(uint32_t hexcolor, char* str);
void draw_enter();
void putSquarePixel (uint32_t hexColor, uint64_t x, uint64_t y, uint64_t thickness);
#endif
