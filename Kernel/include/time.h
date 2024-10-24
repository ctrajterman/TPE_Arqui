#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>



void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
uint64_t getCurrentTimeBinary();
uint8_t getSeconds(); 
void sleep(uint64_t secs);

#endif