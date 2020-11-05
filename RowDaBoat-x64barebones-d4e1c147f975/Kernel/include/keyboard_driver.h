#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

void keyboard_handler(uint64_t rsp);
char getChar();
char getCharWithTimer(uint64_t * startSec,uint64_t posX, uint64_t posY, uint64_t f_color, uint64_t bg_color);
uint64_t * returnReg();

#endif