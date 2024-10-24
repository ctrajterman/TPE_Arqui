GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_time
GLOBAL syscall_getWidth_vd
GLOBAL syscall_getHeight_vd
GLOBAL syscall_drawPixel
GLOBAL syscall_drawSquare

section .text

syscall_read:
    mov rax, 0x00
    int 80h
    ret

syscall_write:
    mov rax, 0x01
    int 80h
    ret

syscall_time:
    mov rax, 0x02
    int 80h
    ret

syscall_drawPixel:
    mov rax, 0x03
    int 80h
    ret

syscall_drawSquare:
    mov rax, 0x04
    mov r10, rcx        ;4to parametro de syscall es R10
    int 80h
    ret

syscall_getWidth_vd:
    mov rax, 0x05
    int 80h
    ret

syscall_getHeight_vd:
    mov rax, 0x06
    int 80h
    ret

syscall_sleep:
mov rax, 0x07
int 80h
ret 
