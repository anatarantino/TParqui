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
uint8_t key;

void keyboard_handler(uint64_t rsp){
    if(pressed_key()){
        key = get_key();
        if (pressed(key)==PRESSED){
            int flag = shiftPressed(key);
            putChar(pressedKeys[(char)key][flag]);
        }
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

    }

}

char getChar(){
    _hlt();
    return buffer[index];

}

int pressed(uint8_t key ){
    if(key > 0x00 && key < 0x58){
        return PRESSED;
    }else if(key >= 0x81 && key <= 0xD8){
        return RELEASED;
    }

    return ERROR; //scan codes not used
}

int shiftPressed(uint8_t key){
    if(key==0x2A || key==0x36 || key==0x3A){
        return SHIFT;
    }

    return NOTSHIFT;
}
