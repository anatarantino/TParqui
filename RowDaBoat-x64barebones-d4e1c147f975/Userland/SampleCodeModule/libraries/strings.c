#include <strings.h>
#include <stdarg.h>
#include <syscall.h>

char getChar(){
    return syscalls(READ, 0, 0, 0, 0, 0, 0);
}
char getCharWithTimer(uint64_t * startSec,uint64_t posX, uint64_t posY, uint64_t f_color, uint64_t bg_color){
  return syscalls(TIMEDREAD,(uint64_t) startSec,posX,posY,f_color,bg_color,0);
}
int strlen(char * str){
    int i = 0;
    while(str[i]!= 0){
        i++;
    }
    return i;
}

int stringcmp(char * str1, char * str2){ 
    int index=0;
    while (str1[index]!=0 && str2[index]!=0)
    {
      if(str1[index]!=str2[index]){
        return FALSE;
      }
      index++;
    }
    if(str1[index]==0 && str2[index]==0){
        return TRUE;
    }
    return FALSE;
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

uint64_t hexastrToInt(char *str){
    uint64_t res = 0;
    char c;

    while ((c = *str++)) {
        char v = ((c & 0xF) + (c >> 6)) | (((c >> 3) & 0x8));
        res = (res << 4) | (uint64_t) v;
    }
    return res;

}

char* read(){
    int index = 0;
    char c;
    char buffer[SIZE];

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

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

int strtok(char * str, const char delim, char * array[], int arraySize){
	int index = 0;
	if(*str != delim && *str != 0){
		array[index++] = str;
    }
	while( *str != 0 ){
		if(*str == delim){
			*str = 0;
			if( *(str+1) != delim &&  (*(str+1) != 0)){
				if(index >= arraySize){
					return index;
                }
				array[index++] = str + 1;
			}
		}
		str++;
	}
	return index;
} 