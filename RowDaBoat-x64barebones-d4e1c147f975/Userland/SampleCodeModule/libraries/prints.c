#include <prints.h>
#include <syscall.h>
#include <strings.h>

#define BLANCO 0xFFFFFF
#define NEGRO 0x000000
#define WRITE 1


void putChar(char c){
    syscalls(WRITE, (uint64_t)&c, 1, BLANCO, NEGRO, 0, 0);
}

void putCharColor(char c,uint64_t f_color,uint64_t bg_color){
    syscalls(WRITE, (uint64_t)&c, 1, f_color, bg_color, 0, 0);
}

void printf(char* str){
     syscalls(WRITE, (uint64_t)str, strlen(str), BLANCO, NEGRO, 0, 0);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
     syscalls(WRITE, (uint64_t)str, strlen(str), f_color, bg_color, 0, 0);
}



