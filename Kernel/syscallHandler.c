#include <stdint.h>
#include <keyBoard.h>
#include <naiveConsole.h>
#define STDOUT 1
#define STDERR 2
#define LENGTH 2
//lengtgh va a cambiar a medida q agreguemos syscalls
typedef struct {
uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} regs;
uint64_t (*sys_arr[])(regs*) = {sys_read,sys_write}; //chequear tema parametro por ahi para este caso si conviene switch

uint64_t syscallHandler(regs* regs){
    if(regs-> rax <0 || regs -> rax > LENGTH){
        return -1; //chequear q se devuelve si hay error
    } else{
        return sys_arr[regs-> rax]();
    }

}
//hacerlo desp de sesion dani
uint64_t sys_read(unsigned int fd, char * buffer, size_t count){
    int i=0;
    while(i<count){//como chequeo q no estoy pisando memoria si count> tamaño buffer? o es responsabilidad usuario?
        buffer[i++]=keyRead();
    }
    return i;
}

uint64_t sys_write(unsigned int fd, char * buffer, size_t count){
    int i=0;
    uint8_t fmt=0;
    if(fd==STDERR){
        fmt= 0x04; //chequear si es 0x40
    }
    while(buffer[i]!=0 && i<count){
        ncPrintCharFormat(buffer[i], fmt);
        i++;
    }
}