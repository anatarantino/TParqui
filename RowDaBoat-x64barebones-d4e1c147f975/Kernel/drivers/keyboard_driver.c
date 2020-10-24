#include <keyboard_driver.h>
#include <keyboard.h>
#include <stdint.h>
#include <interrupts.h>
#include <prints.h>
#include <video_driver.h>

#define SHIFT 1
#define NOTSHIFT 0
#define TRUE 1
#define FALSE 0
#define TOTALKEYS 60
#define MAX 10

static char pressedKeys[TOTALKEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static char buffer[MAX]={0};
int index=0;
char key;

void keyboard_handler(uint64_t rsp){
    if(pressed_key()){
        key = get_key();
        int flag = shiftPressed(key);
        switch (flag){
            case SHIFT:{
                key = get_key();
                putChar(pressedKeys[key][1]);
                break;
            }
            case NOTSHIFT:{
                putChar(pressedKeys[key][0]);
                break;
            }
            
        }

    }
}

char getChar(){
    _hlt();
    return buffer[index];

}

void specialChar(char key,int pos){
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
        buffer[index++]='\n';
    }else{
        buffer[index++]=pressedKeys[key][pos];
    }
}


int shiftPressed(char key){
    if(key==0x2A || key==0x36 || key==0x3A){
        return SHIFT;
    }
    return NOTSHIFT;
}
