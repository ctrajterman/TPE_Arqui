#include <stdint.h>
#include <naiveConsole.h>
#include <time.h>
#include <videoDriver.h>

static uint64_t syscall_write_handler(int fd, char *buffer, uint64_t length);
static uint64_t syscall_read_handler(int fd, char *buffer, uint64_t length);
static uint64_t syscall_time_handler();

// Array de punteros a funciones que reciben los mismos argumentos
void (*syscalls_arr[])(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8) = {syscall_read_handler, syscall_write_handler, syscall_time_handler};

void syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t rax) {
    
    if (rax < (sizeof(syscalls_arr) / sizeof(syscalls_arr[0])) && syscalls_arr[rax]!=0) {
        syscalls_arr[rax](rdi, rsi, rdx, r10, r8);
    }
    return;
}

static uint64_t syscall_write_handler(int fd, char *buffer, uint64_t length) {

    draw_word(0x00FF0000, buffer);
    return 0;
}

static uint64_t syscall_read_handler(int fd, char *buffer, uint64_t length){
    return 0;
}

static uint64_t syscall_time_handler(){
    return getCurrentTimeBinary();
}