#include <stdint.h>
#include <naiveConsole.h>
#include <time.h>
#include <videoDriver.h>
#include "speaker.h"
#include <syscallDispatcher.h>

#define STDIN  0
#define STDOUT 1
#define BLACK 0x000000


static uint64_t syscall_write_handler(int fd, char *buffer, uint64_t length);
static uint64_t syscall_read_handler(int fd, char *buffer);
static uint64_t syscall_time_handler();
static void syscall_drawPixel_handler(uint32_t color, uint64_t x, uint64_t y); 
static void syscall_drawSquare_handler(uint32_t color, uint64_t x, uint64_t y, uint64_t thickness);
static uint64_t syscall_getWidth_vd_handler();
static uint64_t syscall_getHeight_vd_handler();
static void syscall_sleep_handler(uint64_t secs);
static void syscall_paintAll_vd_handler(uint32_t hexColor);
static void syscall_erraseChar_handler(uint32_t hexColor);
static void syscall_increaseFS_handler();
static void syscall_decreaseFS_handler();
static void syscall_erraseLine_handler();
static void syscall_beep_handler( );

// Array de punteros a funciones que reciben los mismos argumentos
void (*syscalls_arr[])(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8) = {syscall_read_handler, syscall_write_handler, syscall_time_handler,
 syscall_drawPixel_handler, syscall_drawSquare_handler, syscall_getWidth_vd_handler, syscall_getHeight_vd_handler, syscall_sleep_handler, syscall_paintAll_vd_handler,
 syscall_erraseChar_handler, syscall_increaseFS_handler, syscall_decreaseFS_handler, syscall_erraseLine_handler, syscall_beep_handler};

void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax) {
    
    if (rax < (sizeof(syscalls_arr) / sizeof(syscalls_arr[0])) && syscalls_arr[rax]!=0) {
        syscalls_arr[rax](rdi, rsi, rdx, r10, r8);
    }
    return;
}

static uint64_t syscall_write_handler(int fd, char *buffer, uint64_t length) {

    drawWord(0xffffff, buffer);
}

static uint64_t syscall_read_handler(int fd, char *buffer){

    if (fd != 0){
        return -1;
    }

    *buffer = getCharPressed();
    return 0;
}

static uint64_t syscall_time_handler(){
    return getCurrentTimeBinary();
}

static void syscall_drawPixel_handler(uint32_t color, uint64_t x, uint64_t y){
    putPixel(color, x, y);
}

static void syscall_drawSquare_handler(uint32_t color, uint64_t x, uint64_t y, uint64_t thickness){
    putSquarePixel(color, x, y, thickness);
}

static uint64_t syscall_getWidth_vd_handler(){
    return getWidth_vd();
}

static uint64_t syscall_getHeight_vd_handler(){
    return getHeight_vd();
}

static void syscall_sleep_handler(uint64_t secs){
    sleep(secs);
}

static void syscall_paintAll_vd_handler(uint32_t hexColor){
    paintAll_vd(hexColor);
}

static void syscall_erraseChar_handler(uint32_t hexColor){
    erraseChar(hexColor);
}

static void syscall_increaseFS_handler(){
    increasePixelSize();
   // paintAll_vd(0x000000);
    
}

static void syscall_decreaseFS_handler(){
    decreasePixelSize();
    //paintAll_vd(0x000000);
}

static void syscall_erraseLine_handler(){
    erraseLine();
    paintAll_vd(0x000000);
}
static void syscall_beep_handler(){
    beep(1);
}