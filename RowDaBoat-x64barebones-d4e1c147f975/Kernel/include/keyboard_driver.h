#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

void keyboard_handler(uint64_t rsp);
char getChar();
char shiftPressed(char key);
char pressed(char key );
char capsLockPressed(char key);

#endif