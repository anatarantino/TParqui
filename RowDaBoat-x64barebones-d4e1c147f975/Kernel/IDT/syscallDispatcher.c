#include <syscallDispatcher.h>
#include <keyboard_driver.h>
#include <prints.h>

#define READ 0
#define WRITE 1
#define CANT_SYS 2

uint64_t syscallDispatcher(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r10, uint64_t r8, uint64_t r9){
    if(rax > 0 && rax <= CANT_SYS){
        switch (rax)
        {
            case READ:
                return getChar();
                break;
            case WRITE:
                syscallWrite((char *) rdi,(uint64_t) rsi, (uint64_t) rdx, (uint64_t) r10);
                break;
        }    
    }
    return 0;
}