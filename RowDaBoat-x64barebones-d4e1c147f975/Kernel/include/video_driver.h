#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024

void initializeVideo(int bg_color,int f_color);
void drawPixel(int x,int y,int color);
void printCharOnScreen(char c, uint64_t f_color, uint64_t bg_color);
void deleteChar();
void newLine();
void clearScreen(uint64_t bg_color);
void scrollScreen();

#endif