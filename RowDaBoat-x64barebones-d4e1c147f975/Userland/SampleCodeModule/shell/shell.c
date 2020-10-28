#include <syscall.h>
#include <prints.h>

#define BLANCO 0xFFFFFF
#define NEGRO 0x000000

static char * commands[] = {"inforeg","printmem","time","chess","help"};
static char * user = "user >> ";

static void startScreen();
static void printMessage();

void startShell(){

    startScreen();
    //printMessage();
    printf("hola");
    while(1){
        printColor("hola genteeeee",0xFFFF00,0xFF0000);
    }

}

static void startScreen(){
    syscalls(SCREEN, 0, 0,BLANCO, NEGRO, 0,0);
}

static void printMessage(){
    printColor("Hola aca va un mensaje super hermo diciendo que arranca el programa",0xFFFF00,0xF0FF0F);
}