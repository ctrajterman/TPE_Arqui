#include <stdio.h>
#include <stdint.h>
#include <sys_calls.h>

extern uint64_t syscall_write();
extern uint64_t syscall_time();
extern uint64_t syscall_drawPixel();
extern uint64_t syscall_drawSquare();
extern uint64_t syscall_getWidth_vd();
extern uint64_t syscall_getHeight_vd();
extern uint64_t syscall_sleep();

void print(const char* buf, uint64_t count) {
	syscall_write(1, buf, count);
}

uint64_t itoa(uint64_t number, char* s) {
    int digits = 0;

    // Contar los dígitos
    for (uint64_t n = number; n != 0; digits++, n /= 10);

    // Manejo del caso donde number es 0
    if (digits == 0) {
        s[0] = '0';
        s[1] = '\0';
        return 1;
    }

    // Terminar la cadena con un carácter nulo
    s[digits] = '\0';

    // Convertir los dígitos en orden inverso
    for (int i = digits - 1; i >= 0; i--) {
        s[i] = (number % 10) + '0';
        number /= 10;
    }

    return digits;
}

void getTime(char* buffer) {
    uint64_t time = syscall_time();
    
    // Convertir horas
    int digits = itoa((time & 0xFF), buffer);
    buffer[digits] = ':'; // Separador de horas
    buffer += (digits + 1);

    // Convertir minutos
    digits = itoa((time >> 8) & 0xFF, buffer);
    buffer[digits] = ':'; // Separador de minutos
    buffer += (digits + 1);

    // Convertir segundos
    itoa((time >> 16) & 0xFF, buffer);
}

void printTime() {
    char buffer[10]; // El buffer debe ser lo suficientemente grande
    getTime(buffer);
    print(buffer, 9);
}

char getCharUser(){
	char c;
	syscall_read(0,&c);
	return c;
}

uint64_t getWidth_vd(){
    int width = syscall_getWidth_vd();
    return width;
}

uint64_t getHeight_vd(){
    int height = syscall_getHeight_vd();
    return height;
}

void drawPixel(uint32_t color, uint64_t x, uint64_t y){
    syscall_drawPixel(color, x, y);
}

void drawSquare(uint32_t color, uint64_t x, uint64_t y, uint64_t thickness){
    syscall_drawSquare(color, x, y, thickness);
}

void nano_sleep(uint64_t secs){
    syscall_sleep(secs);
}