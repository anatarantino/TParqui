#include <syscall.h>
#include <prints.h>
#include <strings.h>
#include <shell.h>

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000

#define TOTAL_SIZE 2000
#define TOTAL_COMMANDS 6

enum comm_num{INFOREG=0,PRINTMEM,TIME,CHESS,HELP,CLEARSC};

static char * commands[] = {"inforeg","printmem","time","chess","help","clear"};
static char * user = "user >> ";

static char * registers[] = {"rax", "rdi", "rsi", "rdx", "r10", "r8", "r9"};


static char buff[TOTAL_SIZE]={0};
static int index=0;

//static functions
static void printMessage();
static void analizeChar(char c);
static void findCommand();
static void applyCommand(int command_num);
static void removeChar();
static void inforeg();
static void printmem();
static void time();
static void chess();
static void help();
static void clear();

void startShell(){
    char c;
    printf(user);
    while(1){
        c=getChar();
        analizeChar(c);
    }

}

static void analizeChar(char c){
    switch (c)
    {
    case '\n':
        findCommand();
        memset(buff,0,TOTAL_SIZE);
        index=0;
        printf(user);
        break;
    case '\b':
        removeChar();
        break;
    default:
        buff[index++]=c;
        putChar(c);
        break;
    }
}

static void findCommand(){
    int result;
    int flag=FALSE;
    int comm = -1;
    for (int i = 0; i < TOTAL_COMMANDS; i++){
        result=stringcmp(buff,commands[i]);
        if(result==TRUE){
            applyCommand(i);    
            flag=TRUE;
            comm = i;
        }
    }
    if(comm != CLEARSC){
        putChar('\n');
        if(flag == FALSE){
            printColor("Invalid command",RED,BLACK);
            putChar('\n');
        }

    }
    
}

static void applyCommand(int command_num){
    switch (command_num)
    {
    case INFOREG:
        inforeg();
        break;
    case PRINTMEM:
        printmem();
        break;
    case TIME:
        time();
        break;
    case CHESS:
        chess();
        break;
    case HELP:
        help();
        break;
    case CLEARSC:
        clear();
        break;
    }
}

static void removeChar(){
    if(index>0){
        buff[index]=0;
        index--;
        putChar('\b');
    }
}

static void inforeg(){
    

}

static void printmem(){

}

static void time(){


}

static void chess(){

}

static void help(){
    putChar('\n');
    printf("HELP\n");
    printf("DESCRIPTION: this is a list of the commands available.\n");
    printf("inforeg -> prints registers values\n");
    printf("printmem -> receives a pointer and makes a memory dump of 32 bytes on screen starting on the direction introduced.\n"); //igual al de fran cambiar!!!
    printf("time -> prints system time on screen.\n"); 
    printf("clear -> clears the screen.\n");
    printf("chess -> this command starts a chess game.\n");
}

static void clear(){
    clearScreen();

}

static void printMessage(){
    printColor("Hola aca va un mensaje super hermo diciendo que arranca el programa",0xFFFF00,0xF0FF0F);
}