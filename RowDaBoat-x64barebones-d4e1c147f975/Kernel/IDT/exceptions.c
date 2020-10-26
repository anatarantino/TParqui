#include <prints.h>
#define ZERO_EXCEPTION 0
#define INVALID_OP	1
#define TOTALREGS 16 //hay 17 en el vector, chequear
#define RED 0xFF0000
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define VIOLET 0xB266FF

static void zero_division();
static void invalid_op();
static void printRegisters(uint64_t * registers);

//puede cambiar el orden de como los recibimos
static char* dataRegisters[] = {"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ", 
						"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
                        "RAX: ", "RIP: ", "RSP: "};

void exceptionDispatcher(int exception, void * registers) {
	if (exception == ZERO_EXCEPTION){
		zero_division();
	}else if(exception == INVALID_OP){
		invalid_op();
	}
	printRegisters(registers);
	printNewLine();
	//resetCurrentProcess()  hay que implementarlo al final :O

}

static void zero_division() {
	printColor("ZERO DIVISION ERROR: division by zero is undefined",YELLOW,RED);
}

static void invalid_op(){
	printColor("INVALID OPERATION CODE EXCEPTION",YELLOW,RED);
}

static void printRegisters(uint64_t * registers){
	for(int i=0 ; i < TOTALREGS ; i++){
		printColor(dataRegisters[i],VIOLET,BLACK);
		printHexColor(registers[i],VIOLET,BLACK); 
		printNewLine();
	}
	//fran imprime el rsp aparte
	printColor(dataRegisters[TOTALREGS],VIOLET,BLACK);
	printHexColor(registers[15 + 3],VIOLET,BLACK);


}