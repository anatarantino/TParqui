#include <syscallDispatcher.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <prints.h>
#include <RTCtime.h>
#include <time.h>

#define READ 0
#define WRITE 1
#define SCREEN 2
#define CLEAR 3
#define REGISTERS 4
#define TIMERTC 5
#define DRAW 6
#define CLEARSPACE 7
#define WRITEONSCREEN 8
#define TICKSELAPSED 9
#define TIMEDREAD 10
#define CHARINTERRUPT 11

//modificar con lo de esceptions
#define TOTALREGS 16 //hay 17 en el vector, chequear
#define RED 0xFF0000
#define YELLOW 0xFFFF00
#define BLACK 0x000000
#define VIOLET 0xB266FF


#define BLACK 0x000000
#define CANT_SYS 12

//                          codigo        puntero       length          f_color     bg_color       extra         extra
//                          uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9
uint64_t syscallDispatcher(t_registers * r){
    if(r->rax >= 0 && r->rax < CANT_SYS){
        switch (r->rax)
        {
            case READ:
                return getChar();
            case TIMEDREAD:
                //hay que ver el orden de como mandamos las cosas
                return getCharWithTimer((uint64_t *) r->rdi, (uint64_t)r->rsi, (uint64_t)r->rdx, (uint64_t)r->r10,(uint64_t)r->r8);
            case WRITE:
                syscallWrite((char *) r->rdi,(uint64_t) r->rsi, (uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case SCREEN:
                initializeVideo((uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case CLEAR:
                clearScreen(BLACK);
                break;
            case REGISTERS:
                return (uint64_t) returnReg();
            case TIMERTC:
                return getTime((time_type)(r->rdi));
            case DRAW:
                drawPixel((int)r->r8,(int)r->r9,(int)r->rdx);
                //r8->x r9->y rdx->color
                break;
            case CLEARSPACE:
                clearSpace((uint32_t)r->rdi, (uint32_t) r->rsi,(uint32_t) r->rdx, (uint32_t) r->r8, (uint64_t)r->r10);
                break;
            case WRITEONSCREEN:
                syscallWriteOnCurrentPos((char *)r->rdi,(uint64_t)r->rsi,(uint64_t)r->rdx, (uint64_t) r->r10,(uint32_t)r->r8,(uint32_t)r->r9);
                //no se si no es r9 y despues r8
                break;
            case TICKSELAPSED:
                return ticks_elapsed();
            case CHARINTERRUPT:
                return waitCharInteruption();
        
        }    
    }
    return 0;
}

