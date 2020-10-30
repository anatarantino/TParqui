#ifndef PRINTS_H
#define PRINTS_H

#include <stdint.h>

void putChar(char c);
void putCharColor(char c,uint64_t f_color,uint64_t bg_color);
void syscallWrite(char* str, uint64_t f_color, uint64_t bg_color);
void printf(char* str);
void printColor(char* str, uint64_t f_color, uint64_t bg_color);
void printInt(uint64_t num);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void clearScreen();

#endif