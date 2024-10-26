
#define ZERO_EXCEPTION_ID 0
#define OP_CODE_INVALID_EXCEPTION 6

#include <videoDriver.h>
#include <stdint.h>
#include <interrupts.h>
#include <syscallDispatcher.h>


static char * regstxt={"RAX:", "RBX:", "RCX:", "RDX:", "RSI:", "RDI:", "RBP:", "RSP:", "R8:", "R9:", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:", "RIP:", "RFLAGS:" };
static uint32_t white=0xFFFFFF;//chequear si esto esta ok
static uint32_t red=0xFF0000;

void exceptionDispatcher(int exception, uint64_t regs[17]) {
	if (exception == ZERO_EXCEPTION_ID)
		drawWord(red, "Cannot Divide by Zero, Register values:");
		newLine_vd();
	if(exception==OP_CODE_INVALID_EXCEPTION)
		drawWord(red, "Invalid Opcode Exception, Register values:");
		newLine_vd();

	for(int i=0; i<17; i++){
		drawWord(white, regstxt[i]);
		drawWord(white, regs[i]);
		newLine_vd();
		}

		drawWord(white, "Press key d to continue");
		newLine_vd();


		char buff;
		picMasterMask(0xFD);
		_sti();
		while(buff!='d'){
			syscall_read_handler(0, &buff);
		}
		_cli();
		picMasterMask(0xFC);	

	//reiniciar pantalla

}


