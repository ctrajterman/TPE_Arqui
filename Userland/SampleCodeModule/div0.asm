GLOBAL div0

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
