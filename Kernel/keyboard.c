#include <keyboard.h>
#include <naiveConsole.h> 

extern int keyPressed();

void keyboard_handler() {
    // Obtener el scancode
    int scancode = keyPressed();

    // Mapa de scancodes a caracteres
    char scanCodes[128] = {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
        'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    // Verificar si el scancode es válido y si corresponde a una tecla imprimible
    if (scancode < 0 || scancode >= 128) {
        return;
    }

    char key = scanCodes[scancode];
    if (key != 0) {
        // Imprimir la tecla
        char toPrint[2] = {key, 0};  // Crear una cadena con la tecla
        ncPrint(toPrint);            // Imprimir la tecla
    }
}