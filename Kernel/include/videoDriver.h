#ifndef LIB_H
#define LIB_H
#include <stdint.h>
#include <font.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(uint32_t hexColor, char c, uint64_t x, uint64_t y);
void drawWord(uint32_t hexColor, char* word);
void putSquarePixel (uint32_t hexColor, uint64_t x, uint64_t y, uint64_t thickness);
uint16_t getWidth_vd();
uint16_t getHeight_vd();

#endif