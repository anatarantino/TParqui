#include <syscall.h>
#include <prints.h>
#include <strings.h>
#include <shell.h>
#include <timeRTC.h>
#include <graphics.h>
#include <chess.h>
#include <colors.h>

#define TOTAL_SIZE 150
#define TOTAL_COMMANDS 8
#define TOTAL_REG 17
#define TOTAL_ARGUMENTS 5

enum comm_num{INFOREG=0,PRINTMEM,TIME,CHESS,HELP,CLEARSC,DIVZERO,OPCODE};

static char * commands[] = {"inforeg","printmem","time","chess","help","clear","divByZeroException","opCodeException"};
static char * user = "grupo33@user:~$";

static char * registers[] = {"R15: ", "R14: ", "R13: ", "R12: ", "R11: ", "R10: ", "R9:  ",
                           "R8:  ", "RSI: ", "RDI: ", "RBP: ", "RDX: ", "RCX: ", "RBX: ","RAX: ",
                            "RIP: ", "RSP: "};


static char buff[TOTAL_SIZE]={0};
static int index=0;

//static functions
static void printMessage();
static void analizeChar(char c);
static void findCommand();
static void applyCommand(int command_num,char*arguments[],int totArgs);
static void removeChar();
static void inforeg(int args, char *arguments[]);
static void printmem(int args, char *arguments[]);
static void time(int args, char *arguments[]);
static void printTime(time_type desc);
static void chess(int args, char *arguments[]);
static void help(int args, char *arguments[]);
static void clear(int args, char *arguments[]);
static void divisionByZero(int args,char *arguments[]);
static void opCodeException(int args,char *arguments[]);

void startShell(){
    char c;
    printMessage();
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
    if((index-2) < TOTAL_SIZE){
        buff[index++]=c;
        putChar(c);
    }
     break;
    }
}

static void findCommand(){
    char * arguments[TOTAL_ARGUMENTS];
    int totArgs = strtok(buff,' ', arguments, 10);
    int result;
    int flag=FALSE;
    int comm = -1;
    for (int i = 0; i < TOTAL_COMMANDS; i++){
        result=stringcmp(arguments[0],commands[i]);
        if(result==TRUE){
            applyCommand(i,arguments+1,totArgs);    
            flag=TRUE;
            comm = i;
        }
    }
    if(comm != CLEARSC && comm !=CHESS){
        putChar('\n');
        if(flag == FALSE){
            printColor("Invalid command",RED,BLACK);
            putChar('\n');
        }

    }
    
}

static void applyCommand(int command_num,char *arguments[],int totArgs){
    switch (command_num)
    {
    case INFOREG:
        inforeg(totArgs,arguments);
        break;
    case PRINTMEM:
        printmem(totArgs,arguments);
        break;
    case TIME:
        time(totArgs,arguments);
        break;
    case CHESS:
        chess(totArgs,arguments);
        break;
    case HELP:
        help(totArgs,arguments);
        break;
    case CLEARSC:
        clear(totArgs,arguments);
        break;
    case DIVZERO:
        divisionByZero(totArgs,arguments);
        break;
    case OPCODE:
        opCodeException(totArgs,arguments);
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

static void inforeg(int args, char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    putChar('\n');
    uint64_t* regs=(uint64_t *)getRegisters();
    for(int i=0; i< TOTAL_REG; i++){
        printColor(registers[i],VIOLET,BLACK);
        printHex(regs[i]);
        putChar('\n');
    }
}

static void printmem(int args, char *arguments[]){
   uint64_t num=hexastrToInt(arguments[0]);
    char buffer[200];
    if(args!=2){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    if(num==0){
        putChar('\n');
        printf("Invalid argument");
        putChar('\n');
        return;
    }
    putChar('\n');
    uint8_t *rsp=(uint8_t *) num;
      for (int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++){
            uintToBase(rsp[8*i + j], buffer, 16);
            printf(buffer);
            putChar(' ');
        }
        putChar('\n'); 
    }

}

static void time(int args, char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    putChar('\n');
    printColor("Date time:",0xFFFF00,BLACK);
    putChar('\n');
    printTime(DAYOFWEEK);
    putChar('\n');
    printTime(DAY);
    putChar('/');
    printTime(MONTH);
    putChar('/');
    printTime(YEAR);
    putChar('\n');
    printTime(HOURS);
    putChar(':');
    printTime(MINUTES);
    putChar(':');
    printTime(SECONDS);

}

static void printTime(time_type desc){
    char buff_aux[3];
    int aux;
    switch(desc){
        case YEAR:
            uintToBase(getTime(YEAR),buff_aux,10);
            printf(buff_aux);
            break;
        case MONTH:
            uintToBase(getTime(MONTH),buff_aux,10);
            printf(buff_aux);
            break;
        case DAY:
            uintToBase(getTime(DAY),buff_aux,10);
            printf(buff_aux);
            break;
        case DAYOFWEEK:
            switch(getTime(DAYOFWEEK)){
                case 1: 
                    printf("Sunday");
                    break;
                case 2:
                    printf("Monday");
                    break;
                case 3: 
                    printf("Tuesday");
                    break;
                case 4:
                    printf("Wednesday");
                    break;
                case 5:
                    printf("Thursday");
                    break;
                case 6:
                    printf("Friday");
                    break;
                case 7:
                    printf("Saturday");
                    break;
            }
            break;
        case HOURS:
            aux = getTime(HOURS);
            if(aux < 3)
                aux = 24 - 3 + aux;
            else
                aux -= 3;
            uintToBase(aux,buff_aux,10);
            printf(buff_aux);
            break;
        case MINUTES:
            uintToBase(getTime(MINUTES),buff_aux,10);
            printf(buff_aux);
            break;
        case SECONDS:
            uintToBase(getTime(SECONDS),buff_aux,10);
            printf(buff_aux);
            break;
        default:
            return;
    }
}


static void help(int args, char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    putChar('\n');
    printf("HELP\n");
    printf("DESCRIPTION: this is a list of the commands available.\n");
    printf("inforeg -> prints registers values, press ctrl + r to update values.\n");
    printf("printmem -> receives a pointer and makes a memory dump of 32 bytes on screen starting on the direction introduced.\n"); //igual al de fran cambiar!!!
    printf("time -> prints system time on screen.\n"); 
    printf("clear -> clears the screen.\n");
    printf("chess -> this command starts a chess game.\n");
    printf("divByZeroException -> tests the division by zero exception.\n");
    printf("opCodeException -> tests the exception caused by an invalid operation code.");

}

static void clear(int args, char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    clearScreen();

}


static void printMessage(){
    printColorOnPos("Press 'help' to see the commands of this shell.",GREEN,BLACK,0,0);
    putChar('\n');
}

static void divisionByZero(int args,char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }

    int a = 0;
    int b = 1/a;
    a = b;
    return;

}
static void opCodeException(int args,char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    __asm__("ud2");
}
static void chess(int args, char *arguments[]){
    if(args!=1){
        putChar('\n');
        printf("Invalid ammount of arguments");
        putChar('\n');
        return;
    }
    clearScreen();
    printColorOnPos("PRESIONE N SI QUIERE UN NUEVO JUEGO O C PARA CONTINUAR EL ANTERIOR",GREEN,BLACK,230,300);
    int state;

    while (state!='n' && state!='N' && state != 'c' && state != 'C')
    {
        state = getChar();
    }
    state = (state == 'n' || state == 'N') ? 0 : 1;
    clearScreen();
    playChess(state);

}

