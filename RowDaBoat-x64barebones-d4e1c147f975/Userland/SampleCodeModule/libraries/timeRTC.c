#include <timeRTC.h>
#include <syscall.h>

uint8_t getTime(time_type descriptor){
    return syscalls(TIMERTC,descriptor,0,0,0,0,0);
}

