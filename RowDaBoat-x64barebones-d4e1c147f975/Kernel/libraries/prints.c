#include <stdint.h>
#include <prints.h>
#include <video_driver.h>


#define BLANCO 0xFFFFFF
#define NEGRO 0x000000

void putChar(char c, int color){

}

void syscallWrite(char* str, uint64_t f_color, uint64_t bg_color){
    
    for(int i=0; str[i]!= 0; i++){
        printCharOnScreen(str[i],f_color,bg_color);
    }
}

void print(char* str){
    syscallWrite(str,BLANCO,NEGRO);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
    syscallWrite(str,f_color,bg_color);
}