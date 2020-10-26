#include <stdint.h>
#include <video_driver.h>
#include <prints.h>
#include <strings.h>

//#define BLANCO 0xFFFFFF
//#define NEGRO 0x000000

void syscallWrite(char* str, uint8_t length, uint64_t f_color, uint64_t bg_color){
    
    for(int i=0; str[i]!= 0 && i < length; i++){
        if(str[i] == '\n'){
            newLine();
        }else if(str[i] == '\b'){
            deleteChar();
        }else if(str[i] == '\t'){
            for(int i =0 ; i<3 ; i++){
                printCharOnScreen(' ',f_color,bg_color);
            }
        }else{
            printCharOnScreen(str[i],f_color,bg_color);
        }
    }
}

void putChar(char c){
    syscallWrite(&c,1,0xFFFFFF,0x000000);
}

void putCharColor(char c,uint64_t f_color,uint64_t bg_color){
    syscallWrite(&c,1,f_color,bg_color);
}


void printf(char* str){
    syscallWrite(str,strlen(str),0xFFFFFF,0x000000);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
    syscallWrite(str,strlen(str),f_color,bg_color);
}

void printNewLine(){
    putChar('\n');
}

void printHex(uint64_t num){
    char buff[10];
    uintToBase(num,buff,16);
    printf(buff);
}

void printHexColor(uint64_t num, uint64_t f_color, uint64_t bg_color){
    char buff[10];
    uintToBase(num,buff,16);
    printColor(buff,f_color,bg_color);
}

void printInt(uint64_t num){
    char buff[10];
    uintToBase(num,buff,10);
    printf(buff);
}

void printIntColor(uint64_t num, uint64_t f_color, uint64_t bg_color){
    char buff[10];
    uintToBase(num,buff,10);
    printColor(buff,f_color,bg_color);
}
