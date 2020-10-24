#include <stdint.h>
#include <video_driver.h>
#include <prints.h>

//#define BLANCO 0xFFFFFF
//#define NEGRO 0x000000

void putChar(char c){
    syscallWrite(&c,0xFFFFFF,0x000000);
}

void putCharColor(char c,uint64_t f_color){
    syscallWrite(&c,f_color,0x000000);
}

void syscallWrite(char* str, uint64_t f_color, uint64_t bg_color){
    
    for(int i=0; str[i]!= 0; i++){
        printCharOnScreen(str[i],f_color,bg_color);
    }
}

void printf(char* str){
    syscallWrite(str,0xFFFFFF,0x000000);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
    syscallWrite(str,f_color,bg_color);
}
