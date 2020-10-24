#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

void keyboard_handler(uint64_t rsp);
char getChar();
int shiftPressed(uint8_t key);
int pressed(uint8_t key );

#endif