#include <syscall.h>
#include <prints.h>
#include <strings.h>
#include <shell.h>

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000

#define TOTAL_SIZE 2000
#define TOTAL_COMMANDS 6

enum comm_num{INFOREG=0,PRINTMEM,TIME,CHESS,HELP,CLEAR};

static char * commands[] = {"inforeg","printmem","time","chess","help","clear"};
static char * user = "user >> ";


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
        putChar('\n');
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
    for (int i = 0; i < TOTAL_COMMANDS; i++){
        result=stringcmp(buff,commands[i]);
        if(result==TRUE){
            applyCommand(i);    
            flag=TRUE;
        }
    }
    if(flag==FALSE){
        putChar('\n');
        printColor("Invalid command",RED,BLACK);
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
    case CLEAR:
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
    printf("ENTRASTE A HELP");
}

static void clear(){
    

}

static void printMessage(){
    printColor("Hola aca va un mensaje super hermo diciendo que arranca el programa",0xFFFF00,0xF0FF0F);
}