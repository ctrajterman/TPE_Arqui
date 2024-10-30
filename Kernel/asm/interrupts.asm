
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt


GLOBAL _int80Handler

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler


GLOBAL _exception0Handler
GLOBAL _intPureba

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)						//le indica al PIC que la interrupción fue manejada y puede continuar.
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	cli
	pushState
	exception_regs_data
	mov rdi, %1 ; pasaje de parametro -> n excepcion
	mov rsi, exception_regs ; para imprimir regs
	call exceptionDispatcher
	popState
	iretq
%endmacro

%macro exception_regs_data 0
mov[exception_regs], rax
	mov [exception_regs+8], rbx
	mov [exception_regs+8*2], rcx
	mov [exception_regs+8*3], rdx
	mov [exception_regs+8*4], rdi
	mov [exception_regs+8*5], rsi
	mov [exception_regs+8*6], rbp

	mov rax, [rsp+18*8]

	mov [exception_regs+8*7], rax 
	mov [exception_regs+8*8], r8
	mov [exception_regs+8*9], r9
	mov [exception_regs+8*10], r10
	mov [exception_regs+8*11], r11
	mov [exception_regs+8*12], r12
	mov [exception_regs+8*13], r13
	mov [exception_regs+8*14], r14
	mov [exception_regs+8*15], r15
	mov rax, [rsp+15*8]
	mov [exception_regs+8*16], rax ;RID
	mov rax, [rsp+17*8]
	mov [exception_regs+8*17], rax ;FLAGS

%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;Cada irqHandler llama a irqHandlerMaster pasandole su parametro asociado, 
;el irqHandlerMaster llama a irqDispatcher que se encarga de llamar al handler asociado a cada interrupcion


;Syscall
_int80Handler:

	mov rcx, r10
	mov r9, rax
	call syscallDispatcher
	iretq


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_intPureba:


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

_exception06Handler:
	exceptionHandler 06

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1

SECTION .data
exception_regs dq 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0