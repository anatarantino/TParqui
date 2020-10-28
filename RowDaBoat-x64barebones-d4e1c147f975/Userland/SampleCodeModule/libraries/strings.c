#include <strings.h>
#include <stdarg.h>
#include <syscall.h>

#define SIZE 100
#define EOF -1


char getChar(){
      return syscalls(READ, 0, 0, 0, 0, 0, 0);
}

int strlen(char * str){
    int i = 0;
    while(str[i]!= 0){
        i++;
    }
    return i;
}

int scanf(const char* format,...){     //scanf("%d %d %f",&num1, &num2, &num3);             CHEQUEARLO 
    va_list args;
    int i = 0, j=0, count = 0;
    char *buff = read();
    char *character;
    va_start(args,format);
    while (format && format[i]) {
      if (format[i] == '%') {
        i++;
        switch (format[i]) {
          case 'c': {
            character = va_arg(args, char*);
            *character = buff[j];
            j++;
            count++;
            break;
          }
          case 'd': {
            buff = strToInt(buff, va_arg(args,int *));
            count++;
            break;
          }
          case 's': {
            character = va_arg(args,char*);
            char temp;
            while( (temp = buff[j]) != '\0'){ 
                *character = buff[j];
                character++;
                j++;
            }
            count++;
            break;
          }
        }
      } else {
        buff[j] =format[i];
        j++;
      }
      i++;
    }
    va_end(args);
    return count;
}


char * read(){
    int index = 0;
    char c;
    char buffer[SIZE] = {0};

    while ((c = getChar()) != '\n') {
        if(c == '\b'){
            if (index != 0) {
                index--;
            }
        }
        else if(c != EOF){
            if (index <= SIZE) {
                buffer[index++] = c;
            }
        }
    }
    buffer[index] = '\0';
    return buffer;
}


char* strToInt(char* string, int* num){
    *num = 0;
	  int signo = 1;
    char character;

    if(*string == '-'){
      character = *(string + 1);
      if (character >= '0' && character <= '9') {
        signo = -1;
        *num = (character - '0') * signo;
        string+=2;
      } else {
        return string;
      }
	  }
    character = *string;
    while (character >= '0' && character <= '9'){
        *num = (*num)*10+(character-'0')*signo;
        string++;
    }
    return string;
}