#include <stdint.h>
#include <video_driver.h>
#include <prints.h>

//#define BLANCO 0xFFFFFF
//#define NEGRO 0x000000

void syscallWrite(char* str, uint64_t f_color, uint64_t bg_color){
    
    for(int i=0; str[i]!= 0; i++){
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
    syscallWrite(&c,0xFFFFFF,0x000000);
}

void putCharColor(char c,uint64_t f_color){
    syscallWrite(&c,f_color,0x000000);
}


void printf(char* str){
    syscallWrite(str,0xFFFFFF,0x000000);
}

void printColor(char* str, uint64_t f_color, uint64_t bg_color){
    syscallWrite(str,f_color,bg_color);
}


/*
void specialChar(char key){
    if(key==0x0E){ //backspace
        if(index!=0){
            index-=1;
            buffer[index]=' ';
        }      
    }
    else if(key==0x0F){ //tab
        for (int i = 0; i < 3; i++)
        {
            buffer[index++]=' ';
        }
    }
    else if(key==0x1C){ //enter
        buffer[index++]='\n';       println();
    }
}
*/