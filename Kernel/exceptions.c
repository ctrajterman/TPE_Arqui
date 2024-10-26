
#define ZERO_EXCEPTION_ID 0
#define OP_CODE_INVALID_EXCEPTION 6

#include <videoDriver.h>
#include <stdint.h>
#include <interrupts.h>
#include <keyboard.h> 

//naiveConsole se usa solo para la transformacion de hexa a ascii de los valores de los regs

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char * regstxt[17]={"RAX:", "RBX:", "RCX:", "RDX:", "RSI:", "RDI:", "RBP:", "RSP:", "R8:", "R9:", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:", "RIP:", "RFLAGS:" };
static uint32_t white=0xFFFFFF;//chequear si esto esta ok
static uint32_t red=0xFF0000;

void exceptionDispatcher(int exception, uint64_t regs[17]) {
	if (exception == ZERO_EXCEPTION_ID)
		drawWord(red, "Cannot Divide by Zero, Register values:");
		newLine_vd();
	if(exception==OP_CODE_INVALID_EXCEPTION)
		drawWord(red, "Invalid Opcode Exception, Register values:");
		newLine_vd();
	char buffer[6];
	for(int i=0; i<17; i++){
		drawWord(white, regstxt[i]);
		uintToBase(regs[i], buffer, 16);
		buffer[2]=0;
		drawWord(white, buffer);
		newLine_vd();
		}

		drawWord(white, "Press key d to continue");
		newLine_vd();


		char buff;
		picMasterMask(0xFD);
		_sti();
		while(buff!='d'){
			buff=getCharPressed();
		}
		_cli();
		picMasterMask(0xFC);	

	//reiniciar pantalla

}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

