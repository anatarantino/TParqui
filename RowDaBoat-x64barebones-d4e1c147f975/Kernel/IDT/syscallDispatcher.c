#include <syscallDispatcher.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <prints.h>

#define READ 0
#define WRITE 1
#define SCREEN 2
#define CLEAR 3
#define REGISTERS 4

//modificar con lo de esceptions
#define TOTALREGS 16 //hay 17 en el vector, chequear
#define RED 0xFF0000
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define VIOLET 0xB266FF




#define BLACK 0x000000
#define CANT_SYS 4

static void printRegisters(uint64_t * registers);
//                          codigo        puntero       length          f_color     bg_color       extra         extra
//                          uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9
uint64_t syscallDispatcher(t_registers * r){
    if(r->rax >= 0 && r->rax <= CANT_SYS){
        switch (r->rax)
        {
            case READ:
                //printf("Entre al read");
                return getChar();
                break;
            case WRITE:
                syscallWrite((char *) r->rdi,(uint64_t) r->rsi, (uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case SCREEN:
                initializeVideo((uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case CLEAR:
                clearScreen(BLACK);
                break;
            case REGISTERS:
                printRegisters(r);
                break;
        }    
    }
    return 0;
}

static char* dataRegisters[] = {"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9: ", 
						"R8: ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ",
                        "RAX: ", "RIP: ", "RSP: "};

static void printRegisters(uint64_t * registers){ //despues modularizar porque se usa en exceptions
	for(int i=0 ; i < TOTALREGS ; i++){
		printColor(dataRegisters[i],VIOLET,BLACK);
		printHexColor(registers[i],VIOLET,BLACK); 
		printNewLine();
	}
	//fran imprime el rsp aparte
	printColor(dataRegisters[TOTALREGS],VIOLET,BLACK);
	printHexColor(registers[15 + 3],VIOLET,BLACK);
}