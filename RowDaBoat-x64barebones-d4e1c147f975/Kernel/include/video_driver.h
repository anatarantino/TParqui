#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

void initializeVideo(int bg_color,int f_color);
void drawPixel(int x,int y,int color);
void printCharOnScreen(char c, uint64_t f_color, uint64_t bg_color);


#endif