#include <time.h>
#include <stdint.h>
#include <keyBoard.h>

static void int_20();
static void int_21();

void irqDispatcher(uint64_t irq) {
	void (*interrupt_arr[])(void) = {int_20,int_21};//chequear si no va & antes de las funciones
	//no c si es necesario el if este chequear
	if(irq>0 && irq <=1){
		interrupt_arr[irq]();
	}
	return;
}

void int_20() {
	timer_handler();
}
void int_21(){
	keyBoard_handler();
}
