
#define ZERO_EXCEPTION_ID 0
#define OP_CODE_INVALID_EXCEPTION 6

static void zero_division();
static void op_code_invalid();


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception==OP_CODE_INVALID_EXCEPTION)
		op_code_invalid();
}


static void zero_division() {
	// Handler para manejar excepcíon
}

static void op_code_invalid(){
	// Handler para manejar la excepcion 
}