#include <syscallDispatcher.h>
#include <keyboard_driver.h>
#include <video_driver.h>
#include <prints.h>

#define READ 0
#define WRITE 1
#define SCREEN 2
#define CLEAR 3

#define BLACK 0x000000

#define CANT_SYS 4
//                          codigo        puntero       length          f_color     bg_color       extra         extra
//                          uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9
uint64_t syscallDispatcher(t_registers * r){
    if(r->rax >= 0 && r->rax <= CANT_SYS){
        switch (r->rax)
        {
            case READ:
                //printf("Entre al read");
                return getChar();
                break;
            case WRITE:
                syscallWrite((char *) r->rdi,(uint64_t) r->rsi, (uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case SCREEN:
                initializeVideo((uint64_t) r->rdx, (uint64_t) r->r10);
                break;
            case CLEAR:
                clearScreen(BLACK);
                break;
        }    
    }
    return 0;
}