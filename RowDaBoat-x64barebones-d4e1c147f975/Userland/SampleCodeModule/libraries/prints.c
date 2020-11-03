#include <prints.h>
#include <syscall.h>
#include <strings.h>

#define BLANCO 0xFFFFFF
#define NEGRO 0x000000

void putChar(char c){
    syscalls(WRITE, (uint64_t)&c, 1, BLANCO, NEGRO, 0, 0);
}

void putCharColor(char c,uint64_t f_color,uint64_t bg_color){
    syscalls(WRITE, (uint64_t)&c, 1, f_color, bg_color, 0, 0);
}

void printf(char* str){
    syscalls(WRITE, (uint64_t)str, strlen(str), BLANCO, NEGRO, 0, 0);
}

void printHex(uint64_t num){
    char buff[10];
    uintToBase(num,buff,16);
    printf(buff);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
    syscalls(WRITE, (uint64_t)str, strlen(str), f_color, bg_color, 0, 0);
}
void printColorOnPos(char *str, uint64_t f_color, uint64_t bg_color, uint32_t posX, uint32_t posY){
	syscalls(WRITEONSCREEN,(uint64_t)str, strlen(str), f_color, bg_color, posX, posY);
}

void printIntOnPosColor(uint64_t num,uint64_t f_color,uint64_t bg_color,uint32_t posX, uint32_t posY){
    char buff[10];
    uintToBase(num,buff,10);
    printColorOnPos(buff, f_color, bg_color, posX, posY);
}

void printInt(uint64_t num){
    char buff[10];
    uintToBase(num,buff,10);
    printf(buff);
}

void clearScreen(){
	syscalls(CLEAR,0,0,0,0,0,0);
}

void clearSpace(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy, uint64_t bg_color){
	syscalls(CLEARSPACE,startx,starty,endx,bg_color,endy,0);
}

uint64_t* getRegisters(){
	return (uint64_t *)syscalls(REGISTERS,0,0,0,0,0,0);
}

uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
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