#include <strings.h>
#include <stdarg.h>

int strlen(char * str){
    int i = 0;
    while(str[i]!= 0){
        i++;
    }
    return i;
}

int scanf(const char* format,...){     //scanf("%d %d %f",&num1, &num2, &num3);
    va_list args;
    int i = 0, j=0, ret = 0;
    char buff[100] = {0}, c;
    char *out_loc;
    while(c != '\n') {
        if (fread(&c, 1, 1, stdin)) {
            buff[i] = c;
            i++;
        }
    }

    va_start(args,format);
    i = 0;
    while (format && format[i]) {
    if (format[i] == '%') {
      i++;
    switch (format[i]) {
        case 'c': {
          * (char *)va_arg( args, char* ) = buff[j];
          j++;
          ret ++;
          break;
        }
        case 'd': {
          * (int *)va_arg( args, int* ) = \
          strtol(&buff[j], &out_loc, 10);
          j += out_loc -&buff[j];
          ret++;
          break;
        }
        case 's': {
          out_loc = (char *)va_arg( args, char* );
          strcpy(out_loc, &buff[j]);
          j += strlen(&buff[j]);
          ret++;
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
   return ret;
}
    
}