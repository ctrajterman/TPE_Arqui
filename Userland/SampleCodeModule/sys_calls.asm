GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_time

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