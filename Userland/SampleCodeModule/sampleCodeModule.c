/* sampleCodeModule.c */

#include <stdio.h>
#include <stdint.h>
#include <syscall.h>
#include <snake.h>
#include <stdlib_user.h>


int main() {

	// print("funcionaaa", 10);

	// printTime();
    
    // while (1)
    // {
    //     if(getCharUser()=='w'){
    //         print("god", 3);
    //         drawPixel(0xB7E5E9, 200, 200);
    //         drawSquare(0xB7E5E9, 200, 200, 74);
    //     }
    // }
    

    gameLoop();

	return 1;
}