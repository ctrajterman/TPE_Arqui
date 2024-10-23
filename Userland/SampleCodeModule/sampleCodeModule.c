/* sampleCodeModule.c */

#include <stdio.h>
#include <stdint.h>

char *string1 =  (char*)0xB8000 + 45 * 2;

extern uint64_t syscall_write();
extern uint64_t syscall_time();

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


int main() {

	// //Test if BSS is properly set up
	// if (var1 == 0 && var2 == 0)
	// 	return 0xDEADC0DE;

	// return 0xDEADBEEF;

	// for (int i = 0; toPrint[i] != 0; i++)
	// {
	// 	*(string1+(i*2)) = toPrint[i];
	// 	*(string1+(i*2)+1) = 0x74;
	// }
	// return 1;

	print("funcionaaa", 10);

	printTime();

	return 1;
}