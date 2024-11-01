GLOBAL div0
global opcode_exc

section .text

div0:
push rbp
mov rbp, rsp

mov rdx, 2
mov rax, 0
div rax

mov rsp, rbp
pop rbp
ret 


opcode_exc:
push rbp
mov rbp, rsp

jmp 0

mov rsp, rbp
pop rbp
ret