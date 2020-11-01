#include <graphics.h>
#include <prints.h>
#include <syscall.h>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
#define BOARDSIZE 760
#define SQUARESIZE 87
#define STARTX 157
#define ENDX 847
#define STARTY 4
#define ENDY 700

void drawPixel(int x, int y, int color){
    syscalls(DRAW,0,0,color,0,x,y);
}
//(w>=STARTX && w<=STARTX+SQUARESIZE) && (h>=STARTY && h<=STARTY+SQUARESIZE) 

void drawBoard(uint64_t color1, uint64_t color2){
    int paint=0;
    int noPaint=0;
    int cantX=0,cantY=0;

    uint64_t aux_color1=color1,aux_color2=color2;
    for(int h=0 ; h<SCREENHEIGHT ; h++){
        if((h-STARTY)%87 == 0){
            if(aux_color1==color1){
                aux_color1=color2;
                aux_color2=color1;
            }else{
                aux_color1=color1;
                aux_color2=color2;
            }
        }
        for(int w=0 ; w<SCREENWIDTH; w++){
            if((w>=STARTX && w<=ENDX) && (h>=STARTY && h<= ENDY)){
                if(((w-STARTX)%87==0)){
                    if(aux_color1==color1){
                        aux_color1=color2;
                        aux_color2=color1;
                    }else{
                        aux_color1=color1;
                        aux_color2=color2;
                    }
                }
                if(cantY>=0 && cantY<87){
                    drawPixel(w,h,aux_color2);
                    cantY++;
                }else{
                    drawPixel(w,h,aux_color1);
                }

            }
        }
        
    }
}

/*
void drawBoard(uint64_t color1, uint64_t color2){
    uint64_t aux_color1=color1,aux_color2=color2;
    for(int y=STARTY ; y<ENDY ; y++){
        if(y%87 == 0){
            if(aux_color1==color1){
                aux_color1=color2;
                aux_color2=color1;
            }else{
                aux_color1=color1;
                aux_color2=color2;
            }
        }
        for(int x=STARTX ; x<ENDX ; x++){
            if(x%87 == 0){
                if(aux_color1==color1){
                        aux_color1=color2;
                        aux_color2=color1;
                    }else{
                        aux_color1=color1;
                        aux_color2=color2;
                    }
            }

            if(y>=0 && y<87){
                drawPixel(x,y,aux_color2);
            }else{
                drawPixel(x,y,aux_color1);
            }
        }

    }
}
*/