#ifndef STRINGS_H
#define STRINGS_H

#include <stdint.h>

#define SIZE 100
#define EOF -1
#define FALSE 0
#define TRUE 1 

int strlen(char * str);
int scanf(const char* format,...);
char * read();
char* strToInt(char* string, int* num);
char getChar();
int stringcmp(char * str1, char * str2);
void * memset(void * destination, int32_t c, uint64_t length);

#endif