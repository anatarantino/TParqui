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
#define MAX 100

static unsigned char pressed(unsigned char key );

static char pressedKeys[TOTALKEYS][2] =
    {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'}, {0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static char buffer[MAX]={0};
static int index=0;
//static char flag;
//char caps;

static unsigned char key;
static char shift = 0;
static char caps = 0;
char keyToAdd;
static char is_pressed;

void keyboard_handler(){ // 0 0 0 0 80
    if(pressed_key()){
        key = get_key();
        is_pressed = pressed(key);
        if(is_pressed == PRESSED){
            switch (key){
                case 0x2A:  //shift pressed
                    shift = 1;
                    break;
                case 0x36:
                    shift = 1;
                    break;
                case 0x3A: //caps locked pressed
                    if(caps == 1){
                        caps = 0;
                    }else{
                        caps = 1;
                    }
                    break;
            
                default:
                    if(pressedKeys[key][0]!=0){
                        if(shift == 1){
                            if(caps == 1){
                                keyToAdd = pressedKeys[key][0];
                            }else{
                                keyToAdd = pressedKeys[key][1];
                            }
                        }else{
                            if(caps == 1){
                                keyToAdd = pressedKeys[key][1];
                            }else{
                                keyToAdd = pressedKeys[key][0];
                            }
                        }
                        buffer[index++] = keyToAdd;
                    }
                    break;
            }
        }else if(is_pressed == RELEASED){
            //shift released
            if(key == 0xAA || key == 0xB6){
                shift = 0;
            }
    
        }   
        
    }
}

char getChar(){
    char c = 0;
    while (c==0){
        _hlt();
        c = buffer[--index];
    }
    return c;

}

static unsigned char pressed(unsigned char key ){
    if(key > 0x00 && key < 0x58){
        return PRESSED;
    }else if(key >= 0x81 && key <= 0xBA){
        return RELEASED;
    }
    return ERROR; //scan codes not used
}

