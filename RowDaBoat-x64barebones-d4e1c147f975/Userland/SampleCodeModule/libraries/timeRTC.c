#include <timeRTC.h>
#include <syscall.h>

uint8_t getTime(time_type descriptor){
    return syscalls(TIMERTC,descriptor,0,0,0,0,0);
}

uint64_t seconds_elapsed(){
    return syscalls(SECONDSELAPSED,0,0,0,0,0,0);
}

