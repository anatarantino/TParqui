#include <prints.h>
#include <colors.h>
#include <vars.h>

#define ZERO_EXCEPTION 0
#define INVALID_OP	6
#define TOTALREGS 16 //hay 17 en el vector, chequear

static void zero_division();
static void invalid_op();
static void printRegisters(uint64_t * registers);

//puede cambiar el orden de como los recibimos
static char* dataRegisters[] = {"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ", 
						"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
                        "RAX: ", "RIP: ", "RSP: "};

void exceptionDispatcher(int exception, uint64_t * registers) {
	if (exception == ZERO_EXCEPTION){
		zero_division();
	}else if(exception == INVALID_OP){
		invalid_op();
	}
	printRegisters(registers);
	printNewLine();
	registers[TOTALREGS]=(uint64_t)sampleCodeModuleAddress;
	registers[TOTALREGS+3]=(uint64_t)sampleCodeModuleRSP;
}

static void zero_division() {
	printColor("\nZERO DIVISION ERROR: division by zero is undefined.\n",YELLOW,RED);
}

static void invalid_op(){
	printColor("\nINVALID OPERATION CODE EXCEPTION.\n",YELLOW,RED);
}

static void printRegisters(uint64_t * registers){
	for(int i=0 ; i < TOTALREGS ; i++){
		printColor(dataRegisters[i],VIOLET,BLACK);
		printHexColor(registers[i],VIOLET,BLACK); 
		printNewLine();
	}
	//imprimir rsp aparte??
	printColor(dataRegisters[TOTALREGS],VIOLET,BLACK);
	printHexColor(registers[15 + 3],WHITE,BLACK);
}