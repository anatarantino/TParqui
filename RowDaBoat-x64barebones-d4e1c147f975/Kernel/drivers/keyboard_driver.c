#include <keyboard_driver.h>
#include <keyboard.h>
#include <stdint.h>
#include <interrupts.h>
#include <prints.h>
#include <video_driver.h>

#define SHIFT 1
#define NOTSHIFT 0
#define PRESSED 1
#define RELEASED 0
#define ERROR -1
#define TOTALKEYS 60
#define MAX 10

static char pressedKeys[TOTALKEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static char buffer[MAX]={0};
int index=0;
//static char flag;
//char caps;

char key;
static char shift = 0;
static char caps = 0;

void keyboard_handler(uint64_t rsp){ // 0 0 0 0 80
    if(pressed_key()){
        key = get_key();
        char p = pressed(key);
        if (p==PRESSED){
            shift = shiftPressed(key);
            putChar(pressedKeys[key][shift]);
        }
        else if(p==RELEASED){
            shift = 0;
        }
    }
}
/*
void keyboard_handler(uint64_t rsp){
    char keyPress;
    if(pressed_key()){
        char key = get_key();
        flag = shiftPressed(key);
        caps=capsLockPressed(key);
        switch (flag){
            case SHIFT:{
//                buffer[index++]=pressedKeys[key][0];
//                putChar(buffer[index-1]);
                if(caps==0){
                    keyPress=pressedKeys[key][1];
                }else{
                    keyPress=pressedKeys[key][0];
                }
               // printf("NOSHIFT");
               // putChar(pressedKeys[(char)key][0]);
               printf("SI SHIFT");
                break;
            }   
            case NOTSHIFT:{
                if(caps==0){
                    keyPress=pressedKeys[key][0];
                }else{
                    keyPress=pressedKeys[key][1];
                }
//                buffer[index++]=pressedKeys[key][1];
//                putChar(buffer[index-1]);
               printf("NO SHIFT");
                break;
            }
        }
            putChar(keyPress);
    }
}*/
/*
        int p=pressed(key);
        if (p==PRESSED){
            putChar(flag+'0');
            putChar(pressedKeys[key][flag]);
        }

*/        /*
        else if(p==RELEASED){
            flag=0;
        }
    */
    //    putChar(pressedKeys[(char)key][flag]);

        
    
        /*
        switch (flag){
            case NOTSHIFT:{
//                buffer[index++]=pressedKeys[key][0];
//                putChar(buffer[index-1]);
                printf("NOSHIFT");
                putChar(pressedKeys[(char)key][0]);
                break;
            }   
            case SHIFT:{
                printf("SHIFT");

                key = get_key();
//                buffer[index++]=pressedKeys[key][1];
//                putChar(buffer[index-1]);
                putChar(pressedKeys[(char)key][1]);
                break;
            }
        }
        */

    //}


char getChar(){
    _hlt();
    return buffer[index];

}

char pressed(char key ){
    if(key > 0x00 && key < 0x58){
        return PRESSED;
    }else if(key >= 0x81 && key <= 0xD8){
        return RELEASED;
    }
    return ERROR; //scan codes not used
}

char shiftPressed(char key){
    if(key==0x2A || key==0x36 ){
        return SHIFT;
    }
    return NOTSHIFT;
}

char capsLockPressed(char key){
    if(key==0x3A){
        return PRESSED;
    }
    return RELEASED;
}
