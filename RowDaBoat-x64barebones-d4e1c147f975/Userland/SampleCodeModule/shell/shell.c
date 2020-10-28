#include <syscall.h>

#define BLANCO 0xFFFFFF
#define NEGRO 0x000000

static char * commands[] = {"inforeg","printmem","time","chess","help"};
static char * user = "user >> ";

void startShell(){
    startScreen();


}

void startScreen(){
    syscalls(SCREEN, 0, 0, 0, BLANCO, NEGRO, 0);
}