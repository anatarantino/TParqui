#ifndef PRINTS_H
#define PRINTS_H

void putChar(char c, int color);
void syscallWrite(char* str, uint64_t f_color, uint64_t bg_color);
void print(char* str);
void printColor(char* str, uint64_t f_color, uint64_t bg_color);

#endif