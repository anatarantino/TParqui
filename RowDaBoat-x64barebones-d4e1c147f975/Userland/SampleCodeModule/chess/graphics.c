#include <graphics.h>
#include <prints.h>
#include <syscall.h>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
#define BOARDSIZE 760
#define SQUARESIZE 95
#define STARTX 162
#define ENDX 862
#define STARTY 4
#define ENDY 764

void drawPixel(int x, int y, int color){
    syscalls(DRAW,0,0,color,0,x,y);
}


void drawBoard(uint64_t color1, uint64_t color2){
    int cant_sq=0;
    for(int h=0 ; h<SCREENHEIGHT ; h++){
        for(int w=0 ; w<SCREENWIDTH; w++){
            if((w>=STARTX && w<=ENDX) && (h>=STARTY && h<= ENDY)){
                if((w>=STARTX && w<=STARTX+SQUARESIZE) && (h>=STARTY && h<=STARTY+SQUARESIZE)){
                    drawPixel(w,h,color2);
                }else{
                    drawPixel(w,h,color1);
                }
            }
        }
    }
}